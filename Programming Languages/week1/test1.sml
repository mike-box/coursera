(*created by mike meng*)
(*data:2020.5.24*)
fun pow (x:int,y:int) = 
    if y=0
    then 1
    else x*pow(x,y-1)

fun cube (x:int) = 
    pow(x,3)

val ans = cube(3)

val ans1 = cube(100)
