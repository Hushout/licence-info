#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD9 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////

;Ex1:

(define square
  (lambda (n)
    (* n n)))

(define test-tree '(1 (2 (3 4) 5) (6 7)))

(define sum-odd-squares
  (lambda (tree)
  (cond ((null? tree) 0)
        ((not (pair? tree))
         (if (odd? tree) (square tree) 0))
        (else (+ (sum-odd-squares (car tree))
                 (sum-odd-squares (cdr tree)))))))

;Ex2:

;(sum-odd-squares (list 1 (list 2 (list 3 4) 5) (list 6 7)))

;Ex3:

(define accumulate
  (lambda (combiner null-value L)
    (if (empty? L) null-value (combiner (car L) (accumulate combiner null-value (cdr L))))))

(define enumerate-tree
  (lambda (tree)
    (cond ((null? tree) '())
          ((list? (car tree)) (enumerate-tree (append (car tree) (enumerate-tree (cdr tree)))))
          (else (cons (car tree) (enumerate-tree (cdr tree)))))))

(define sum-odd-squares2
  (lambda (tree)
    (accumulate + 0 (map square (filter odd? (enumerate-tree tree))))))

;Ex4:

;(sum-odd-squares2 (list 1 (list 2 (list 3 4)) 5))

;(sum-odd-squares2 (list 1 (list 2 (list 3 4) 5) (list 6 7)))

;Ex5:

(define estPair?
  (lambda (n)
    (= (modulo n 2) 0)))

(define squareImp
  (lambda (n)
    (if (not (estPair? n)) (square n) 1)))

(define enumerate-leaf
  (lambda (tree)
    (cond ((null? tree) '())
          ((not (pair? tree)) '())
          ((and (empty? (cdr tree)) (not (pair? (car tree)))) tree)
          (else (append (enumerate-leaf (car tree)) (enumerate-leaf (cdr tree)))))))


(define prod-odd-squares
  (lambda (tree)
    (accumulate * 1 (map squareImp (enumerate-leaf tree)))))

;Ex6:

;1)



