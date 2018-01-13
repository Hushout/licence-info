#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD7 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////



;Ex1:

(define make-complexe
  (lambda (a b)
    (list a b)))

(define pre
  (lambda (C)
    (car C)))

(define pim
  (lambda (C)
    (cadr C)))

(define reel?
  (lambda (C)
    (= ( pim C) 0)))

(define complexe?
  (lambda (C)
    (= (pre C) 0)))

;Ex2:

(define somme-complexe
  (lambda (C1 C2)
    (make-complexe (+ (pre C1) (pre C2)) 
                   (+ (pim C1) (pim C2)))))

(define produit-complexe
  (lambda (C1 C2)
    (make-complexe (- (* (pre C1) (pre C2)) 
                      (* (pim C1) (pim C2)))
                   (+ (* (pim C1) (pre C2))
                      (* (pre C1) (pim C2))))))

(define inverse-complexe
  (lambda (C)
    (make-complexe (/ (pre C) (+ (pre C) (pre C))
                      (* (pim C) (pim C)))
                   (/ (- 0 (pim C)) (+ (* (pre C) (pre C))
                                               (* (pim C) (pim C)))))))

(define divise-complexe
  (lambda (C d)
    (produit-complexe C (inverse-complexe d))))

;Ex3:

(define puiss-complexe
  (lambda (C k)
    (if (= 0 k) 
        (make-complexe 1 0) 
        (if (> k 0) 
            (produit-complexe C (puiss-complexe C (- k 1)))
            (puiss-complexe (inverse-complexe C) (- 0 k))))))
				

;Ex4:

;1)

(define monome
  (lambda (deg coef)
    (if (= deg 0) (list coef) (cons 0 (monome (- deg 1) coef)))))

;2)
	
(define addpoly
  (lambda (p1 p2)
    (cond ((null? p1) p2)
          ((null? p2) p1)
          (else (cons (+ (car p1) (car p2)) 
                      (addpoly (cdr p1) (cdr p2)))))))

;3)

(define multconst
  (lambda (p c)
    (map (lambda (n) (* n c)) p)))

;4)

(define multvar
  (lambda (p)	
    (cons 0 p)))

;5)

(define puiss-add
  (lambda (n k add)
    (if (= 0 k) add (puiss-add n (- k 1) (* add n)))))

(define puiss
  (lambda (n k)
    (puiss-add n k 1)))

(define evalpoly-inc
  (lambda (p v inc)
    (if (null? p) 
        0 
        (+ (* (puiss (car p) inc) v) (evalpoly-inc (cdr p) v (+ inc 1))))))
					
(define evalpoly
  (lambda (p v)
    (if (null? p) 0 (+ (car p) (* v (evalpoly (cdr p) v))))))	

;Ex5:

;1)

(define monome->string
  (lambda (coef deg)
    (cond ((or (= coef 0) (= deg 0)) (number->string coef))
          (else (string-append (number->string coef) "^" (number->string deg))))))

;2)

(define polynome->string
  (lambda (p i)
    (cond ((null? p) "")
          ((null? (cdr p)) (monome->string (car p) i))
          (else (string-append (monome->string (car p) i)
                               " + " (polynome->string (cdr p) (+ i 1)))))))