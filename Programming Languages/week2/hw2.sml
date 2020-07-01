(* Dan Grossman, Coursera PL, HW2 Provided Code *)
(* Created by mike meng @ 2020.6.3*
   Decription: week2 home work
   Country: Wuhan . China
   Email: mml1106@outlook.com
   Phone: 8617786016228
   Date: 2020.6.5   
*)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

fun append (xs,ys) =
    case xs of
      [] => ys
      | x::xs' => x :: append(xs',ys)

fun has(x : string ,xs : string list) = 
   case xs of
      [] => false
      | y::xs' => if same_string(x,y)
                  then true 
                  else has(x,xs')  
(* put your solutions for problem 1 here *)
(* problem a*,wtrite by mike meng *)
fun all_except_option (x : string, ys : string list) = 
   case ys of
      [] => NONE
      | y::ys' => if not (same_string(x,y))
                  then case all_except_option(x,ys') of 
                        NONE => NONE
                        |SOME e => SOME (y::e)
                  else SOME ys'

(* problem b , modify by mike meng @ 2020.6.5 *)
fun get_substitutions1( xss : string list list, x : string) = 
   case xss of
      [] => []
      | xs::xss' => if has(x,xs)
                     then case  all_except_option(x,xs) of
                        NONE => get_substitutions1(xss',x)
                        | SOME arr => append(arr,get_substitutions1(xss',x))
                     else get_substitutions1(xss',x)

(* problem c , modify by mike meng @ 2020.6.5*)
fun get_substitutions2( xss : string list list, x : string) = 
   let fun helper(xss, xs) = 
      case xss of
         [] => xs
         | ys::xss' => if has(x,ys)
                        then 
                           case all_except_option(x,ys) of
                              NONE => helper(xss',xs)
                              | SOME arr => helper(xss',append(xs,arr))
                        else helper(xss',xs)
   in
      helper(xss,[])
   end
           
(* problem d , modify by mike meng @ 2020.6.5*) 
type fullname = {first : string, 
                 middle : string , 
                 last : string}

fun similar_names(names : string list list , name : fullname) = 
   let 
      val {first = x,middle = y,last = z} = name
      fun helper(xs) = 
         case xs of
            [] => []
            | v::xs' => {first = v,middle = y , last = z}::helper(xs')
   in
      name::helper(get_substitutions1(names,x))
   end
   

(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* put your solutions for problem 2 here *)
(* problem a *)  
fun card_color(c : card) = 
   case c of
      (Spades,_) => Black
      |(Clubs,_) => Black
      |(Diamonds,_) => Red
      |(Hearts,_) => Red

(* problem b *)  
fun card_value(c : card) = 
   case c of
      (_,Ace) => 11
      |(_,Jack) => 10
      |(_,Queen) => 10
      |(_,King) => 10
      |(_,Num e) => e

(* problem c *)  
fun remove_card(cs : card list, c : card, ex) = 
   case cs of
      [] => raise ex
      | x::cs' => if x = c 
                  then cs'
                  else x::remove_card(cs',c,ex)

(* problem d *)  
fun all_same_color(cs : card list) = 
   case cs of 
      [] => true
      | c::[] => true
      | x::(y::rest) => card_color(x) = card_color(y) andalso all_same_color(y::rest)

(* problem e *)
fun sum_cards(cs : card list) =
   let 
      fun helper(cs,sum) = 
         case cs of
            [] => sum
            |c::cs => helper(cs,sum + card_value(c))
   in 
      helper(cs,0)
   end

(* problem f *)
fun score(cs : card list, goal: int) =
   let val sum = sum_cards(cs)
   in
      if all_same_color(cs)
      then 
         if sum > goal
         then (3*(sum-goal)) div 2
         else (goal-sum) div 2
      else 
         if sum > goal
         then 3*(sum-goal)
         else goal-sum
   end

(* problem g *)
fun officiate(cs : card list , step : move list, goal : int) = 
   let          
      fun play(cs : card list , step : move list, hold : card list) = 
         case step of
            [] => hold
            |s::step' => (case s of 
                           Discard e => play(cs,step',remove_card(hold,e,IllegalMove))
                           | Draw => (case cs of
                                    [] => hold
                                    |c::cs' =>  (if sum_cards(c::hold) > goal
                                                then c::hold
                                                else play(cs',step',c::hold))))
   in
      score(play(cs,step,[]),goal)
   end

(* put your solutions for problem 3 here *)
(*challenge  problem 3a*)

(* check wether card is Ace*)
fun is_ace(c : card) = 
   case c of
      (_,Ace) => true
      |_ => false

(* count the number of ace in the card list*)
fun ace_count(lst : card list) = 
   let 
      fun helper(lst, total) = 
         case lst of 
            [] => total
            |c::lst' => if is_ace(c)
                       then helper(lst',total+1)
                       else helper(lst',total)
   in
      helper(lst,0)
   end

(*minum value*)
fun min_value(x : int ,y : int) = 
   if x < y
   then x
   else y

(*change*)
fun best_score(ace_num : int, goal : int, sum : int) =
   if  sum <= goal
   then goal - sum
   else 
        (if ace_num = 0
        then  sum - goal
        else  min_value(sum - goal, best_score(ace_num - 1,goal,sum - 10)))
     

(*score challenge*)
fun score_challenge(cs : card list, goal: int) = 
   if all_same_color(cs)
   then best_score(ace_count(cs),goal,sum_cards(cs)) div 2
   else best_score(ace_count(cs),goal,sum_cards(cs))

(*officiate challenge*)
fun officiate_challenge(cs : card list , step : move list, goal : int) = 
   let          
      fun play(cs : card list , step : move list, hold : card list) = 
         case step of
            [] => hold
            |s::step' => (case s of 
                           Discard e => play(cs,step',remove_card(hold,e,IllegalMove))
                           | Draw => (case cs of
                                    [] => hold
                                    |c::cs' =>  (if (sum_cards(c::hold) - ace_count(c::hold)*10) > goal
                                                then c::hold
                                                else play(cs',step',c::hold))))
   in
      score_challenge(play(cs,step,[]),goal)
   end

(*challenge  problem 3b*)
fun test_zero(cs : card list, goal : int,sum : int ) = 
   case cs of
      [] => NONE
      |c::cs' => if sum - card_value(c) = goal
                 then SOME c
                 else test_zero(cs',goal,sum)

(*fun careful_player(cs : card list,goal : int ) = 
   let 
      fun play(remain : card list, hold : card list , step : move list) = 
         sum = sum_cards(hold)
         in
            case remain of 
            [] => step
            | x::remain' => if goal - sum > 10 orelse sum + card_value(x) <= goal
                           then play(remain', x::hold , Draw::step)
                           else case test_zero(hold,goal,sum + card_value(x)) of
                                 NONE => Discard()
         end
   in
      play(cs,[],[])
   end*)

(*careful_player() = *)
