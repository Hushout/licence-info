#lang scheme

;TP de Logique 1

;1)Representation des propositions

;Q1:

(define F1 '(<-> (^ a b) (v (! a) b)))

(define F2 '(v (! (^ a (! b))) (! (-> a b))))

(define F3 '(^ (! (-> a (v a b))) (! (! (^ a (v b (! c)))))))

(define F4 '(^ (v (! a) (v b d)) (^ (v (! d) c) (^ (v c a) (^ (v (! c) b) (^ (v (! c) (! b)) (v (! b) d)))))))

;Q2

(define (neg? f) (eq? f '!))
(define (and? f) (eq? f '^))
(define (or? f) (eq? f 'v))
(define (imp? f) (eq? f '->))
(define (equ? f) (eq? f '<->))
(define (top? f) (eq? f 'T))
(define (bot? f) (eq? f 'B))
(define (symbLog? f) (or (top? f) (bot? f) (and? f) (or? f) (neg? f) (imp? f) (equ? f)))
(define (symbProp? f) (and (symbol? f) (not (symbLog? f))))
(define (atomicFbf? f) (or (symbProp? f) (top? f) (bot? f)))
(define (conBin? f) (or (and? f) (or? f) (imp? f) (equ? f)))


(define (fbf? f)
  (cond ((atomicFbf? f) #t)
        ((list? f) (cond ((and (= (length f) 2) (neg? (car f))) (fbf? (cadr f)))
                         ((and (= (length f) 3) (conBin? (car f))) (and (fbf? (cadr f)) (fbf? (caddr f))))
                         (else #f)))
        (else #f)))

;2)Syntaxe des propositions

(define (conRac f) (car f)) ; retourne le connecteur racine d’une fbf non atomique
(define (fils f) (cadr f)) ; retourne le fils d’une fbf dont la racine est un connecteur unaire
(define (filsG f) (cadr f)) ; retourne le fils gauche d’une fbf dont la racine est un connecteur binaire
(define (filsD f) (caddr f)) ; retourne le fils droit d’une fbf dont la racine est un connecteur binaire
(define (negFbf? f) ; teste si une fbf a une négation comme connecteur racine
  (and (not (atomicFbf? f))
       (neg? (conRac f)))) 

;Q3:

(define (nbc f)
  (cond ((atomicFbf? f) 0)
        ((negFbf? f) (+ 1 (nbc (fils f))))
        ((conBin? (conRac f)) (+ 1 (nbc (filsG f)) (nbc (filsD f))))
        (else (display "nbc : mauvais argument"))))

;Q4:

(define (prof f)
  (cond ((atomicFbf? f) 0)
        ((negFbf? f) (+ 1 (prof (fils f))))
        ((conBin? (conRac f)) (+ 1 (max (prof (filsG f)) (prof (filsD f)))))
        (else (display "prof : mauvais argument"))))

;Q5:

(define remove-duplicated
  (lambda (L)
    (if (null? L) '()
        (if (member (car L) (cdr L))
            (remove-duplicated (cdr L))
            (cons (car L) (remove-duplicated (cdr L)))))))

(define ensSP
  (lambda (f)
    (cond ((and (atomicFbf? f) (not (or (top? f) (bot? f)))) (list f))
          ((or (top? f) (bot? f)) '())
          ((negFbf? f) (remove-duplicated (ensSP (fils f))))
          ((conBin? (conRac f)) (remove-duplicated (append (ensSP (filsG f)) (ensSP (filsD f)))))
          (else (display "ensSP: mauvais argument")))))

;Q6:

(define affiche
  (lambda (f)
    (display f)))

;3)Sémantique des propositions

;Q7:

(define I1 (list (cons 'a 1) (cons 'b 0) (cons 'c 1)))

(define I2 (list (cons 'a 0) (cons 'b 0) (cons 'c 0)))

(define I3 (list (cons 'a 1) (cons 'b 1) (cons 'c 1)))

;Q8:

(define intSymb
  (lambda (s I)
    (cond ((null? I) (display "intSymb: Ce symbole propositionel n'est pas défini dans l'interpretation"))
          ((eq? s (caar I)) (cdar I))
          (else (intSymb s (cdr I))))))

;Q9:

(define intNeg
  (lambda (a)
    (if (= a 0) 1 0)))

(define intAnd
  (lambda (a b)
    (if (and (= a 1) (= b 1)) 1 0)))

(define intOr
  (lambda (a b)
    (if (or (= a 1) (= b 1)) 1 0)))

(define intImp
  (lambda (a b)
    (if (or (not (= a 1)) (= b 1)) 1 0)))

(define intEqu
  (lambda (a b)
    (if (and (= (intImp a b) 1) (= (intImp b a) 1)) 1 0)))

(define (intTop)
  1)

(define (intBot)
  0)

;Q10:

(define valV
  (lambda (f I)
    (if (fbf? f)
        (cond ((top? f) (intTop))
              ((bot? f) (intBot))
              ((atomicFbf? f) (intSymb f I))
              ((neg? (conRac f)) (intNeg (valV (fils f) I)))
              ((and? (conRac f)) (intAnd (valV (filsG f) I) (valV (filsD f) I)))
              ((or?  (conRac f)) (intOr  (valV (filsG f) I) (valV (filsD f) I)))
              ((imp? (conRac f)) (intImp (valV (filsG f) I) (valV (filsD f) I)))
              ((equ? (conRac f)) (intEqu (valV (filsG f) I) (valV (filsD f) I)))
              (else (display "valV : cas imprevu")))
        
        (display "valV : formule mal formée"))))

;Q11:

(define modele?
  (lambda (f I)
    (= (valV f I) 1)))

;4)Satisfabilité et validité d'une proposition

;Q12:

(define IPQ (list (list (cons 'p 0) (cons 'q 0))
                  (list (cons 'p 0) (cons 'q 1))
                  (list (cons 'p 1) (cons 'q 0))
                  (list (cons 'p 1) (cons 'q 1))))

;Q13

;number->binList : Converti un nombre <n> en une liste binaire

(define number->binList
  (lambda (n)
    (if (or (= n 1) (= n 0)) (list n) (append (number->binList (floor (/ n 2))) (list (modulo n 2))))))

;addZeros : Ajoute <nb> zeros à une liste <L>

(define addZeros
  (lambda (nb L)
    (if (= 0 nb) L (cons 0 (addZeros (- nb 1) L)))))

;bin-format : Formate une liste binaire <bin> de longueur <binlength> sur un nombre de bits <bitNumber>

(define bin-format
  (lambda (bin binLength bitNumber)
    (cond ((= bitNumber binLength) bin)
          ((> bitNumber binLength) (addZeros (- bitNumber binLength) bin))
          (else (bin-format (cdr bin) (- binLength 1) bitNumber)))))

;number->binListF : Converti un nombre <n> en une liste binaire formatée sur <bitNumber> bits

(define number->binListF
  (lambda (n bitNumber)
    (let ((bin (number->binList n)))
      (bin-format bin (length bin) bitNumber))))

;binToInt : Creer une interpretation à partir d'une liste de symbol prop <LS> et un liste binaire <LBin> de même taille.
;Ex: (binToInt '(a b c) '(0 1 0)) -> ((a . 0) (b . 1) (c . 0))

(define binToInt
  (lambda (LS LBin)
    (map cons LS LBin)))

;ensInt-acc : Associe avec un binToInt l'ensemble des symbol prop <E> avec toutes les Liste binaire crée avec les valeurs <n> à <nMax>
;             formatée sur <nbBit> bits et stock ce resultat dans acc.

(define ensInt-acc
  (lambda (E n nMax nbBit acc)
    (cond ((null? E) '(()))
          ((= n nMax) (append acc (list (binToInt E (number->binListF n nbBit)))))
          (else (ensInt-acc E (+ n 1) nMax nbBit (append acc (list (binToInt E (number->binListF n nbBit)))))))))

;ensInt : Fonction qui génère l'ensemble des interpretations d'un ensemble de symbol <E>, garantie 100% efficace !

(define ensInt
  (lambda (E)
    (let ((l (length E)))
      (ensInt-acc E 0 (- (expt 2 l) 1) l '()))))

;Q14:

(define satisfiable?
  (lambda (fbf)
    (ormap (lambda (I) (modele? fbf I)) (ensInt (ensSP fbf)))))

;Q15:

(define valide?
  (lambda (fbf)
    (andmap (lambda (I) (modele? fbf I)) (ensInt (ensSP fbf)))))

;Q16:

(define insatisfiable?
  (lambda (fbf)
    (null? (filter (lambda (I) (modele? fbf I)) (ensInt (ensSP fbf))))))

;5)Equivalence et consequence logique

;Q17:

(define equivalent1?
  (lambda (fbf1 fbf2)
    (letrec ((ensI1 (ensInt (ensSP fbf1))) (ensI2 (ensInt (ensSP fbf2))))
      (if (= (length (ensSP fbf1)) (length (ensSP fbf2)))
          (andmap eq? (map (lambda (I) (modele? fbf1 I)) ensI1)
                  (map (lambda (I) (modele? fbf2 I)) ensI2)) #f))))

;Q18:

;Creer une nouvelle fbf avec le connecteur ET et deux fbf.

(define consAnd
  (lambda (fbf1 fbf2)
    (list '^ fbf1 fbf2)))

;Creer une nouvelle fbf avec le connecteur NON et une fbf.

(define consNeg
  (lambda (fbf)
    (list '! fbf)))

(define consequence2?
  (lambda (F1 F2)
    (insatisfiable? (consAnd F1 (consNeg F2)))))

;Q19:

(define ensSPallFbf
  (lambda (E)
    (if (null? E) '() (remove-duplicated (append (ensSP (car E)) (ensSPallFbf (cdr E)))))))

;Q20:

(define modeleCommun?
  (lambda (EnsFbf Int)
    (andmap (lambda (fbf) (modele? fbf Int)) EnsFbf)))

;Q21:

(define contradictoire?-int
  (lambda (EnsFbf Int)
    (cond ((null? Int) #t)
          ((modeleCommun? EnsFbf (car Int)) #f)
          (else (contradictoire?-int EnsFbf (cdr Int))))))

(define contradictoire?
  (lambda (EnsFbf)
    (contradictoire?-int EnsFbf (ensInt (ensSPallFbf EnsFbf)))))

;Q22:



;Q23:

(define conjonction
  (lambda (EnsFbf)
    (cond ((null? EnsFbf) '())
          ((null? (cdr EnsFbf)) (car EnsFbf))
          (else (consAnd (car EnsFbf) (conjonction (cdr EnsFbf)))))))

;Q24:

(define consequenceI?
  (lambda (EnsFbf fbf)
    (consequence2? (conjonction EnsFbf) fbf)))

;6)Mise en forme conjonctive

;Q25:

(define oteEqu
  (lambda (f)
    (cond ((atomicFbf? f) f)
          ((negFbf? f) (list (conRac f) (oteEqu (fils f))))
          ((conBin? (conRac f))
           (if (equ? (conRac f))
               (list '^ (list '-> (oteEqu (filsG f)) (oteEqu (filsD f))) (list '-> (oteEqu (filsD f)) (oteEqu (filsG f))))
               (list (conRac f) (oteEqu (filsG f)) (oteEqu (filsD f)))))
          (else (display "Erreur mauvais argument")))))

;Q26:

(define oteImp
  (lambda (f)
    (cond ((atomicFbf? f) f)
          ((negFbf? f) (list (conRac f) (oteImp (fils f))))
          ((conBin? (conRac f))
           (if (imp? (conRac f))
               (list 'v (list '! (oteImp (filsG f))) (oteImp (filsD f)))
               (list (conRac f) (oteImp (filsG f)) (oteImp (filsD f)))))
          (else (display "Erreur mauvais argument")))))

;Q27:

(define oteCste
  (lambda (f)
    (cond ((atomicFbf? f)
           (cond ((top? f) (list 'v (list '! 'p) 'p))
                 ((bot? f) (list '^ (list '! 'p) 'p))
                 (else f)))
          ((negFbf? f) (list (conRac f) (oteCste (fils f))))
          ((conBin? (conRac f)) (list (car f) (oteCste (filsG f)) (oteCste (filsD f))))
          (else (display "Erreur mauvais argument")))))

;Q28:

(define redNeg
  (lambda (f)
    (cond ((atomicFbf? f) f)
          ((negFbf? f)
           (cond ((atomicFbf? (fils f)) (list '! (redNeg (fils f))))
                 ((negFbf? (fils f)) (redNeg (fils (fils f))))
                 ((conBin? (conRac (fils f)))
                  (list (conRac (fils f)) (redNeg (list '! (redNeg (filsG (fils f))))) (redNeg (list '! (redNeg (filsD (fils f)))))))
                 (else (list (redNeg (fils f))))))
          ((conBin? (conRac f)) (list (conRac f) (redNeg (filsG f)) (redNeg (filsD f))))
          (else (display "Erreur mauvais argument")))))

;Q29:

(define consFbfBinaire
  (lambda (s fbf1 fbf2)
    (list s fbf1 fbf2)))

(define distOu
  (lambda (f)
  (cond ((or (symbProp? f) (negFbf? f)) f)
        ((and? (conRac f)) (consFbfBinaire '^ (distOu (filsG f)) (distOu (filsD f))))
        (else (let ((Gprime (distOu (filsG f))) (Hprime (distOu (filsD f))))
                (cond ((and(not(atomicFbf? Gprime)) (and?(conRac Gprime)))
                       (consFbfBinaire '^ (distOu (consFbfBinaire 'v (filsG Gprime) Hprime))
                                       (distOu (consFbfBinaire 'v (filsD Gprime) Hprime))))
                      ((and(not(atomicFbf? Hprime)) (and?(conRac Hprime)))
                       (consFbfBinaire '^ (distOu (consFbfBinaire 'v (filsG Hprime) Gprime))
                                       (distOu (consFbfBinaire 'v (filsD Hprime) Gprime))))
                      (else (consFbfBinaire (conRac f) (distOu Gprime) (distOu Hprime)))))))))
;Q30:

(define formeConj
  (lambda (f)
    (distOu (redNeg (oteCste (oteImp (oteEqu f)))))))

;7)Forme clausale

;Q31:

(define C1 '(^ (^ a (^ (v (! c) a) (v c b))) (^ (v d a) (v d b))))

(define transClause
  (lambda (f)
    (cond ((atomicFbf? f) (list f))
          ((negFbf? f) (list (list (conRac f) (car (transClause (fils f))))))
          ((conBin? (conRac f)) (remove-duplicated (append (transClause (filsG f)) (transClause (filsD f))))))))
;Q32:




