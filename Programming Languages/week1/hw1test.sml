(* Homework1 Simple Test *)
(* These are basic test cases. Passing these tests does not guarantee that your code will pass the actual homework grader *)
(* To run the test, add a new line to the top of this file: use "homeworkname.sml"; *)
(* All the tests should evaluate to true. For example, the REPL should say: val test1 = true : bool *)


val test10 = is_older ((1,2,3),(2,3,4)) = true

val test11 = is_older ((2,3,4),(2,3,4)) = false

val test12 = is_older ((2,3,3),(2,3,4)) = true

val test20 = number_in_month ([(2012,2,28),(2013,12,1)],2) = 1

val test21 = number_in_month ([(2012,2,28),(2013,12,1),(2013,12,1)],5) = 0

val test30 = number_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = 3

val test31 = number_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,4]) = 2

val test40 = dates_in_month ([(2012,2,28),(2013,12,1)],2) = [(2012,2,28)]

val test41 = dates_in_month ([(2012,2,28),(2013,12,1),(2013,2,1)],2) = [(2012,2,28),(2013,2,1)]

val test50 = dates_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4]) = [(2012,2,28),(2011,3,31),(2011,4,28)]

val test51 = dates_in_months ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28),(2011,6,28)],[2,3,4,6]) = [(2012,2,28),(2011,3,31),(2011,4,28),(2011,6,28)]

val test60 = get_nth (["hi", "there", "how", "are", "you"], 2) = "there"

val test61 = get_nth (["hi", "there", "how", "are", "you"], 3) = "how"

val test70 = date_to_string (2013, 6, 1) = "June 1, 2013"

val test71 = date_to_string (2013, 7, 1) = "July 1, 2013"

val test80 = number_before_reaching_sum (10, [1,2,3,4,5]) = 3

val test81 = number_before_reaching_sum (11, [1,2,3,4,5]) = 4

val test90 = what_month 70 = 3

val test91 = what_month 100 = 4

val test100 = month_range (31, 34) = [1,2,2,2]

val test101 = month_range (100, 101) = [4,4]

val test110 = oldest([(2012,2,28),(2011,3,31),(2011,4,28)]) = SOME (2011,3,31)

val test111 = oldest([(2012,2,28),(2011,3,31),(2011,4,28),(2010,4,28)]) = SOME (2010,4,28)

val test120 = number_in_months_challenge ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,2,3,4]) = 3

val test121 = number_in_months_challenge ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,4,2,4]) = 2

val test122 = dates_in_months_challenge ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28)],[2,3,4,2,3,4]) = [(2012,2,28),(2011,3,31),(2011,4,28)]

val test123 = dates_in_months_challenge ([(2012,2,28),(2013,12,1),(2011,3,31),(2011,4,28),(2011,6,28)],[2,3,4,6,2,3,4]) = [(2012,2,28),(2011,3,31),(2011,4,28),(2011,6,28)]

val test130 = reasonable_date((2020,5,20)) = true

val test131 = reasonable_date((2020,5,0)) = false

val test132 = reasonable_date((2020,2,30)) = false

val test133 = reasonable_date((2020,2,29)) = true