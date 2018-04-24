#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD3 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////

;Ex1:

#|
a)
(let ((a 2)
      (b (* 2 2))
      (c 10))
  (* c (- a b))) -> -20

b)
(let ((x 5))
  (* x x)
  (let ((x 10))
    (* x x))) -> 100

c)
(let ((a 2)
      (b (let ((a 3) (b 4))
           (- a b)(+ a b))))
  (* a b)) -> 14
|#

;Ex2:

;((lambda (a b c) (* c (- a b))) 2 (* 2 2) 10)

;Ex3:

(define a 10)

;(let ((x a)) (* 2 x)) -> 20

;(let ((a a)) (* 2 a)) -> 20

;(let ((a (* 2 a))) (* 2 a)) -> 40

;(let ((a (* 2 a)) (b 5) (c (+ 1 a))) (+ a b c)) -> 36

;Ex4:

#|
(let ((a 'b) (b 3))
(display 'a)(display " : ")(display a)(newline)
(display 'b)(display " : ")(display b)(newline)
(let ((a 4) (b a))
(display 'a)(display " : ")(display a)(newline)
(display 'b)(display " : ")(display b)))


l'expression affiche :

a : b
b : 3
a : 4
b : b

|#

;Ex5:

;(define a 10) -> 10

;(let ((a 2) (b a)) (* a b)) -> 20

;(let* ((a 2 (b a))) (* a b)) -> 4

;(let* ((a (* 2 a )) (b 5) (c (+ 1 a))) (+ a b c)) -> 46

;(letrec ((a (* 2 a)) (b 5) (c (+ 1 a))) (+ a b c)) -> Erreur

;(let ((x 5)) (let* ((y (+ x 10)) (z (* x y))) (+ x y z))) -> 95


;Ex6:

;(define a 10) -> 10

;(define (foo x) (* a x)) -> (* 10 x)

;(let ((a 0)) (foo 5)) -> 50

;(define a 100) -> 100

;(let ((a 0)) (foo 5)) -> 500

;((lambda (a) (let ((a 1) (foo (lambda (x) (+ a x)))) (foo a))) 5) -> 6

;((lambda (a) (let* ((a 1) (foo (lambda (x) (+ a x)))) (foo a))) 5) -> 2