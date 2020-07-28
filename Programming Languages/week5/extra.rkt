#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file
;; Created by mike meng , mml1106@outlook.com
;; Author: mike meng
;; Date: 2020.7.15
;; put your code below
(define ones (lambda () (cons 1 ones)))
;;problem 1
(define (palindromic xs)
    (letrec ([f (lambda (lst1 lst2)
                    (if (or (null? lst1) (null? lst2))
                        null
                        (cons (+ (car lst1) (car lst2)) (f (cdr lst1) (cdr lst2)))))])
    (f xs (reverse xs))))


;;problem 2
(define fibonacci
    (let ([f1 0]
          [f2 1]
          [f3 0])
        (letrec ([f (lambda ()
                    (begin
                        (set! f3 (+ f1 f2))
                        (set! f1 f2)
                        (set! f2 f3)
                        (cons f2 f)))])
         f)))

;;problem 3
(define (stream-until f stream)
    (let ([next (stream)])
        (if (f (car next))
            (stream-until f (cdr next))
            (car next))))

;;problem 4
(define (stream-map f stream)
    (let ([next (stream)])
        (cons (f (car next)) (stream-map f (cdr next)))))

;;problem 5
(define (stream-zip s1 s2)
    (let ([next1 (s1)]
          [next2 (s2)])
        (cons (cons (car next1) (car next2)) (stream-map (cdr next1) (cdr next2)))))

;;problem 7
(define (interleave xs)
    (letrec ([f (lambda (x)
                (let ([next (list-ref xs (remainder x (length xs)))])
                        (begin
                            (list-set xs (remainder x (length xs)) (cdr (next)))
                            (cons (car (next)) (lambda () (f (+ x 1)))))))])
            (lambda () (f 0))))

;;problem 8
(define (pack n stream)
    (letrec ([f (lambda (curr_stream x)
                    (if (= x 0)
                        (cons curr_stream null)
                        (let ([pr (curr_stream)])
                            (cons (car pr) (f (cdr pr) (- x 1))))))])
            (lambda () 
                (let ([next (f stream n)])
                     (cons (take next n) (pack n (last next)))))))

;;problem 9
(define (sqrt-stream n)
    (letrec ([f (lambda (x)
                    (let ([next (/ (+ x (/ n x)) 2.0)])
                         (cons next (lambda () (f next)))))])
            (lambda () (f n))))
                         
;;problem 10
(define (approx-sqrt n e)
    (stream-until (lambda (x) (< (* e 1.0) (abs (- (* n 1.0) (* x x))))) (sqrt-stream n)))

;;problem 11
(define-syntax perform
    (syntax-rules (if unless)
        [(perform e1 if e2) (let ([res e2]) (if res e1 res))]
        [(perform e1 unless e2) (let ([res e2]) (if res res e1))]))
           