#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD1 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////

;Ex1:

(define min
  (lambda (a b)
    (if (> a b) b a)))

(define max
  (lambda (a b)
    (if (>= a b) a b)))

(define median
  (lambda (a b c)
    (min (max a b) (max b c))))

(define triangle?
  (lambda (a b c)
    (and (not (or (= a 0)  (= b 0) (= c 0))))))

(define equilateral?
  (lambda (a b c)
    (and (= a b c))))
    
(define isocele?
  (lambda (a b c)
    (and (not (equilateral? a b c)) (or (= a b) (= b c) (= a c)))))

(define rectangle?
  (lambda (a b c)
    (and (triangle? a b c) (= (sqrt (max a (max b c))) (+ (sqrt (median a b c)) (sqrt (min a (min b c))))))))

;Ex2:

(define majIf
  (lambda (c)
    (if (and (char-alphabetic? c) (char-lower-case? c) (char<? c #\m)) (char-upcase c)  c)))

;Ex3:

(define getChar
  (lambda (s n)
    (if (and (string? s) (> (string-length s) n)) (string-ref s n) (display "Erreur nombre trop grand ou chaine non valide !"))))

;Ex4:

(define hms-vers-s
  (lambda (h m s)
    (+ (* h 3600) (* m 60) s)))

(define hms<?
  (lambda (h1 m1 s1 h2 m2 s2)
    (< (hms-vers-s h1 m1 s1) (hms-vers-s h2 m2 s2))))

;Ex5:

(define voiture?
  (lambda (h r)
    (and (< h 1) (< r 0.80) (< (* h pi (sqrt r)) 1))))

;Ex6:

(define commande
 (lambda (qte prix)
   (let ((prixCom (* qte prix)))
     (cond ((>= prixCom 600) prixCom)
           ((and (<= prixCom 600) (> (+ prixCom (/ (* 10 prixCom) 100)) 600)) 600)
           (else (+ prixCom (/ (* 10 prixCom) 100)))))))


