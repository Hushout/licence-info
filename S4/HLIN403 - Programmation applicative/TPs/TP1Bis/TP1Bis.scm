;Odorico thibault 20144124 groupe B

#lang scheme

;TP1 bis:

(require (lib "turtles.ss" "graphics"))

;Ex1:

#|
Soit A0 la longueur du trait au niveau 0
La longueur du trait au niveau 1 =  A0 + A0/3

De maniere generale:

Ai = A(i-1) + A(i-1)/3

donc quand i tend vers l'infini, la longueur du trait Ai tend egalement vers l'infini.
|#

;Ex2:

(define von_koch
  (lambda (prof a)
    (cond ((= prof 0) (draw a))
          (else (begin (von_koch (- prof 1) (/ a 3)) (turn 60)
                       (von_koch (- prof 1) (/ a 3)) (turn -120)
                       (von_koch (- prof 1) (/ a 3)) (turn 60)
                       (von_koch (- prof 1) (/ a 3)))))))

        
;Ex3:

(define prepa-von-koch
  (lambda ()
    (turtles #t)
    (clear)
    (move -400)))

(define prepa-von-koch2
  (lambda ()
    (turtles #t)
    (clear)
    (turn -90)
    (move 400)
    (turn 90)
    (move -200)))

(define von-koch
  (lambda (prof a)
    (prepa-von-koch)
    (von_koch prof a)))

;Ex4:

(define (anim-von-koch n)
  (if (= n 0) (sleep 1) (begin (von-koch n 800) (anim-von-koch (- n 1)))))

;Ex5:

(define von_koch_mod
  (lambda (prof a)
    (cond ((= prof 0) (draw a))
          (else (begin (von_koch_mod (- prof 1) (/ a 3)) (turn 90)
                       (von_koch_mod (- prof 1) (/ a 3)) (turn -90)
                       (von_koch_mod (- prof 1) (/ a 3)) (turn -90)
                       (von_koch_mod (- prof 1) (/ a 3)) (turn 90)
                       (von_koch_mod (- prof 1) (/ a 3)))))))

(define von-koch-mod
  (lambda (prof a)
    (prepa-von-koch)
    (von_koch_mod prof a)))

;Ex6

(define drawBorder1
 (lambda (prof lgr nbc angl)
   (if (> nbc 0) (begin (von_koch prof lgr) (turn angl) (drawBorder1 prof lgr (- nbc 1) angl)) 'fin)))

(define drawBorder2
 (lambda (prof lgr nbc angl)
   (if (> nbc 0) (begin (von_koch_mod prof lgr) (turn angl) (drawBorder2 prof lgr (- nbc 1) angl)) 'fin)))
 
(define von-koch-poly
  (lambda (prof lgr nbc)
    (prepa-von-koch2)
    (if (< nbc 1) (display "Nombre de cotés insufisants")
        (drawBorder1 prof lgr nbc (/ 360 nbc)))))

(define von-koch-mod-poly
  (lambda (prof lgr nbc)
    (prepa-von-koch2)
    (if (< nbc 1) (display "Nombre de cotés insufisants")
        (drawBorder2 prof lgr nbc (/ 360 nbc)))))

;Ex7:

(define accumulate
  (lambda (combiner null-value a b)
    (if (> a b) null-value (combiner a (accumulate combiner null-value (+ a 1) b)))))

;1)

(define fact-accu
  (lambda (n)
    (accumulate * 1 1 n)))
;2)

(define somme-accu
  (lambda (n)
    (accumulate + 0 1 n)))

;3)

(define liste-accu
  (lambda (n)
    (accumulate cons '() 1 n)))

;Ex8:

;1)

(define accumulate-term
  (lambda (combiner null-value term a b)
    (if (> a b) null-value
        (combiner (term a) (accumulate-term combiner null-value term (+ a 1) b)))))
;2)

(define fact-accu2
  (lambda (n)
    (accumulate-term * 1 (lambda (x) x) 1 n)))

(define somme-accu2
  (lambda (n)
    (accumulate-term + 0 (lambda (x) x) 1 n)))

(define liste-accu2
  (lambda (n)
    (accumulate-term cons '() (lambda (x) x) 1 n)))

;3)

(define div-fact
  (lambda (n)
    (/ 1 (fact-accu (- n 1)))))

(define exp-accu
  (lambda (prec)
    (exact->inexact (accumulate-term + 0 div-fact 1 prec))))

;4)

(define impair-ok
  (lambda (n)
    (if (= (modulo n 2) 0) 1 n)))

(define prod-impair
  (lambda (n)
    (accumulate-term * 1 impair-ok 1 n)))

;5)

(define pair-ok
  (lambda (n)
    (if (= (modulo n 2) 0) n 1)))

(define prod-pair
  (lambda (n)
    (accumulate-term * 1 pair-ok 1 n)))

;6)

(define mod3-ok
  (lambda (n)
    (if (= n (modulo 1 3)) n 1)))

(define prod-mod3
  (lambda ()
    (accumulate-term * 1 mod3-ok 1 50)))

;Ex9:

;1)

(define accumulate-term-next
  (lambda (combiner null-value term a next b)
    (if (> a b) null-value
        (combiner (term a) (accumulate-term-next combiner null-value term (next a) next b)))))

;2)

(define fact-accu3
  (lambda (n)
    (accumulate-term-next * 1 (lambda (x) x) 1 (lambda (x) (+ x 1)) n)))

(define somme-accu3
  (lambda (n)
    (accumulate-term-next + 0 (lambda (x) x) 1 (lambda (x) (+ x 1)) n)))

(define liste-accu3
  (lambda (n)
    (accumulate-term-next cons '() (lambda (x) x) 1 (lambda (x) (+ x 1)) n)))

;3)

(define div-som
  (lambda (n)
    (/ 1 n)))

(define oppose-plus-un
  (lambda (n)
    (if (>= n 0) (- 0 (+ n 1)) (+ (abs n) 1))))

(define sommeS
  (lambda (n)
    (exact->inexact (accumulate-term-next + 0 div-som 1 oppose-plus-un n))))

;Ex10:

(define carre
  (lambda (n)
    (* n n)))

(define plus-deux
  (lambda (n)
    (+ n 2)))

(define give-impair
  (lambda (n)
    (if (= (modulo n 2) 0) (+ n 1) n)))

(define carreN/carreN+1
  (lambda (n)
    (/ (carre n) (carre (+ n 1)))))

(define pi-product
  (lambda (prec)
    (exact->inexact(accumulate-term-next * 1 carreN/carreN+1 2 plus-deux prec))))