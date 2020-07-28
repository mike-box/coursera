#lang racket

; predefined streams from lecture (also use #4 stream-for-n-steps from HW4 for tests and to see values of streams)
(require rackunit)
(require "hw4.rkt")
(require "extra.rkt")
(provide (all-defined-out))

(define ones (lambda () (cons 1 ones)))
(define nats
  (letrec ([f (lambda (x) (cons x (lambda () (f (+ x 1)))))])
    (lambda () (f 1))))
(define powers-of-two
  (letrec ([f (lambda (x) (cons x (lambda () (f (* x 2)))))])
    (lambda () (f 2))))
(define a 2)
(define evens
  (letrec ([f (lambda (x)  (cons x (lambda () (f (+ x 2)))))])
    (lambda() (f 2))))
(define ahh ; (a, aa, aaa, etc) 
  (letrec ([f (lambda (s)
                (cons (string-append s "a") (lambda () (f (string-append s "a")))))])
    (lambda() (f ""))))
  
; TESTS
   ; #1
   (check-equal? (palindromic (list 1 2 4 8)) (list 9 6 6 9) "Palindromic test 1")
   (check-equal? (palindromic (list 1 2 3 4 5)) (list 6 6 6 6 6) "Palindromic test 2")
   ; #2
   (check-equal? (car (fibonacci)) 0 "Fibonacci test 1")
   (check-equal? (car ((cdr (fibonacci)))) 1 "Fibonacci test 2")
   (check-equal? (car ((cdr ((cdr (fibonacci)))))) 1 "Fibonacci test 3")
   (check-equal? (car ((cdr ((cdr ((cdr (fibonacci)))))))) 2 "Fibonacci test 4")
   (check-equal? (car ((cdr ((cdr ((cdr ((cdr (fibonacci)))))))))) 3 "Fibonacci test 5")
   (check-equal? (car ((cdr((cdr ((cdr ((cdr ((cdr (fibonacci)))))))))))) 5 "Fibonacci test 6")

   ; #3 - counts number of items in stream until f return false
   (check-equal? (stream-until (lambda(x) (<= x 100)) nats) 100 "Stream until test 1")
   (check-equal? (stream-until (lambda(x) (not (equal? x 32))) nats) 31 "Stream until test 2")
   (check-equal? (stream-until (lambda(x) (< x 100)) evens) 49 "Stream until test 3")
   (check-equal? (stream-until (lambda(x) (not (equal? x 32))) powers-of-two) 4 "Stream until test 4")
   ; #4
   (check-equal? (car ((stream-map (lambda(x) (- x)) evens))) -2 "Stream map test 1") ; f makes numbers negative
   (check-equal? (car ((cdr ((stream-map (lambda(x) (- x)) evens))))) -4 "Stream map test 2")
   (check-equal? (car ((cdr ((stream-map (lambda(x) (* x x)) evens))))) 16 "Stream map test 3") ; f squares numbers
   (check-equal? (car ((cdr ((stream-map (lambda(s) (string-append s "b")) ahh))))) "aab" "Stream map test 4")
   ; #5
   (check-equal? (car ((cdr ((stream-zip nats powers-of-two))))) (cons 2 4) "Stream zip test 1")
   (check-equal? (car ((cdr((cdr ((cdr ((cdr ((cdr ((stream-zip ones nats))))))))))))) (cons 1 6) "Stream zip test 2")
   (check-equal? (car ((cdr((cdr ((cdr ((cdr ((cdr ((stream-zip ones powers-of-two))))))))))))) (cons 1 64) "Stream zip test 3")
   ; #6 No code required. HINT: What is the last element of a stream?
   ; NOTE: Remaining tests make use of hw4#4 so make sure that is in the same file
   ; #7
   (check-equal? (stream-for-n-steps (interleave (list ones nats ahh)) 6) '(1 1 "a" 1 2 "aa") "Interleave test 1")
   (check-equal? (stream-for-n-steps (interleave (list ones nats ahh powers-of-two)) 13) '(1 1 "a" 2 1 2 "aa" 4 1 3 "aaa" 8 1) "Interleave test 2")
   ; #8
   (check-equal? (car ((cdr ((pack 3 nats))))) '(4 5 6) "Pack test 1")
   (check-equal? (stream-for-n-steps (pack 3 nats) 5) '((1 2 3) (4 5 6) (7 8 9) (10 11 12) (13 14 15)) "Pack test 2")
   (check-equal? (stream-for-n-steps (pack 2 nats) 15) '((1 2) (3 4) (5 6) (7 8) (9 10) (11 12) (13 14) (15 16) (17 18) (19 20) (21 22) (23 24) (25 26) (27 28) (29 30)) "Pack test 3")
   (check-equal? (stream-for-n-steps (pack 5 ones) 5) '((1 1 1 1 1) (1 1 1 1 1) (1 1 1 1 1) (1 1 1 1 1) (1 1 1 1 1)) "Pack test 4")
   ; SKIPPED 9,10
   ; #11
   (check-equal? (perform (+ 1 1) if (= 3 3)) 2 "Perform test 1")
   (check-equal? (perform (+ 1 1) if (= 3 4)) #f "Perform test 2")
   (check-equal? (perform (+ 1 1) unless (= 3 4)) 2 "Perform test 3")
   (check-equal? (perform (+ 1 1) unless (= 3 3)) #t "Perform test 4")