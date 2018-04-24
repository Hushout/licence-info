;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;          Définition d'un type formule bien formée           ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; teste si x est un connecteur
(defun conp (x)
  (or (eq x 'n) (eq x '&) (eq x 'v) (eq x '->) (eq x '<->)))

;teste si x est un connecteur binaire
(defun con2p (x)
  (and (conp x) (not (eq x 'n))))

;teste si x est le connecteur neg
(defun negp (x)
  (eq x 'n))

; teste si x est une constante propositionnelle (VRAI et FAUX)
(defun constp (x)
  (or (eq x 'T) (eq x ())))

; teste si x est un symbole propositionnel
(defun symbp (x)
  (and (symbolp x) (not (constp x)) (not (conp x)))) 

; teste si x est une fbf
(defun fbfp (p)
  ; (base)
  (cond ((symbp p) t)
	((constp p) t)
	((listp p)   ; sinon ce doit être une liste
	 ; (cons)
	 (cond ((and (negp (car p)) (= (length p) 2)) (fbfp (cadr p))) ; R1 : règle du neg (connecteur unaire)
	       ((and (con2p (car p)) (= (length p) 3)) (and (fbfp (cadr p)) (fbfp (caddr p)))) ; R2 : règle des connecteurs binaires
	       (t nil)))  ; sinon ce n'est pas une fbf
	(t nil)))  

; définition de la formule F1
(defvar F1  '(<-> (& a b) (v (n a) b)))
; (fbf F1) --> t
; à compléter avec F2, F3 et F4


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;           Fonctions de manipulation du type fbf             ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; retourne le connecteur racine d'une fbf
(defun conRac (f)
  ; à compléter : un simple car fait l'affaire ! 
)

; retourne la sous formule d'une fbf dont le connecteur racine est neg
(defun ssfbf (f)
  ; à compléter : un car et un cdr suffisent !
)

; retourne la sous formule gauche d'une fbf dont le connecteur racine est binaire
(defun ssfbfG (f)
  ; à compléter...
)

; retourne la sous formule droite d'une fbf dont le connecteur racine est binaire
(defun ssfbfD (f)
  ; à compléter...
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;           Fonctions de manipulation du type fbf             ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; retourne le nombre de connecteurs d'une fbf
(defun nbc (f)
  ; (base)
  (cond ((symbp f) 0)   ; cas ou F appartient a S
	((constp f) 0)  ; cas ou F appartient à {VRAI,FAUX}
  ; (cons)
	((negp (conRac f)) (+ 1 (nbc (ssfbf f))))          ; cas ou F =  non G
	(t (+ 1 (+ (nbc (ssfbfG f)) (nbc (ssfbfD f)))))))  ; cas ou F = G c H avec c un connecteur binaire

; retourne la profondeur d'une fbf
(defun prof (f)
; à compléter...
)

; retourne l'ensemble des symboles propositionnels de f
(defun ensSymbProp (f)
; à compléter
)
; pour cette derniere fonction il faut se doter d'un type ensemble : une liste fait l'affaire
; reste à écrire les fonctions
; appartient?, inclus?, union, intersection, difference
