;Odorico thibault 20144124 groupe B

#lang scheme

;////////////////////////////////////////////////////////////////
;////////////////////////// TP2 /////////////////////////////////
;////////////////////////////////////////////////////////////////

;TP2:

(define LVal '(1 2 3 4 5 6 7 8 9 10 25 50 75 100))
(define Op '(+ * - /))

(define parcours
  (lambda (liste n)
    (if (= n 0)
        (car liste) (parcours (cdr liste) (- n 1)))))

;Ex1

(define make-cible
  (lambda ()
    (+ (random 900) 100)))

(define make-tirage
 (lambda ()
  (cons (parcours LVal (random 14))
        (cons (parcours LVal (random 14))
              (cons (parcours LVal (random 14))
                    (cons (parcours LVal (random 14))
                          (cons (parcours LVal (random 14))
                                (cons (parcours LVal (random 14))
                                      '()))))))))

;Ex2

(define estDans?
  (lambda (liste n)
    (cond ((null? liste) #f )
          ((list? (car liste)) (or (estDans? (car liste) n) (estDans? (cdr liste) n)))
          ((= (car liste) n) #t)
          (else (estDans? (cdr liste) n)))))


(define estDans-non-rec?
  (lambda (n L)
    (cond((null? L) #f)
         ((= n (car L)) #t)
         (else(estDans? n (cdr L))))))

;Ex3

(define estValide?
  (lambda (op x y)
    (cond ((and (eq? '/ op) (= y 0)) #f)
          ((and (>= ((eval op) x y) 0) (integer? ((eval op) x y)))  #t)
          (else #f))))

;Ex4

(define opere
  (lambda (LOp x y)
    (cond ((null? LOp) '())
          ((estValide? (car LOp) x y) (cons ((eval(car LOp)) x y ) (opere (cdr LOp) x y)))
          ((estValide? (car LOp) y x) (cons ((eval(car LOp)) y x ) (opere (cdr LOp) x y)))
          (else (opere (cdr LOp) x y)))))

(define delete-at
  (lambda (k1 k2 lst)
    (cond ((null? lst) '())
          ((zero? k2) (cdr lst))
          ((zero? k1) (delete-at (- k1 1) (- k2 1) (cdr lst)))
          (else (cons (car lst) (delete-at (- k1 1) (- k2 1) (cdr lst)))))))

(define insert-at
  (lambda (newlst k lst)
    (cond ((null? lst) newlst)
          ((zero? k) (append newlst lst))
          (else (cons (car lst) (insert-at newlst (- k 1) (cdr lst)))))))

;Ex5

(define opereWith
  (lambda (LOp k1 k2 L)
    (map (lambda (e) (cons e (delete-at k1 k2 L))) (opere LOp (list-ref L k1) (list-ref L k2)))))

(define genere_plaques_bis
  (lambda (LOp k1 k2 L acc)
    (letrec ((longL (length L)))
      (cond ((or (null? LOp) (null? L) (null? (cdr L))) '())
            ((= k1 (- longL 2)) (append acc (opereWith LOp k1 k2 L)))
            ((= k2 (- longL 1)) (genere_plaques_bis LOp (+ k1 1) (+ k1 2) L (append acc (opereWith LOp k1 k2 L))))
            (else (genere_plaques_bis LOp k1 (+ k2 1) L (append acc (opereWith LOp k1 k2 L))))))))

(define genere_plaques
  (lambda (LOp L)
    (genere_plaques_bis LOp 0 1 L '())))

;Ex6 & Ex8

(define jeu '(4 50 9 2 6 3))

(define genere_sous_plaques
  (lambda (LOp L)
    (cond ((null? L) '())
          (else (append (genere_plaques Op (car L)) (genere_sous_plaques LOp (cdr L)))))))

(define ciblesEstDans
  (lambda (entier-cible plaque)
    (= (car plaque) entier-cible)))


(define ceb-bis
  (lambda (Op plaques entier-cible)
    (cond ((null? (cdar plaques)) "le compte n’est pas bon")
          ((ormap (lambda (L) (ciblesEstDans entier-cible L)) plaques) "le compte est bon") 
          (else (ceb-bis Op (genere_sous_plaques Op plaques) entier-cible)))))

(define ceb
  (lambda (Op jeu entier-cibles)
    (ceb-bis Op (genere_plaques Op jeu)  entier-cibles)))

;Ex7

(define plus-proche
  (lambda (L n p)
    (cond ((null? L) p)
          ((null? (cdr L)) p)
          (( <= (min (abs(- n p))) (min (abs(- n (car L))))) (plus-proche (cdr L) n p))
          (else (plus-proche (cdr L) n (car L))))))

(define approche
  (lambda (L n)
    (if (estDans? L n) n (plus-proche L n (car L)))))


;//////////////////// Contrôle TP2 /////////////////////

(define make-tirage5
 (lambda ()
  (cons (parcours LVal (random 14))
        (cons (parcours LVal (random 14))
              (cons (parcours LVal (random 14))
                    (cons (parcours LVal (random 14))
                          (cons (parcours LVal (random 14))
                                      '())))))))

(define ex3
  (lambda ()
    (make-tirage5)))

(define plEx4 '(9 100 75 3 8)) 

(define ex4
  (lambda ()
    (ceb Op plEx4 288)))


