(*problem 1*)
fun compose_opt f1 f2 = fn a => case (f2 a) of 
                                    NONE => NONE
                                   | SOME b => f1 b

(*problem 2*)
fun do_until f p x =
    if p x 
    then do_until f p (f x)
    else x

(*problem 3*)
fun factorial x = #2 (do_until (fn (x,acc) => (x-1,acc*x))  (fn (x,_) => x > 0) (x,1))

(*problem 4*)
fun fixed_point f = do_until f (fn x => f x <> x)

(*problem 5*)
fun map2 f = fn (a,b) => (f a,f b)

(*problem 6*)
fun app_all f g = fn x => List.foldl (fn (x,y) => y@(f x)) [] (g x)

(*problem 7*)
fun app_all f g = fn x => List.foldr (fn (x,y) => (f x)@y) [] (g x)

(*problem 8*)
fun partition f = fn xs => List.foldr (fn (x,y) => if f x then (x::(#1 y),#2 y) else ((#1 y),x::(#2 y))) ([],[]) xs

(*problem 9*)
fun unfold f x = case f x of 
                    NONE => NONE
                    |(a,b) => a::(unfold f b)

(*problem 10*)
fun factorial x = List.foldl (fn (x,y) => x*y) 1 (unfold (fn n => if n = 0 then NONE else SOME(n, n-1)) x)

(*problem 11*)
fun map f xs = List.foldl (fn (x,acc) => (f x)::acc) [] xs

(*problem 12*)
fun filter f xs = List.foldl (fn (x,acc) => if f x then x::acc else acc) [] xs

(*problem 13*)
fun foldl f init xs = List.foldr f init (List.rev xs)

(*problem 14*)
datatype 'a tree = leaf | node of {value: 'a,left : 'a tree, right : 'a tree}

fun tree_map f tree = case tree of
                 leaf => leaf
                | node {value = v ,left = l, right = r} => node {value = f v ,left = tree_map f l, right = tree_map f r}

fun tree_filter f tree = case tree of
                 leaf => leaf
                | node {value = v ,left = l, right = r} => if f v 
                                                           then node {value = v ,left = tree_filter f l, right = tree_filter f r}
                                                           else leaf

fun tree_fold f acc tree = case tree of 
                            leaf => acc
                           |node {value = v ,left = l, right = r} => f (tree_fold f acc l,v,tree_fold f acc r)
                    