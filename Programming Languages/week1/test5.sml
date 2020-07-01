(*created by mike meng*)
fun append_element( x : int list , y : int) = 
    if null x
    then [y]
    else (hd x)::append_element((tl x),y)

fun count_from(x : int) =
    let 
        fun count(from : int , to : int) = 
            if from = to
            then [to]
            else from::count(from + 1,to)
    in
        count(1,x)
    end

fun good_max(x : int list) = 
    if null x
    then 0
    else 
        if null (tl x)
        then hd x
        else
            let val curr = good_max(tl x)
            in
                if curr <= (hd x)
                then hd x
                else curr
            end

