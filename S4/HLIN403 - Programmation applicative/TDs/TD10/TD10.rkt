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

(define-syntax cons-stream
  (syntax-rules ()
    ((cons-stream x y)
     (cons x (delay y)))))

(define the-empty-stream '())

(define stream-null?
  (lambda (stream)
    (null? stream)))

(define stream-car
  (lambda (stream)
    (car stream)))

(define stream-cdr
  (lambda (stream)
    (force (cdr stream))))

(define stream-ref
  (lambda (S n)
    (if (= n 0) (stream-car S) (stream-ref (stream-cdr S) (- n 1)))))

(define stream-for-each
  (lambda (proc s)
    (if (stream-null? s) 'done (begin (proc (stream-car s)) (stream-for-each proc (stream-cdr s))))))

#|
(define (stream-map op s1 s2)
  (let ((h1 (stream-car s1)) (h2 (stream-car s2)))
    (cons-stream (op h1 h2)
                 (stream-map op (stream-cdr s1) (stream-cdr s2)))))
|#

(define stream-map
  (lambda (proc s)
    (if (stream-null? s)
        the-empty-stream
        (cons-stream (proc (stream-car s)) (stream-map (stream-cdr s))))))

(define (display-unit x)
  (begin (display x) (display " ")))

(define stream-display
  (lambda (s)
    (stream-map display-unit s)))

(define stream1 (cons-stream 1 '(2 3 4 5)))
(define stream2 (cons-stream 6 '(7 8 9 10)))

;1)

(define ones (cons-stream 1 ones))

;2)

(define (add-streams s1 s2)
  (stream-map + s1 s2))

(define (stream-enumerate-interval low high)
  (if (> low high)
      the-empty-stream
      (cons-stream
       low
       (stream-enumerate-interval (+ low 1) high))))

;3)

(define integrers (cons-stream 1 (add-streams ones integrers)))

(define fibs
  (cons-stream 0
               (cons-stream 1
                            (add-streams (stream-cdr fibs) fibs))))

;Ex7:

(define mul-streams
  (lambda (f1 f2)
    (f2)))
