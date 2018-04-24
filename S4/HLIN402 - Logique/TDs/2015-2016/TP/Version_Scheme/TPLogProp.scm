;Traduction Lisp --> Scheme
;
;Par Barthélémy Antonin
; &  Choquet Brett
;[MAJ] Implémentation de la gestion de la distributivité du ET et du OU d'une fbf grâce à la fonction X
; Ecrit en "Assez Gros Scheme"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;          Définition d'un type formule bien formée           ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Les define qui suivent permettent d'assurer les tests codés sous Lisp

; On définit eq comme la fonction equal? en scheme
(define eq equal?)

; On définit symbolp comme symbol? en scheme
(define symbolp symbol?)

; On définit listp comme list?
(define listp list?)

; On définit nil comme la liste vide
(define nil '())

; teste si x est un connecteur
(define (conp x)
  (or (eq x 'n) (eq x '&) (eq x 'v) (eq x '->) (eq x '<->)))

;teste si x est un connecteur binaire
(define (con2p x)
  (and (conp x) (not (eq x 'n))))

; teste si x est un et ou un ou
(define (con&v? x)
  (if (or (eq x '&) (eq x 'v)) #t
      #f))


;teste si x est le connecteur neg
(define (negp x)
  (eq x 'n))

; teste si x est une constante propositionnelle (VRAI et FAUX)
(define (constp x)
  (or (eq x 'T) (eq x ())))

; teste si x est un symbole propositionnel
(define (symbp x)
  (and (symbolp x) (not (constp x)) (not (conp x)))) 

; teste si x est une fbf
(define (fbfp p)
; definition d'une fonction qui permet la disributivité du & et du v et pas celle du <-> et ->
  (define (X p1)
    (cond
      ((eq p1 '()) #t)
      ((not (eq '() p1)) (and (fbfp (car p1)) (X (cdr p1))))
    )
  )
; (base)
  (cond ((symbp p) #t)
	((constp p) #t)
	((listp p)   ; sinon ce doit être une liste
	 ; (cons)
	 (cond ((and (negp (car p)) (= (length p) 2)) (fbfp (cadr p))) ; R1 : règle du neg (connecteur unaire)
	       ((and (con2p (car p)) (= (length p) 3)) (and (fbfp (cadr p)) (fbfp (caddr p)))); R2 : règle des connecteurs binaires
               ((and (con&v? (car p)) (> (length p) 3)) (X (cdr p)))
               (else  #f)))  ; sinon ce n'est pas une fbf
         (else #f)))


; définition de la formule F1
; à compléter avec F2, F3 et F4

(define F1  '(<-> (& a b) (v (n a) b)))
; (fbf F1) --> t
(define F2 '(v (n (& a (n b))) (n (-> a b))))
; (fbf F2) --> t
(define F3 '(& (n (-> a (v a b))) (n (n (& a (v b (n c)))))))
; (fbf F3) --> t
(define F4 '(& (v (n a) b d) (v c (n d)) (v c a) (v b (n c)) (v (n c) (n b)) (v (n b) d)))
; (fbf F4) --> t

#| Commentaire en Scheme à supprimer pour pouvoir executer le code ci-dessous

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;           Fonctions de manipulation du type fbf             ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; retourne le connecteur racine d'une fbf
(define (conRac f)
  ; à compléter : un simple car fait l'affaire ! 
)

; retourne la sous formule d'une fbf dont le connecteur racine est neg
(define (ssfbf f)
  ; à compléter : un car et un cdr suffisent !
)

; retourne la sous formule gauche d'une fbf dont le connecteur racine est binaire
(define (ssfbfG f)
  ; à compléter...
)

; retourne la sous formule droite d'une fbf dont le connecteur racine est binaire
(define (ssfbfD f)
  ; à compléter...
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;           Fonctions de manipulation du type fbf             ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; retourne le nombre de connecteurs d'une fbf
(define (nbc f)
  ; (base)
  (cond ((symbp f) 0)   ; cas ou F appartient à S
	((constp f) 0)  ; cas ou F appartient à {VRAI,FAUX}
  ; (cons)
	((negp (conRac f)) (+ 1 (nbc (ssfbf f))))          ; cas ou F =  non G
	(else (+ 1 (+ (nbc (ssfbfG f)) (nbc (ssfbfD f)))))))  ; cas ou F = G c H avec c un connecteur binaire

; retourne la profondeur d'une fbf
(define (prof f)
; à compléter...
)

; retourne l'ensemble des symboles propositionnels de f
(define (ensSymbProp f)
; à compléter
)
; pour cette derniere fonction il faut se doter d'un type ensemble : une liste fait l'affaire
; reste à écrire les fonctions
; appartient?, inclus?, union, intersection, difference


|#; Fin de commentaire