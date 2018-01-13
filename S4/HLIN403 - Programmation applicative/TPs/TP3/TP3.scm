;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname TP3) (read-case-sensitive #t) (teachpacks ((lib "draw.rkt" "teachpack" "htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "draw.rkt" "teachpack" "htdp")) #f)))
;Odorico thibault 20144124 groupe B

;TP3:

;Ex1:

(define make-domino
  (lambda (a b)
    (list a b)))

(define randomino
  (lambda ()
    (make-domino (random 7) (random 7))))

(define fg
  (lambda (dom)
    (car dom)))

(define fd
  (lambda (dom)
    (cadr dom)))

(define jeu-vide '())

(define jeu-vide?
  (lambda (jeu)
    (eq? jeu jeu-vide)))

(define tete-jeu
  (lambda (jeu)
    (car jeu)))

(define queue-jeu
  (lambda (jeu)
    (cdr jeu)))

;Ex2:


(define jeu-test '((1 1) (0 3) (5 2) (3 3) (2 2) (2 3)))

(define chaine-test '((2 3) (3 0) (0 6) (6 6) (6 5) (5 2)))

(define make-jeu
  (lambda ()
    jeu-vide))

(define val-jeu
  (lambda (jeu n)
    (list-ref jeu n)))

;Ex3:

(define est-double?
  (lambda (dom)
    (= (fg dom) (fd dom))))

;Ex4:

(define double-jeu
  (lambda (jeu)
    (cond ((null? jeu) '())
          ((est-double? (car jeu)) (append (list (car jeu)) (double-jeu (cdr jeu))))
          (else (double-jeu (cdr jeu))))))
 
;Ex5:

(define retourner
  (lambda (dom)
    (list (fd dom) (fg dom))))

;Ex6:

(define contient-dom
  (lambda (dom n)
    (or (= (fg dom) n) (= (fd dom) n))))

(define peut-jouer-jeu?
  (lambda (jeu n)
    (cond ((null? jeu) #f)
          ((contient-dom (car jeu) n) #t)
          (else (peut-jouer-jeu? (cdr jeu) n)))))


;Ex7:

(define extraire
  (lambda (n jeu)
    (cond ((null? jeu) '())
          ((contient-dom (car jeu) n) (car jeu))
          (else (extraire n (cdr jeu))))))
    
;Ex8:

(define chaine-valide?
  (lambda (jeu)
    (cond ((null? jeu) #t)
          ((null? (cdr jeu)) #t)
          ((not (= (fd (car jeu)) (fg (cadr jeu)))) #f)
          (else (chaine-valide? (cdr jeu))))))

;Ex9:

(define ex-g
  (lambda (jeu)
    (cond ((null? jeu) '())
          (else (fg (car jeu))))))

(define ex-d
  (lambda (jeu)
    (cond ((null? jeu) '())
          ((null? (cdr jeu)) (fd (car jeu)))
          (else (ex-d (cdr jeu))))))


;Ex10:

(define sont-egaux?
  (lambda (dom1 dom2)
    (or (and (= (fg dom1) (fg dom2)) (= (fd dom1) (fd dom2)))
        (and (= (fg dom1) (fd dom2)) (= (fd dom1) (fg dom2))))))

(define supprimer
  (lambda (dom jeu)
    (cond ((null? dom) jeu)
          ((jeu-vide? jeu) '())
          ((sont-egaux? dom (car jeu)) (cdr jeu))
          (else (append (list (car jeu)) (supprimer dom (cdr jeu)))))))
 
;Ex11:

(define ajout-fin
  (lambda (dom jeu)
    (if (null? jeu) (list dom) (append (list (car jeu)) (ajout-fin dom (cdr jeu))))))

(define ajouter
  (lambda (dom jeu)
    (cond ((null? jeu) (ajout-fin dom jeu))
          ((= (fd dom) (ex-g jeu)) (append (list dom) jeu))
          ((= (fd (retourner dom))  (ex-g jeu)) (append (list (retourner dom)) jeu))
          ((= (fg dom) (ex-d jeu)) (ajout-fin dom jeu))
          ((= (fg (retourner dom))  (ex-d jeu)) (ajout-fin (retourner dom) jeu))
          (else #f))))

          
;Ex12:

;Renvoie vrai si le domino est jouable dans la chaine.
(define domino-jouable?
  (lambda (dom chaine)
    (cond ((null? dom) #f)
          ((null? chaine) #t)
          ((= (fd dom) (ex-g chaine)) #t)
          ((= (fd (retourner dom))  (ex-g chaine)) #t)
          ((= (fg dom) (ex-d chaine)) #t)
          ((= (fg (retourner dom))  (ex-d chaine)) #t)
          (else #f))))

;Renvoie le domino du jeu qui est jouable dans la chaine.
(define domino-jouable
  (lambda (jeu chaine)
    (cond ((jeu-vide? jeu) '())
          ((domino-jouable? (car jeu) chaine) (car jeu))
          (else (domino-jouable (cdr jeu) chaine)))))

;Renvoie un jeu sans l'element qui est jouable dans la chaine.
(define supprimer-jouable
  (lambda (jeu chaine)
    (supprimer (domino-jouable jeu chaine) jeu)))

;Renvoie vrai si un domino du jeu est jouable dans la chaine.
(define peut-jouer?
  (lambda (jeu chaine)
    (cond ((jeu-vide? jeu) #f)
          ((domino-jouable? (car jeu) chaine) #t)
          (else (peut-jouer? (cdr jeu) chaine)))))

(define pose
  (lambda (jeu chaine)
    (cond ((not (peut-jouer? jeu chaine)) (list jeu chaine))
          (else (list (supprimer-jouable jeu chaine) (ajouter (domino-jouable jeu chaine) chaine))))))

;TP3: 4) Partie Graphique

;Selection language niveau avancé, ajout teachpack draw.rkt

;Ex13:

(define dessiner-gros-point
  (lambda (pos)
    (draw-solid-disk pos 2)))

;Ex14:

(define dessiner-rectangle
  (lambda (pos1 pos2)
    (begin (draw-solid-line pos1 (make-posn (posn-x pos2) (posn-y pos1)))
           (draw-solid-line (make-posn (posn-x pos2) (posn-y pos1)) pos2)
           (draw-solid-line pos2 (make-posn (posn-x pos1) (posn-y pos2)))
           (draw-solid-line (make-posn (posn-x pos1) (posn-y pos2)) pos1))))

;Ex15:

(define dessiner-point-2
  (lambda (pos nb)
    (begin (dessiner-gros-point (make-posn (- (posn-x pos) 6) (- (posn-y pos) 6)))
                           (dessiner-gros-point (make-posn (+ (posn-x pos) 6) (+ (posn-y pos) 6))))))


(define dessiner-point-2-inv
  (lambda (pos nb)
    (begin (dessiner-gros-point (make-posn (+ (posn-x pos) 6) (- (posn-y pos) 6)))
                           (dessiner-gros-point (make-posn (- (posn-x pos) 6) (+ (posn-y pos) 6))))))


(define dessiner-point-6
  (lambda (pos nb)
    (begin (dessiner-gros-point (make-posn (- (posn-x pos) 6) (posn-y pos)))
           (dessiner-gros-point (make-posn (+ (posn-x pos) 6) (posn-y pos)))
           (dessiner-point pos 4))))

(define dessiner-point
  (lambda (pos nb)
    (cond ((= nb 1) (dessiner-gros-point pos))
          ((= nb 2) (dessiner-point-2 pos nb))
          ((= nb 3) (begin (dessiner-point pos 1) (dessiner-point pos 2)))
          ((= nb 4) (begin (dessiner-point-2 pos nb) (dessiner-point-2-inv pos nb)))
          ((= nb 5) (begin (dessiner-point pos 1) (dessiner-point pos 4)))
          ((= nb 6) (dessiner-point-6 pos nb))
          (else #f))))

      

(define dessiner-demi-dominos
  (lambda (pos nb)
    (begin (dessiner-rectangle
            (make-posn (- (posn-x pos) 12) (- (posn-y pos) 12))
            (make-posn (+ (posn-x pos) 12) (+ (posn-y pos) 12)))

           (dessiner-point pos nb))))

;Ex16:

(define dessiner-dominos
  (lambda (pos dom)
    (begin (dessiner-demi-dominos (make-posn (- (posn-x pos) 12) (posn-y pos)) (fg dom))
           (dessiner-demi-dominos (make-posn (+ (posn-x pos) 12) (posn-y pos)) (fd dom)))))

;Ex17:

(define dessiner-jeu-dominos-pos
  (lambda (jeu nj pos)
    (cond ((jeu-vide? jeu) 'fin) 
          ((and (< (posn-y pos) (- win-h (* 24 5))) (= nj 1)) (dessiner-jeu-dominos-pos jeu nj (make-posn (+ (posn-x pos) 50) (- win-h 12))))
          ((and (< (posn-y pos) (- win-h (* 24 5))) (= nj 2)) (dessiner-jeu-dominos-pos jeu nj (make-posn (- (posn-x pos) 50) (- win-h 12))))
          ((= nj 1) (begin (dessiner-dominos pos (car jeu))
                           (dessiner-jeu-dominos-pos (cdr jeu) nj (make-posn (posn-x pos) (- (posn-y pos) 24)))))

          ((= nj 2) (begin (dessiner-dominos pos (car jeu))
                           (dessiner-jeu-dominos-pos (cdr jeu) nj (make-posn (posn-x pos) (- (posn-y pos) 24)))))

          (else (display "Erreur : Argument")))))

(define dessiner-jeu-dominos
  (lambda (jeu numJ)
    (cond ((= numJ 1) (dessiner-jeu-dominos-pos jeu 1 (make-posn 24 (- win-h 12))))
          ((= numJ 2) (dessiner-jeu-dominos-pos jeu 2 (make-posn (- win-w 25) (- win-h 12))))
          (else (display "Erreur : Argument")))))

;Ex18:
 
(define dessiner-chaine-dominos-pos
  (lambda (chaine pos)
    (cond ((jeu-vide? chaine) 'fin)
          ((> (posn-x pos) (- win-w 25)) (dessiner-chaine-dominos-pos chaine (make-posn 24 (+ (posn-y pos) 24))))
          (else (begin (dessiner-dominos pos (car chaine))
                       (dessiner-chaine-dominos-pos (cdr chaine) (make-posn (+ (posn-x pos) 50) (posn-y pos)))))))) 
          
(define dessiner-chaine-dominos
  (lambda (chaine)
    (dessiner-chaine-dominos-pos chaine (make-posn 24 12))))

;Ex19:

(define generer-jeu
  (lambda (nbDominos)
    (if (= nbDominos 0) jeu-vide (append (list (randomino)) (generer-jeu (- nbDominos 1))))))

(define initChaine
  (lambda ()
    (list (randomino))))

;Ex20:


(define debut-jeu
  (lambda (nbDominos)
    (list (generer-jeu nbDominos) (generer-jeu nbDominos) (initChaine))))

;Ex21:

(define timeInSec 0.5)

(define affiche-jeu
  (lambda (J1 J2 chaine)
    (begin (clear-all)
           (dessiner-jeu-dominos J1 1)
           (dessiner-jeu-dominos J2 2)
           (dessiner-chaine-dominos chaine))))
 
(define jouer
  (lambda (J1 J2 chaine)
    (letrec ((tour1 (pose J1 chaine)) (tour2 (pose J2 (cadr tour1))))
      (cond ((and (jeu-vide? J1) (jeu-vide? J2)) (display "Egalité !")) 
            ((not (peut-jouer? J1 chaine)) (display "Le joueur 1 a perdu !"))
            ((not (peut-jouer? J2 (cadr tour1))) (begin (affiche-jeu (car tour1) J2 (cadr tour1)) (display "Le joueur 2 a perdu !")))
            (else (begin (affiche-jeu (car tour1) J2 (cadr tour1)) (sleep-for-a-while timeInSec)
                         (affiche-jeu (car tour1) (car tour2) (cadr tour2)) (sleep-for-a-while timeInSec)
                         (jouer  (car tour1) (car tour2) (cadr tour2)))))))) 
     
;Ex22:

;Best:
;349 256

;Default:
;342 256

(define win-w 349)
(define win-h 256)

(define j1 '((1 1) (1 1) (1 1) (1 1) (2 2)))

(define j2 '((1 1) (1 1) (1 1) (1 1) (1 1)))

(define init '((1 1)))

(define jeu-test2 (list j1 j2 init))
 
(define jeu 
  (lambda (x)
    (let ((L (debut-jeu x)))
      (begin (start win-w win-h)
             (affiche-jeu (car L) (cadr L) (caddr L))
             (sleep-for-a-while timeInSec)
             (jouer (car L) (cadr L) (caddr L))))))

;//////////////////// Contrôle TP3 /////////////////////

(define nbEx5 '(0 1 2 3 4 5 6))

(define jeuEx5 '((1 1) (0 1) (3 5) (3 3)))

(define ex5
  (lambda ()
    (begin (if (null? (extraire 0 jeuEx5)) (display "0 Non jouable\n") (display "0 jouable\n"))
           (if (null? (extraire 1 jeuEx5)) (display "1 Non jouable\n") (display "1 jouable\n"))
           (if (null? (extraire 2 jeuEx5)) (display "2 Non jouable\n") (display "2 jouable\n"))
           (if (null? (extraire 3 jeuEx5)) (display "3 Non jouable\n") (display "3 jouable\n"))
           (if (null? (extraire 4 jeuEx5)) (display "4 Non jouable\n") (display "4 jouable\n"))
           (if (null? (extraire 5 jeuEx5)) (display "5 Non jouable\n") (display "5 jouable\n"))
           (if (null? (extraire 6 jeuEx5)) (display "6 Non jouable\n") (display "6 jouable\n")))))



(define enleve-doublons
  (lambda (jeu)
    (cond ((null? jeu) '())
          ((est-double? (car jeu)) (enleve-doublons (cdr jeu)))
          (else (append (list (car jeu)) (enleve-doublons (cdr jeu)))))))

(define ex6
  (lambda ()
    (display (enleve-doublons jeuEx5))))

(define chaineEx7 '((1 2) (2 2) (2 5) (5 6) (6 3)))

(define ex7
  (lambda ()
    (display (cadr (pose jeuEx5 chaineEx7))))) 

(define ex8
  (lambda ()
    (display (generer-jeu 6))))

(define genliste
  (lambda (d f p)
    (cond ((> d f) '())
          (else (cons d (genliste (+ d p) f p))))))


(define make-lancer
  (lambda (a b c)
    (list a b c)))

(define premier
  (lambda (lancer)
    (car lancer)))

(define deuxieme
  (lambda (lancer)
    (cadr lancer)))

(define troisieme
  (lambda (lancer)
    (caddr lancer)))


(define gagnant?
  (lambda (lancer)
    (if (and (= (premier lancer) 4) (= (deuxieme lancer) 2) (= (troisieme lancer) 1)) #t #f)))