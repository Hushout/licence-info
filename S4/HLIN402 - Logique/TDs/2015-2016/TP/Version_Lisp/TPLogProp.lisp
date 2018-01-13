;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;          D�finition d'un type formule bien form�e           ;
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
	((listp p)   ; sinon ce doit �tre une liste
	 ; (cons)
	 (cond ((and (negp (car p)) (= (length p) 2)) (fbfp (cadr p))) ; R1 : r�gle du neg (connecteur unaire)
	       ((and (con2p (car p)) (= (length p) 3)) (and (fbfp (cadr p)) (fbfp (caddr p)))) ; R2 : r�gle des connecteurs binaires
	       (t nil)))  ; sinon ce n'est pas une fbf
	(t nil)))  

; d�finition de la formule F1
(defvar F1  '(<-> (& a b) (v (n a) b)))
; (fbf F1) --> t
; � compl�ter avec F2, F3 et F4


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                             ;
;           Fonctions de manipulation du type fbf             ;
;                                                             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; retourne le connecteur racine d'une fbf
(defun conRac (f)
  ; � compl�ter : un simple car fait l'affaire ! 
)

; retourne la sous formule d'une fbf dont le connecteur racine est neg
(defun ssfbf (f)
  ; � compl�ter : un car et un cdr suffisent !
)

; retourne la sous formule gauche d'une fbf dont le connecteur racine est binaire
(defun ssfbfG (f)
  ; � compl�ter...
)

; retourne la sous formule droite d'une fbf dont le connecteur racine est binaire
(defun ssfbfD (f)
  ; � compl�ter...
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
	((constp f) 0)  ; cas ou F appartient � {VRAI,FAUX}
  ; (cons)
	((negp (conRac f)) (+ 1 (nbc (ssfbf f))))          ; cas ou F =  non G
	(t (+ 1 (+ (nbc (ssfbfG f)) (nbc (ssfbfD f)))))))  ; cas ou F = G c H avec c un connecteur binaire

; retourne la profondeur d'une fbf
(defun prof (f)
; � compl�ter...
)

; retourne l'ensemble des symboles propositionnels de f
(defun ensSymbProp (f)
; � compl�ter
)
; pour cette derniere fonction il faut se doter d'un type ensemble : une liste fait l'affaire
; reste � �crire les fonctions
; appartient?, inclus?, union, intersection, difference
