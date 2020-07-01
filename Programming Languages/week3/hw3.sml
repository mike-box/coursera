(*
1. Write a function only_capitals that takes a string list and returns a string list that has only
the strings in the argument that start with an uppercase letter. Assume all strings have at least 1
character. Use List.filter, Char.isUpper, and String.sub to make a 1-2 line solution.
*)	
val only_capitals =  List.filter(fn s => Char.isUpper (String.sub(s,0)))
	
(*
2. Write a function longest_string1 that takes a string list and returns the longest string in the
list. If the list is empty, return "". In the case of a tie, return the string closest to the beginning of the
list. Use foldl, String.size, and no recursion (other than the implementation of foldl is recursive).
*)
val longest_string1 = List.foldl (fn (x,max) => if String.size(x) > String.size(max) then x else max) ""
	
	
(*
3. Write a function longest_string2 that is exactly like longest_string1 except in the case of ties
it returns the string closest to the end of the list. Your solution should be almost an exact copy of
longest_string1. Still use foldl and String.size.
*)	
val longest_string2 = List.foldl (fn (x,max) => if String.size(x) >= String.size(max) then x else max) ""


(*
4. Write functions longest_string_helper, longest_string3, and longest_string4 such that:
• longest_string3 has the same behavior as longest_string1 and longest_string4 has the
same behavior as longest_string2.
• longest_string_helper has type (int * int -> bool) -> string list -> string
(notice the currying). This function will look a lot like longest_string1 and longest_string2
but is more general because it takes a function as an argument.
• If longest_string_helper is passed a function that behaves like > (so it returns true exactly
when its first argument is stricly greater than its second), then the function returned has the same
behavior as longest_string1.
• longest_string3 and longest_string4 are defined with val-bindings and partial applications
of longest_string_helper.
*)
fun longest_string_helper opr = List.foldl (fn (x,max) => 
         if opr (String.size(x) , String.size(max)) then x else max) ""
		 
val longest_string3 = longest_string_helper(op >)

val longest_string4 = longest_string_helper(op >=)


(*
5. Write a function longest_capitalized that takes a string list and returns the longest string in
the list that begins with an uppercase letter, or "" if there are no such strings. Assume all strings
have at least 1 character. Use a val-binding and the ML library’s o operator for composing functions.
Resolve ties like in problem 2.
*)
val longest_capitalized = longest_string1 o only_capitals


(*
6. Write a function rev_string that takes a string and returns the string that is the same characters in
reverse order. Use ML’s o operator, the library function rev for reversing lists, and two library functions
in the String module. (Browse the module documentation to find the most useful functions.)
*)
val rev_string = implode o List.rev o explode


(*
7. Write a function first_answer of type (’a -> ’b option) -> ’a list -> ’b (notice the 2 arguments
are curried). The first argument should be applied to elements of the second argument in order
until the first time it returns SOME v for some v and then v is the result of the call to first_answer.
If the first argument returns NONE for all list elements, then first_answer should raise the exception
NoAnswer. Hints: Sample solution is 5 lines and does nothing fancy.
*)
exception NoAnswer

fun first_answer f x =
  case x of
  [] => raise NoAnswer
  | (head::xs) => case f(head) of
                 NONE => first_answer f xs
				 | SOME v => v


				 
(*
8. Write a function all_answers of type (’a -> ’b list option) -> ’a list -> ’b list option
(notice the 2 arguments are curried). The first argument should be applied to elements of the second
argument. If it returns NONE for any element, then the result for all_answers is NONE. Else the
calls to the first argument will have produced SOME lst1, SOME lst2, ... SOME lstn and the result of
all_answers is SOME lst where lst is lst1, lst2, ..., lstn appended together (order doesn’t matter).
Hints: The sample solution is 8 lines. It uses a helper function with an accumulator and uses @. Note
all_answers f [] should evaluate to SOME [].
*)
fun all_answers f x =
    let fun aux(xs, acc) =
	   case xs of
	   [] => SOME acc
	   | head::tail => (case f(head) of
                			       NONE =>  NONE
    							   | SOME v => aux(tail, v @ acc))
    in
	  aux (x,[])
    end
	
	
	
