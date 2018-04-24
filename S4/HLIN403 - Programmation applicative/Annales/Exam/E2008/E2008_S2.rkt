#lang scheme


;Ex1:

#|
(define x 4) ;-> rien mais associe 4 à x
(define y (+ x 2)) ;-> rien mais associe 6 à x
(define f (lambda (x) (let ((y (+ x 1))) (+ x y)))) ;-> rien definie la fonction f(x) |--> x + x 1
(+ x (f 2)) ;-> 9
(and (< x 5) (> y 5)) ;-> #t
;(define x 8) ; -> erreur redefinition de x
y ; -> 6
'(+ 2 (+ x 1)) ; -> (+ 2 (+ x 1))
(define li '(1 2 3)) ; -> rien mais associe (1 2 3) à li
(eq? li '(1 2 3)) ; -> eq? compare les pointeurs mem donc ici le resultat est #f
(cons li (list 4 5)) ; -> ((1 2 3) 4 5)
(append li (list 4 5)) ; -> (1 2 3 4 5)
|#

;Ex2:


;1)

(define compter
  (lambda (symb LSymb)
    (cond ((null? LSymb) 0)
          ((equal? symb (car LSymb)) (+ 1 (compter symb (cdr LSymb))))
          (else (compter symb (cdr LSymb))))))

;2)

(define begaie
  (lambda (LSymb)
    (cond ((null? LSymb) '())
          (else (append (cons (car LSymb) (list (car LSymb))) (begaie (cdr LSymb)))))))

;3)

(define debegaie
  (lambda (LSymb)
    (cond ((null? LSymb) '())
          ((null? (cdr LSymb)) (list (car LSymb)))
          ((equal? (car LSymb) (cadr LSymb)) (debegaie (cdr LSymb)))
          (else (cons (car LSymb) (debegaie (cdr LSymb)))))))

;4)

(define compter-ter
  (lambda (symb LSymb)
    (letrec ((boucle (lambda (symb LSymb acc)
                       (cond ((null? LSymb) acc)
                             ((equal? symb (car LSymb)) (boucle symb (cdr LSymb) (+ acc 1)))
                             (else (boucle symb (cdr LSymb) acc))))))
      (boucle symb LSymb 0))))

;5)

(define begaie-ter
  (lambda (LSymb)
    (letrec ((boucle (lambda (LSymb acc)
                       (cond ((null? LSymb) acc)
                             (else (boucle (cdr LSymb) (append acc (cons (car LSymb) (list (car LSymb))))))))))
      (boucle LSymb '()))))

;Ex3:

;1)

(define pow2
  (lambda (n)
    (if (= 0 n) 1 (* 2 (pow2 (- n 1))))))

;2)

(define iter-pow2
  (lambda (n)
    (letrec ((boucle (lambda (n acc)
                       (if (= 0 n) acc (boucle (- n 1) (* acc 2))))))
      (boucle n 1))))

;3)

(define powerof2?
  (lambda (n)
    (cond ((= n 1) #t)
          ((not (= (remainder n 2) 0)) #f)
          (else (powerof2? (quotient n 2))))))

;4)

(define powerof2?-v2
  (lambda (n)
    (or (and (= (modulo (quotient n 2) 2) 0) (= (remainder n 2) 0)) (= n 1) (= n 2))))

;5)

(define powerof?
  (lambda (n k)
    (or (and (= (modulo (quotient n k) k) 0) (= (remainder n k) 0)) (= n 1) (= n k))))

;Ex4:

;1)

(define make-produit
  (lambda (nom prix)
    (list nom prix)))

(define prod-test (make-produit 'balle 10))

(define nom
  (lambda (produit)
    (car produit)))

(define valeur
  (lambda (produit)
    (cadr produit)))

;2)

;Les deux fonction precendentes peuvent nous servir d'accesseur pour une interface qui nous
;permattra de manipuler des produits de maniere securisé.

;3)

(define Lprod '((voiture 40) (peluche 50) (velo 100) (balle 10) (train 60) (cube 11)(disque 12)))

(define prix
  (lambda (name LProd)
    (cond ((null? LProd) (display "Le produit n'existe pas"))
          ((equal? name (nom (car LProd))) (valeur (car LProd)))
          (else (prix name (cdr LProd))))))

;4)

(define plusCher
  (lambda (lp)
    (letrec ((maxChere (lambda (lp maxP)
                         (cond ((null? lp) maxP)
                               ((>= (valeur (car lp)) (valeur maxP)) (maxChere (cdr lp) (car lp)))
                               (else (maxChere (cdr lp) maxP))))))
      (maxChere lp (list 'prodNulle 0)))))

;5)

(define oteProd
  (lambda (lp prod)
    (cond ((null? lp) '())
          ((equal? (car lp) prod) (cdr lp))
          (else (cons (car lp) (oteProd (cdr lp) prod))))))

(define achatCher
  (lambda (lp s)
    (let ((plusC (plusCher lp)))
      (cond ((null? lp) '())
            ((> (valeur plusC) s) (achatCher (oteProd lp plusC) s))
            ((<= (valeur plusC) s) (cons plusC (achatCher (oteProd lp plusC) s)))))))
            
              