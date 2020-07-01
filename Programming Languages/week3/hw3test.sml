(* Homework3 Simple Test*)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)

val test1 = only_capitals ["A","B","C"] = ["A","B","C"]

val test11 = only_capitals ["A","B","C","a","b","c"] = ["A","B","C"]

val test12 = only_capitals ["A","B","C","a","b","D"] = ["A","B","C","D"]

val test2 = longest_string1 ["A","bc","C","ac"] = "bc"

val test21 = longest_string1 ["aa","bca","C","ac","aaa"] = "bca"

val test3 = longest_string2 ["A","bc","C","ac"] = "ac"

val test31 = longest_string2 ["aa","bca","C","ac","aaa"] = "aaa"

val test4a = longest_string3 ["aa","bca","C","ac","aaa"] = "bca"

val test4b = longest_string4 ["aa","bca","C","ac","aaa"] = "aaa"

val test5 = longest_capitalized ["A","bc","C"] = "A"

val test51 = longest_capitalized ["A","bc","C","Acc"] = "Acc"

val test6 = rev_string "abc" = "cba"

val test7 = first_answer (fn x => if x > 3 then SOME x else NONE) [1,2,3,4,5] = 4

val test8 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [2,3,4,5,6,7] = NONE

val test81 = all_answers (fn x => if x > 2 andalso x < 6 then SOME [x] else NONE) [3,4,5] = SOME [3,4,5]

val test82 = all_answers (fn x => if x = 1 then SOME [x] else NONE) [] = SOME []

val test9a = count_wildcards Wildcard = 1

val test9b = count_wild_and_variable_lengths (Variable("a")) = 1

val test9c = count_some_var ("x", Variable("x")) = 1

val test10 = check_pat (TupleP([Variable("x"),Variable("y")])) = true

val test101 = check_pat (ConstructorP ("hi",TupleP[Variable "x",Variable "x"])) = false

val test102 = check_pat (ConstructorP ("hi",TupleP[Variable "x",ConstructorP ("yo",TupleP[Variable "x",UnitP])])) = false

val test103 = check_pat (ConstructorP ("hi",TupleP[Variable "x",ConstructorP ("yo",TupleP[Variable "x",UnitP])])) = false

val test11 = match (Const(1), UnitP) = NONE

val test110 = match (Constructor ("egg",Const 4),ConstructorP ("egg",ConstP 4)) = SOME []

val test12 = first_match Unit [UnitP] = SOME []