(*
9. (This problem uses the pattern datatype but is not really about pattern-matching.) A function g has
been provided to you.
(a) Use g to define a function count_wildcards that takes a pattern and returns how many Wildcard
patterns it contains.
(b) Use g to define a function count_wild_and_variable_lengths that takes a pattern and returns
the number of Wildcard patterns it contains plus the sum of the string lengths of all the variables
in the variable patterns it contains. (Use String.size. We care only about variable names; the
constructor names are not relevant.)
(c) Use g to define a function count_some_var that takes a string and a pattern (as a pair) and
returns the number of times the string appears as a variable in the pattern. We care only about
variable names; the constructor names are not relevant.
*)
datatype pattern = Wildcard
		 | Variable of string
		 | UnitP
		 | ConstP of int
		 | TupleP of pattern list
		 | ConstructorP of string * pattern

datatype valu = Const of int
	      | Unit
	      | Tuple of valu list
	      | Constructor of string * valu
		  
fun g f1 f2 p =
    let 
	   val r = g f1 f2 
    in
	  case p of
	    Wildcard          => f1 ()
	  | Variable x        => f2 x
	  | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
	  | ConstructorP(_,p) => r p
	  | _                 => 0
    end
	
val count_wildcards = g (fn x => 1) (fn y => 0)

val count_wild_and_variable_lengths = g (fn (_) => 1) (fn x => String.size x)

fun count_some_var (s, p) =
  g (fn (_) => 0) (fn x => if x = s then 1 else 0) p
  
  
 (*
 10. Write a function check_pat that takes a pattern and returns true if and only if all the variables
appearing in the pattern are distinct from each other (i.e., use different strings). The constructor
names are not relevant. Hints: The sample solution uses two helper functions. The first takes a
pattern and returns a list of all the strings it uses for variables. Using foldl with a function that uses
@ is useful in one case. The second takes a list of strings and decides if it has repeats. List.exists may
be useful. Sample solution is 15 lines. These are hints: We are not requiring foldl and List.exists
here, but they make it easier.
 *)
fun check_pat (p) =
    let
        fun variables(p) =
	    case p of
	        Variable x        => [x]
	      | TupleP ps         => List.foldl (fn (v,vs) => vs @ variables(v)) [] ps
	      | ConstructorP(_,p) => variables(p)
	      | _                 => []
        fun repeats sl =
            case sl of
                [] => true
              | x::xs => if List.exists (fn a => a = x) xs then false else repeats(xs)
    in
        repeats(variables(p))
    end
 
(*
11. Write a function match that takes a valu * pattern and returns a (string * valu) list option,
namely NONE if the pattern does not match and SOME lst where lst is the list of bindings if it does.
Note that if the value matches but the pattern has no patterns of the form Variable s, then the result
is SOME []. Hints: Sample solution has one case expression with 7 branches. The branch for tuples
uses all_answers and ListPair.zip. Sample solution is 13 lines. Remember to look above for the
rules for what patterns match what values, and what bindings they produce. These are hints: We are
not requiring all_answers and ListPair.zip here, but they make it easier.
*)

fun match(valu, pat) =
    case (valu, pat) of
         (_, Wildcard)	=> SOME []
		 |(v, Variable s) => SOME [(s,v)]
		 |(Unit , UnitP) =>SOME []
		 |(Const i, ConstP j) => if i=j then SOME [] else NONE
		 |(Tuple vt, TupleP pt) => if List.length vt = List.length pt
								   then all_answers match (ListPair.zip(vt, pt))
								   else NONE
         |(Constructor(sv , vv), ConstructorP(sp , pp)) => if sv=sp then match (vv, pp) else NONE
		 | _ => NONE
(*
12. Write a function first_match that takes a value and a list of patterns and returns a
(string * valu) list option, namely NONE if no pattern in the list matches or SOME lst where
lst is the list of bindings for the first pattern in the list that matches. Use first_answer and a
handle-expression. Hints: Sample solution is 3 lines.
*)		
fun first_match v pl = SOME (first_answer (match) (List.map(fn(x) => (v,x)) pl))
			handle NoAnswer => NONE
  
  
  
