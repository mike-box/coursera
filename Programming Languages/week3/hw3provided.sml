(* Coursera Programming Languages, Homework 3, Provided Code *)
(* Dan Grossman, Coursera PL, HW2 Provided Code *)
(* Created by mike meng @ 2020.6.13*
   Decription: week3 home work
   Country: Wuhan . China
   Email: mml1106@outlook.com
   Phone: 8617786016228
   Date: 2020.6.13   
*)
exception NoAnswer

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

(*problem 1*)
fun only_capitals xs = List.filter (fn x => Char.isUpper(String.sub(x,0))) xs

(*problem 2*)
fun longest_string1 xs = List.foldl (fn (x,y) => if String.size x > String.size y then x else y) "" xs

(*problem 3*)
fun longest_string2 xs = List.foldl (fn (x,y) => if String.size x >= String.size y then x else y) "" xs

(*problem 4*)
fun longest_string_helper f = fn xs => List.foldl (fn (x,y) => if f(String.size x,String.size y) then x else y) "" xs
val longest_string3 = longest_string_helper (fn (x,y) => x > y)
val longest_string4 = longest_string_helper (fn (x,y) => x >= y)

(*problem 5*)
fun longest_capitalized xs = List.foldl (fn (x,y) => if String.size x > String.size y andalso Char.isUpper(String.sub(x,0)) 
														then x 
														else y) "" xs
(*problem 6*)
fun rev_string x = String.implode(List.rev(String.explode x))

(*problem 7*)
fun first_answer f xs = case xs of 
						  []     => raise NoAnswer
						| x::xs' => case f(x) of
									 NONE   => first_answer f xs'
									|SOME e => e

(*problem 8*)
fun all_answers f xs = case xs of 
						  []     => SOME []
						| x::[]  => f(x)
						| x::xs' => case f(x) of
										  NONE   => NONE
										| SOME e => case (all_answers f xs') of 
														 NONE   => NONE
														|SOME f => SOME (e@f)
(*problem 9*)				
val count_wildcards = g (fn _ => 1) ( fn _ => 0) 
val count_wild_and_variable_lengths = g (fn _ => 1) ( fn x => String.size x) 
fun count_some_var(x : string , p : pattern) = g (fn _ => 0) (fn y => if x = y then 1 else 0) p 
									
(*problem 10*)
fun check_pat p = 
	let 
		fun unique xs = 
			case xs of 
				  []     => true
				| x::[]  => true
				| x::xs' => (not (List.exists (fn y => y = x) xs')) andalso unique(xs')
		
		fun get_pat(p : pattern) = 
			case p of 
				  Variable x          => [x]
	  			| TupleP ps   		  => List.foldl (fn (p,lst) => get_pat(p)@lst) [] ps
				| ConstructorP(_,pat) => get_pat(pat)
				| _ => []
	in
		unique(get_pat(p))
	end

(*problem 11*)
fun match(v : valu, p : pattern) = 
	case (v,p) of
		 (_,Wildcard)         => SOME []
		|(_,Variable x)       => SOME [(x,v)]
		|(Unit,UnitP)         => SOME []
		|(Const y,ConstP x)   => if x = y then SOME [] else NONE
		|(Tuple vs,TupleP ps) => if (List.length ps) = (List.length vs) 
								 then all_answers match (ListPair.zip(vs,ps))
								 else NONE 
		|(Constructor(s2,v2),ConstructorP(s1,p1)) => if  s1 = s2 then match(v2,p1) else NONE
		| _                   => NONE

(*problem 12*)
fun first_match v ps = SOME (first_answer (fn p => match(v,p)) ps)
					   handle NoAnswer => NONE

(**** for the challenge problem only ****)
datatype typ = Anything
	     | UnitT
	     | IntT
	     | TupleT of typ list
	     | Datatype of string

(*
datatype pattern = Wildcard
		 | Variable of string
		 | UnitP
		 | ConstP of int
		 | TupleP of pattern list
		 | ConstructorP of string * pattern*)

(**** you can put all your code here ****)

fun typecheck_patterns(sstlist, patlst) = 
	let 
		fun get_datatype(xs,s) = case xs of
									 [] => ""
									|(s1,s2,_)::xs' => if s1 = s 
														then s2
														else get_datatype(xs',s)

		fun get_datatype_value(xs,s) = case xs of
										 [] => Anything
										|(s1,s2,t)::xs' => if s1 = s 
															then t
															else get_datatype_value(xs',s)

		fun merge_type(t1,t2) = case (t1,t2) of
								(Anything, _)  => t2 
							   |(_, Anything)  => t1 
							   |(UnitT,UnitT)  => t1
							   |(IntT,IntT)    => t1
							   |(TupleT tt1,TupleT tt2) =>  (case (tt1,tt2) of
							   								 ([],[]) => TupleT []
															|(head1::tail1,head2::tail2) => (let
																								val type1 = merge_type(head1,head2)
																								val type2 = merge_type(TupleT tail1,TupleT tail2)
																							in 
																								case type2 of 
																									TupleT x => TupleT(type1::x)
																									| _      => raise NoAnswer
																							end)
															|(_,_) => raise NoAnswer)
															
							   |(Datatype s1,Datatype s2) => (if s1 = s2 
							   								 then t1 
															 else raise NoAnswer)
							   |(_,_) => raise NoAnswer

		fun typecheck(pat) = case pat of 
								Wildcard   => Anything
							   |Variable _ => Anything
							   |UnitP      => UnitT
							   |ConstP _   => IntT
							   |TupleP tl  => (case tl of 
							   					[] => TupleT []
											    | head::tail =>  (let 
																	val type1 = typecheck(head)
																	val type2 = typecheck(TupleP tail)
																 in
																	case type2 of
																		TupleT x => TupleT (type1::x)
																	   | _       => raise NoAnswer
																 end))
							   |ConstructorP(s,t) => (let
															val typename  = get_datatype(sstlist,s)
															val ttype = get_datatype_value(sstlist,s)
															val checktype = merge_type(ttype,typecheck(t))
													  in
													  		if typename = ""
							   					     		then raise NoAnswer
													 		else Datatype(typename)
													 end)
		
	in
		SOME (List.foldl merge_type Anything (List.map typecheck patlst))
			  handle NoAnswer => NONE
	end

