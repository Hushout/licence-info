#lang scheme


;I) Récursivité terminale:

;Ex1:
#|

La recursivité terminale est une recursivité qui permet de ne pas avoir a conserver
les reference des resultar des precedentes recursion en le mettant en paramètre de la fonction.

ce qui permet d'optimiser la memoire consomé par la fonction par rapports a une recursion enveloppée
|#

;Exemple somme entier 1 -> n

;enveloppé:

(define sommeEntier
  (lambda (n)
    (if (= n 0) 0 (+ n (sommeEntier (- n 1))))))

;terminale:

(define sommeEntierTer
  (lambda (n)
    (letrec ((boucle (lambda (n acc)
                       (if (= n 0) acc (boucle (- n 1) (+ n acc))))))
      (boucle n 0))))


;Ex2:

(define count
  (lambda (e L)
    (cond ((null? L) 0)
          ((list? (car L)) (+ (count e (car L)) (count e (cdr L))))
          ((eq? (car L) e) (+ 1 (count e (cdr L))))
          (else (count e (cdr L))))))

;Ex3:

(define countTer
  (lambda (e L)
    (letrec ((boucle (lambda (e L acc)
                       (cond ((null? L) acc)
                             ((list? (car L)) (boucle e (cdr L) (+ (boucle e (car L) 0) acc)))
                             ((eq? (car L) e) (boucle e (cdr L) (+ acc 1)))
                             (else (boucle e (cdr L) acc))))))
      (boucle e L 0))))


;II) Récursivité arborescente:

(define arbre-test '(1 ((2 ((3 ()) (4 ((5 ()) (6 ()))))))))

;Constructeur:

(define make-arbre
  (lambda (e L)
    (cons e L)))

;Accesseur:

(define element
  (lambda (A)
    (car A)))

(define fils
  (lambda (A)
    (cadr A)))

;Prédicats

(define arbre-vide?
  (lambda (A)
    (eq? A '())))

(define feuille?
  (lambda (A)
    (null? (fils A))))

;Ex3:

(define effeuillage
  (lambda (A)
    (cond ((arbre-vide? A) '())
          ((feuille? A) '())
          (else (cons (element A)(list (map effeuillage (fils A))))))))
#|
(define parcoursFils
  (lambda (f fils)
    (cond (
|#

;Ex5:



;Ex7:

(define cube
  (lambda (x)
    (* x x x)))

(define derive
  (lambda (f dx x)
    (/ (- (f (+ x dx)) (f x)) dx)))

;Ex8:

(define (make-rotation a b c d)
  (let ((rot (cons (cons a b) (cons c d))))
    (if (determinant1? rot) rot (display "erreur determinant"))))


(define get-x11
  (lambda (rot)
    (caar rot)))

(define get-x12
  (lambda (rot)
    (cdar rot)))

(define get-x21
  (lambda (rot)
    (cdar rot)))

(define get-x22
  (lambda (rot)
    (cddr rot)))

(define rotation?
  (lambda (rot)
    (and (pair? rot) (pair? (car rot)) (pair? (cdr rot))
         (determinant1? rot))))

(define determinant1?
  (lambda (rot)
    (= (- (* (get-x11 rot) (get-x22 rot)) (get-x12 rot) (get-x21 rot)) 1)))

(define m (make-rotation 1 0 0 1))

;Ex10:

;(voir make-rotation)