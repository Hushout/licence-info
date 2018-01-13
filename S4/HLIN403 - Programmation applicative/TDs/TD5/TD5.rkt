#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD5 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////



;Ex1:

;1) non, c'est une paire d'elements.

;2) non, c'est une liste.

;3) non, la liste vide n'est pas une paire.


;Ex2:

;(5 (((6 7 9 'r))) 8 12) -> bon

;(9 (((8 4 5 (4) 25) 3) 7) -> mauvais

;(() ()) -> bon

;(56 'p ('K 6) 8 (() (7 6 2))) -> bon


;Ex3:

;(car (2)) -> 2 & (cdr (2)) -> ()

;(car ()) -> erreur & (cdr ()) -> erreur

;(car ((1 2) 3 4)) -> (1 2) & (cdr ((1 2) 3 4)) -> (3 4)

;(car (() ())) -> () & (cdr (() ())) -> (())

;(car (1 (2 (3 4 5) 6) 7)) -> 1 & (cdr (1 (2 (3 4 5) 6) 7)) -> (2 (3 4 5) 6) 7)

;(car (((8 4) 6 (5 4)) (7 8 9))) -> ((8 4) 6 (5 4)) & (cdr (((8 4) 6 (5 4)) (7 8 9))) -> ((7 8 9))


;Ex4:

;1) erreur

;2) (+ (2 6) 10)

;3) 5

;4) 7

;5) (9)

;6) (5)

;7) ((a b) c d)

;8) (7 e f)

;9) (a b c d)

;10) (a)

;11) (a b c)

;12) nope


;Ex5:

;1) a = (+ (* (+ 2 6) 3) (+ 1 3))

;2) (cdr a) -> ((* (+ 2 6) 3) (+ 1 3))

;3) (cdadr a) -> ((+ 2 6) 3)


;Ex6:

(define premdeux?
  (lambda (e L)
    (if (empty? L) #f 
        (if (equal? (car L) e) #t
            (if (empty? (cdr L)) #f (equal? (cadr L) e))))))


;Ex7:

;(cons '(a b) '(c d)) -> ((a b) c d)

;(list '(a b) '(c d)) -> ((a b) (c d))

;(append '(a b) '(c d)) -> (a b c d)


;Ex8:

;1) (a b 5 a)

;6) 14


;Ex9:

(define longueur
  (lambda (L)
         (if (empty? L) 0 (+ 1 (longueur (cdr L))))))


;Ex10:

(define doubleSans
  (lambda (L)
    (if (empty? L) '() (cons (* (car L) 2) (doubleSans (cdr L))))))

(define doubleAvec
  (lambda (L)
    (map (lambda (n) (* n 2)) L)))