(* 
challenge problem
 Write a function typecheck_patterns that “type-checks” a pattern list. Types
for our made-up pattern language are defined by:
datatype typ = Anything (* any type of value is okay *)
| UnitT (* type for Unit *)
| IntT (* type for integers *)
| TupleT of typ list (* tuple types *)
| Datatype of string (* some named datatype *)
typecheck_patterns should have type ((string * string * typ) list) * (pattern list) -> typ option.
The first argument contains elements that look like ("foo","bar",IntT), which means constructor foo
makes a value of type Datatype "bar" given a value of type IntT. Assume list elements all have different
first fields (the constructor name), but there are probably elements with the same second field (the datatype
name). Under the assumptions this list provides, you “type-check” the pattern list to see if there exists
some typ (call it t) that all the patterns in the list can have. If so, return SOME t, else return NONE.
You must return the “most lenient” type that all the patterns can have. For example, given patterns
TupleP[Variable("x"),Variable("y")] and TupleP[Wildcard,Wildcard], return TupleT[Anything,Anything]
even though they could both have type TupleT[IntT,IntT]. As another example, if the only patterns
are TupleP[Wildcard,Wildcard] and TupleP[Wildcard,TupleP[Wildcard,Wildcard]], you must return
TupleT[Anything,TupleT[Anything,Anything]].
*)



(*
(string * string * typ) list can be understood as a statement of datatypes.
eg. [(sa1,sa,ta1),(sa2,sa,ta2),...,(san,sa,tan),...
     (sb1,sb,tb1),(sb2,sb,tb2),...,(sbm,sb,tbm)] match type (string * string * typ) list we can konw
datatype sa = sa1 of ta1 | sa2 of ta2 | ... | san of tan
...
datatype sb = sb1 of tb1 | sb2 of tb2 | ... | sbm of tbm
*)

(*
pattern list can be thought as the pattern of case expression
eg. [ConstructorP("Empty",UnitP),ConstructorP("Sedan", Variable "a"), ConstructorP("Truck", TupleP[Variable "b", Wildcard]), Wildcard,TupleP[Wildcard, TupleP[Wildcard,Wildcard]]] 
we can get to know that
case x of  Empty => p0 Sedan(a) => p1 | Truck(b,_) => p2 | _ => p3 | (_,(_,_)) =>p4
*)

(*
this function tries to match the function contructed by the second parameter (pattern list)
with the  datatype of the first parameter ((string * string * typ) list)
*)

datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string
		
fun typecheck_patterns(sstlist, pl)	=
    let
       fun getDatatype (sstl, s) =   (*s is the elements of constructorP,try to find the corresponding (string * string * typ)*)
           case sstl of
           [] => ""
		   |(s1, s2, _)::xs => if s1 = s then s2
                               else getDatatype(xs, s)
							 
	   fun typecheck p = case p of    (*check the single element*)
	                     Wildcard => Anything         (*Wildcard     :    _ =>...  *)
						 | Variable _ => Anything     (*Variable a   :    a =>...   a is variable name*)
						 | UnitP => UnitT             (*UnitP        :             *)
						 | ConstP _ => IntT           (*ConstP b     :    b =>...    b belongs to int type*)
						 | TupleP [] => TupleT []
						 | TupleP (head::tail) => 
						 (let
						      val type1 = typecheck head
							  val type2 = typecheck ( TupleP tail )
						  in
						      case type2 of
							  TupleT x => TupleT(type1::x)
							 | _ => raise NoAnswer
						  end
 						 )
						 (*TupleP(a,b,...)  :     (a,b,...)=>...  *)
						 | ConstructorP(ps,_) => if getDatatype (sstlist, ps) = "" 
						                         then raise NoAnswer
                                                 else Datatype(getDatatype (sstlist, ps))
	                     (*ConstructorP(s,t) :    s(t) =>... *)
						   						   
	  fun MergeType (t1, t2) = (*Merge the typ pattern*)
          case (t1, t2) of
          (Anything, _) => t2
          | (_, Anything) => t1
		  | (TupleT tt1 ,TupleT tt2) => 
		         (case (tt1,tt2) of
				       ([],[]) => TupleT []
					   |(head1::tail1, head2::tail2) => 
					    (let val mergetype1 = MergeType(head1,head2)
						     val mergetype2 = MergeType(TupleT tail1 , TupleT tail2)
						 in
						     case mergetype2 of
                             TupleT x => TupleT(mergetype1::x)
							 | _ => raise NoAnswer
						 end			
						)
                       |(_,_) => raise NoAnswer		        
		          )
          | (_, _) => if t1 = t2 then t1 else raise NoAnswer	  
	 in 
        (SOME (List.foldl MergeType Anything (List.map typecheck pl))
         handle NoAnswer => NONE )
     end

fun baz f a b c d e = (f (a ^ b))::(c + d)::e
baz : (string->int)->int->int->int->int->int list->int list
f : string -> int
a : string 
b : string 
c : int 
d : int
e : int list