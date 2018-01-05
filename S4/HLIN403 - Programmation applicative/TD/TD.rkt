#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////////// Annexe //////////////////////////////////
;/////////////////////////////////////////////////////////////////////////////


(define binList->number-add
  (lambda (L taille add)
    (if (= taille 0)
        add
        (binList->number-add (cdr L) (- taille 1) (+ add (* (car L) (puiss 2 (- taille 1))))))))

(define binList->number
  (lambda (L)
    (binList->number-add L (length L) 0)))

(define number->binList
  (lambda (n)
    (if (or (= n 1) (= n 0)) (list n) (append (number->binList (floor (/ n 2))) (list (modulo n 2))))))

(define addZeros
  (lambda (nb L)
    (if (= 0 nb) L (cons 0 (addZeros (- nb 1) L)))))

(define bin-format
  (lambda (bin binLength bitNumber)
    (cond ((= bitNumber binLength) bin)
          ((> bitNumber binLength) (addZeros (- bitNumber binLength) bin))
          (else (bin-format (cdr bin) (- binLength 1) bitNumber)))))

(define plusUnBin
  (lambda (L)
    (letrec ((longueurL (length L))
             (bin (number->binList (+ (binList->number-add L longueurL 0) 1))))
      (bin-format bin (length bin) longueurL))))

;Transforme (a b c) (0 1 0) -> ((a . 0) (b . 1) (c . 0))

(define queDesUn?
  (lambda (L)
    (andmap (lambda (n) (= n 1)) L)))

(define toutAZero
  (lambda (L)
    (map (lambda (n) 0) L)))

(define bin->int
  (lambda (LS LB)
    (map cons LS LB)))

(define ensInt-bin
  (lambda (LS LB)
    (if (queDesUn? LB) (list (bin->int LS LB)) (append (list (bin->int LS LB)) (ensInt-bin LS (plusUnBin LB))))))

(define ensInt
  (lambda (L)
    (ensInt-bin L (toutAZero L))))

(define testInt
  (lambda (L)
    (if (ensInt L) #t #f))) 