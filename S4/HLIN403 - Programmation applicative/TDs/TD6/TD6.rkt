#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD6 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////


;Ex1:

;>(fact 5)
; >(fact 4)
;  >(fact 3)
;   >(fact 2)
;    >(fact 1)
;     >(fact 0)
;     >1
;    >1
;   >2
;  >6
; >24
;>120

;Ex2:

;>(fact-iter 5)
; >(fact 5 1)
;  >(fact 4 5)
;   >(fact 3 20)
;    >(fact 2 60)
;     >(fact 1 120)
;      >(fact 0 120)
;      >120

;Ex3:

(define sum-square-1-n
  (lambda (n)
    (if (= n 0) 0 (+ (* n n) (sum-square-1-n (- n 1))))))

(define sum-square-1-n-iter
  (lambda (n acc)
    (if (= n 0) acc (sum-square-1-n-iter (- n 1) (+ acc (* n n))))))

;Ex4:

(define inverse-rec
  (lambda (L)
    (if (null? L) '() (append (inverse-rec (cdr L)) (list (car L))))))

(define inverse-acc
  (lambda (L acc)
    (if (null? L) acc (inverse-acc (cdr L) (append (list (car L)) acc)))))

;Ex5:

(define sommeListe
  (lambda (L acc)
    (if (null? L) acc (sommeListe (cdr L) (+ acc (car L))))))

;Ex6:

(define sommerangimpair
  (lambda (L acc)
    (cond ((null? L) acc)
          ((null? (cdr L)) (+ acc (car L)))
          (else (sommerangimpair (cddr L) (+ acc (car L)))))))

;Ex7:

(define appartient?
  (lambda (e L)
    (cond ((null? L) #f)
          ((eq? e (car L)) #t )
          (else (appartient? e (cdr L))))))

;Ex8:

(define debut-acc
  (lambda (L n acc)
    (if (or (null? L) (= n 0)) acc (debut-acc (cdr L) (- n 1) (append acc (list (car L)))))))

(define debut
  (lambda (L n)
    (debut-acc L n '())))
