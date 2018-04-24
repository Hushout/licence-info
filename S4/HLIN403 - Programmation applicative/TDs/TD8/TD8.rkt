#lang scheme

;/////////////////////////////////////////////////////////////////////////////
;/////////////////////////////// HLIN403 - TD8 ///////////////////////////////
;/////////////////////////////////////////////////////////////////////////////



(define rendreMonnaie
  (lambda (somme nbSortesPieces valeurPiece)
    (letrec ((rendre (lambda (somme n)
                       (cond ((= somme 0) 1)
                             ((or (< somme 0) (= n 0)) 0)
                             (#t (+ (rendre somme (- n 1)) (rendre (- somme (valeurPiece n)) n)))))))
      (rendre somme nbSortesPieces))))

(define valeurPiecesEuro
  (lambda (piece)
    (cond ((= piece 1) 1)
          ((= piece 2) 2)
          ((= piece 3) 5)
          ((= piece 4) 10)
          ((= piece 5) 20)
          ((= piece 6) 50)
          ((= piece 7) 100)
          ((= piece 8) 200))))

(define rendreEuro
  (lambda (somme)
    (rendreMonnaie somme 8 valeurPiecesEuro)))


;Ex1:

(define rendreMonnaieList
  (lambda (somme nbSortesPieces valeurPiece)
    (letrec ((rendre (lambda (somme n L)
                       (cond ((= somme 0) (list L))
                             ((or (< somme 0) (= n 0)) '())
                             (#t (append (rendre somme (- n 1) L) (rendre (- somme (valeurPiece n)) n (cons (valeurPiece n) L))))))))
      (rendre somme nbSortesPieces '()))))

(define rendreEuroList
  (lambda (somme)
    (rendreMonnaieList somme 8 valeurPiecesEuro)))

;Ex2:

;Les noeuds seront représenter par un liste composé d'un entier et d'un string pour la couleur.

;Ex3:

;//////////////////////// Consante

(define noir #t)
(define rouge #f)

;//////////////////////// Constructeur

(define make-noeud
  (lambda (int col)
    (cons int col)))

;//////////////////////// Accesseurs

(define get-noeud-int
  (lambda (node)
    (car node)))

(define get-noeud-col
  (lambda (node)
    (cdr node)))

;//////////////////////// Predicat

(define noir?
  (lambda (node)
    (get-noeud-col node)))

(define pair?
  (lambda (node)
    (= (modulo (get-noeud-int node) 2) 0)))

(define noeud-test (make-noeud 14 noir))

;Ex4:

;//////////////////////// Consante

(define empty-arn '())

;//////////////////////// Constructeur

(define make-arn
  (lambda (root left right)
    (list root left right)))

;//////////////////////// Accesseurs

(define get-root-arn
  (lambda (arn)
    (car arn)))

(define get-left-arn
  (lambda (arn)
    (cadr arn)))

(define get-right-arn
  (lambda (arn)
    (caddr arn)))

;//////////////////////// Predicats
    
(define empty-arn?
  (lambda (arn)
    (eq? arn empty-arn)))

(define leaf-arn?
  (lambda (arn)
    (and (not (empty-arn? arn)) (empty-arn? (get-left-arn arn)) (empty-arn? (get-right-arn arn)))))

(define arn-test (make-arn (make-noeud 1 noir) (make-noeud 1 noir) (make-noeud 1 noir)))

;Ex4:

(define transform-node
  (lambda (node)
    (let* ((v (get-noeud-int node)) (c (if (even? v) rouge noir))) (make-noeud v c))))

(define pairARN
  (lambda (arn)
    (if (empty-arn? arn) empty-arn
        (make-arn (transform-node (get-root-arn arn)) (pairARN (get-left-arn arn))  (pairARN (get-right-arn arn))))))
#|
(define (monochrome? arn)
  (if (or (empty-arn? arn) (leaf-arn? arn)) #t
      (or (and (not (empty-arn? (get-left-arn arn) (equal? (get-noeud-col (get-root-arn arn)) (get-noeud-col (get-root (get-left-arn arn)))) (monochrome? (get-left-arn arn)))
                    (and (not (empty-arn? (get-right arn) equal? (get-noeud-col (get-root
      

|#