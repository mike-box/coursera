(*created by mike meng @ 2020.5.24*)
(*question 1*)
fun is_older(x : (int * int * int) , y : (int * int * int)) = 
    if (#1 x) < (#1 y)
    then true
    else 
        if (#1 x) > (#1 y)
        then false
        else 
            if (#2 x) < (#2 y)
            then true
            else 
                if (#2 x) > (#2 y)
                then false
                else
                    if (#3 x) < (#3 y)
                    then true
                    else false

(*question 2*)
fun number_in_month(dates : (int * int * int) list, month : int) = 
    if null dates
    then 0
    else 
        if #2 (hd dates) = month
        then 1 + number_in_month(tl dates,month)
        else number_in_month(tl dates,month)

(*question 3*)
fun number_in_months(dates : (int * int * int) list, months : int list) = 
    if null months
    then 0
    else number_in_month(dates, hd months) + number_in_months(dates,tl months)    

(*question 4*)
fun dates_in_month(dates : (int * int * int) list, month : int) = 
    if null dates
    then []
    else 
        if #2 (hd dates) = month
        then (hd dates)::dates_in_month(tl dates,month)
        else dates_in_month(tl dates,month)

(*question 5*)
fun append(xs : (int * int * int) list, ys : (int * int * int) list) = (* part of the course logo :) *)
    if null xs
    then ys
    else hd(xs) :: append(tl(xs), ys)

fun dates_in_months(dates : (int * int * int) list, months : int list) = 
    if null months
    then []
    else append(dates_in_month(dates,hd months),dates_in_months(dates,tl months))

(*question 6*)
fun get_nth(x : string list, n : int) = 
    if n = 1
    then hd x
    else get_nth(tl x, n - 1)

(*question 7*)        
fun date_to_string(date : int*int*int) = 
    let 
        val months = ["January", "February", "March", "April","May", "June", "July", "August", "September", "October", "November", "December"]
    in
        get_nth(months,#2 date)^" "^Int.toString(#3 date)^", "^Int.toString(#1 date)
    end

(*question 8*)
fun number_before_reaching_sum(n : int , x : int list) = 
    if n <= (hd x)
    then 0
    else 1 + number_before_reaching_sum(n - (hd x),tl x)

(*question 9*)
fun count_month(months: int list,days : int) = 
    if days <= (hd months)
    then 1
    else 1 + count_month(tl months, days - (hd months))

fun what_month(n : int) = 
    let 
        val months = [31,28,31,30,31,30,31,31,30,31,30,31]
    in
        count_month(months,n)
    end

(*question 10*)
fun month_range(day1 : int ,day2 : int) = 
    if day1 > day2
    then []
    else  what_month(day1)::month_range(day1+1,day2)
        
(*question 11*)
fun oldest(days : (int * int * int) list) = 
    if null days
    then NONE
    else
        let 
            val oldest_day = oldest(tl days)
        in
            if isSome oldest_day andalso is_older(valOf oldest_day,hd days)
            then oldest_day
            else SOME (hd days)
        end

(*question 12*)
fun check_exsit(x : int list, n : int) = 
    if null x
    then false
    else 
        if hd x = n
        then true
        else check_exsit(tl x,n)

fun remove_duplicates(x : int list) = 
    if null x
    then []
    else 
        let 
            val rest = remove_duplicates(tl x)
        in
            if check_exsit(rest,hd x)
            then rest
            else (hd x)::rest
        end

fun number_in_months_challenge(dates : (int * int * int) list, months : int list) = 
    if null months
    then 0
    else
        let 
            val rest_months = remove_duplicates(months)
        in
            number_in_months(dates,rest_months)
        end  

fun dates_in_months_challenge(dates : (int * int * int) list, months : int list) = 
    if null months
    then []
    else
        let 
            val rest_months = remove_duplicates(months)
        in
            dates_in_months(dates,rest_months)
        end  
        

(*question 13*)
fun is_leap_year(x : int ) = 
    if (x mod 400) = 0 orelse ((x mod 4) = 0 andalso (x mod 100) > 0)
    then true
    else false

fun get_day_of_month(days : int list, month : int ) = 
    if month = 1
    then hd days
    else get_day_of_month(tl days,month - 1)

fun check_day_of_month(maxday : int , n : int) = 
    if n <= 0 orelse n > maxday
    then false
    else true

fun reasonable_date(date : int * int * int) = 
    if (#1 date) <= 0 orelse (#2 date) <= 0 orelse (#3 date) <= 0 orelse (#2 date) > 12
    then false
    else
        let 
            val months1 = [31,28,31,30,31,30,31,31,30,31,30,31]
            val months2 = [31,29,31,30,31,30,31,31,30,31,30,31]
        in
            if is_leap_year(#1 date)
            then check_day_of_month(get_day_of_month(months2,#2 date),#3 date)
            else check_day_of_month(get_day_of_month(months1,#2 date),#3 date)
        end
    