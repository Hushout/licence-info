#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD4 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////



;Ex1:

(define somme-carres 
  (lambda (n)
    (if (= n 0) 0 ( + (* n n) (somme-carres (- n 1))))))

;Ex2:

(define puissance
  (lambda (n k)
    (if (= k 0) 1 (* n (puissance n (- k 1))))))


;Ex3:

;1)

(define somme-prix
  (lambda (n)
    (if (= n 0) 0 (+ (puissance (- n 1) 2) (somme-prix (- n 1))))))

;2)

(define gain-jour
  (lambda (n)
    (abs (- 300000 (somme-prix n)))))

;Ex4:

(define sommechiffre
  (lambda (n)
    (cond ((= n 0) 0)
          (else (+ (- n (* (round(/ n 10)) 10)) (sommechiffre (round (/ n 10))))))))

;Ex5:

(define avec?
  (lambda (c x)
    (cond ((= x c) #t)
          ((= x 0) #f)
          (else (or (= c (- x (* (round(/ x 10)) 10))) (avec? c (round (/ x 10))))))))
;Ex6:

(define puissancemax-bis
  (lambda (p pbase m)
    (if (> (* p pbase) m) p (puissancemax-bis (* p pbase) pbase  m))))

(define puissancemax
  (lambda (p m)
    (puissancemax-bis p p m)))

;Ex7:

(define nb->multdix
  (lambda (n)
    (if (= n 0) 1 (* 10 (nb->multdix (floor (/ n 10)))))))

(define chiffrescroissants
  (lambda (n)
    (cond ((= n 0) 0)
          (else (+ n (* (chiffrescroissants (- n 1)) (nb->multdix n)))))))

