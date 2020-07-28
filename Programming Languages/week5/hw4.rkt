#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file
;; Created by mike meng , mml1106@outlook.com
;; Author: mike meng
;; Date: 2020.7.10
;; put your code below
(require racket/trace)
;;problem 1
(define (sequence low high stride)
    (if (> low high)
        null
        (cons low (sequence (+ low stride) high stride))))

;;problem 2
(define (string-append-map xs suffix)
    (map (lambda (str) (string-append str suffix)) xs))

;;problem 3
(define (list-nth-mod xs n)
    (cond [(< n 0) (error "list-nth-mod: negative number")]
          [(null? xs) (error "list-nth-mod: empty list")]
          [#t (car (list-tail xs (remainder n (length xs))))]))

;;problem 4
(define (stream-for-n-steps stream n)
    (if (= n 0)
        null
        (let ([next (stream)])
            (cons (car next) (stream-for-n-steps (cdr next) (- n 1))))))

;;proble 5
(define funny-number-stream
  (letrec ([f (lambda (x) 
                (if (= (remainder x 5) 0) 
                    (cons (* x -1) (lambda () (f (+ x 1))))
                    (cons x (lambda () (f (+ x 1))))))])
    (lambda () (f 1))))

;;problem 6
(define dan-then-dog
    (letrec ([f (lambda (x)  
                (if (= x 1) 
                    (cons "dan.jpg" (lambda () (f 0)))
                    (cons "dog.jpg" (lambda () (f 1)))))]) 
    (lambda () (f 1))))

;;problem 7
(define (stream-add-zero stream)
    (lambda ()
        (let ([pr (stream)])
            (cons (cons 0 (car pr)) (stream-add-zero (cdr pr))))))

;;problem 8
(define (cycle-lists xs ys)
    (letrec ([f (lambda (n) 
                (cons (cons (car (list-tail xs (remainder n (length xs)))) 
                            (car (list-tail ys (remainder n (length ys))))) 
                      (lambda () (f (+ n 1)))))])
    (lambda () (f 0))))

;;problem 9
(define (vector-assoc v vec)
    (letrec ([f (lambda (x) 
                (if (< x (vector-length vec))
                    (let ([val (vector-ref vec x)])
                        (if (and (cons? val) (equal? v (car val)))
                            val
                            (f (+ x 1))))
                    #f))])
    (f 0)))
                
;;problem 10
(define (cached-assoc xs n)
    (letrec ([memo (make-vector n #f)]
             [index 0])
    (lambda (x)
        (let ([ans (vector-assoc x memo)])
            (if ans
                ans 
                (let ([new-ans (assoc x xs)])
                        (begin
                            (vector-set! memo index new-ans)
                            (set! index (remainder (+ index 1) (vector-length memo)))
                            new-ans)))))))
              
;;problem 11
(define-syntax while-less
    (syntax-rules (do)
        [(while-less e1 do e2)
            (let ([target e1])
                (letrec ([f (lambda ()
                            (let ([res e2])
                              (if (and (number? res) (< res target) )
                                (f)
                                #t)))])
                 (f)))]))
            