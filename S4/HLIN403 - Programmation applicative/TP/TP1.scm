;Odorico thibault 20144124 groupe B

#lang scheme

;////////////////////////////////////////////////////////////////
;////////////////////////// TP1 /////////////////////////////////
;////////////////////////////////////////////////////////////////

(define (puis2 x)
  (* x x))

(define (puis4 x)
  (puis2 (puis2 x)))

(define (puis x y)
  (if (= y 1) x (* x (puis x (- y 1)))))

(define (fctTest x)
  (cond ((= x 5) 3)
        ((>= x 8) (puis2 x))
        ((= x 6) 'toto)
        ((= x 7) #t)
        (else #f)))

(define (divisible? x y)
  (if (= (modulo x y) 0) #t #f))

;Ex7

(define monabs
  (lambda (x)
    (if (< x 0) (- 0 x) x)))

;Ex8

(define care-div
  (lambda (x y)
    (if (= y 0) (display "Erreur : Div-zero") (/ x y))))

;Ex9

(define signalS
  (lambda (t)
    (cond ((<= t -1) 1)
          ((< t -3) 0)
          ((> t 4) 0)
          ((>= t 2) 2)
          (else 0))))

;Ex10

(define placement
  (lambda (capital taux annee)
    (* capital (puis (+ 1 taux) annee))))

;////////////////////////////////////////////////////////////////
;////////////////////////// Tortue //////////////////////////////
;////////////////////////////////////////////////////////////////

(require (lib "turtles.ss" "graphics"))

;Ex12

(define carreT
  (lambda (lgr)
    (begin
    (turtles #t)
    (clear)
    (draw lgr)
    (turn 90)
    (draw lgr)
    (turn 90)
    (draw lgr)
    (turn 90)
    (draw lgr)
    (turn 90))))

;Ex13

(define hexaT
  (lambda (lgr)
    (begin
    (turtles #t)
    (clear)
    (draw lgr)
    (turn 60)
    (draw lgr)
    (turn 60)
    (draw lgr)
    (turn 60)
    (draw lgr)
    (turn 60)
    (draw lgr)
    (turn 60)
    (draw lgr)
    (turn 60))))

;Ex14

(define TL
  (lambda (lgr angl)
    (begin
    (turtles #t)
    (draw lgr) 
    (turn angl))))

(define drawL
  (lambda (lgr angl nb)
    (if (> nb 0) (begin (TL lgr angl) (drawL lgr angl (- nb 1))) 'Fin)))

(define figT
 (lambda (lgr nbc)
   (begin
   (turtles #t)
   (clear)
    (if (< nbc 1) (display "Nombre de cotés insufisants") (drawL lgr (/ 360 nbc) nbc)))))
    
;Ex15

(define bissextile?
  (lambda (annee)
    (cond ((= (modulo annee 400) 0) #t)
          ((and (= (modulo annee 4) 0) (not (= (modulo annee 100) 0))) #t)
          (else #f))))
;Ex16

(define nb-annees-bissextiles
  (lambda (annee)
    (cond ((and (bissextile? annee) (> annee 1900)) (+ 1 (nb-annees-bissextiles (- annee 1))))
          ((> annee 1900) (nb-annees-bissextiles (- annee 1)))
          (else 0))))
            
;Ex17

(define estPair
  (lambda (n)
    (if (= (modulo n 2) 0) #t #f)))

(define nb-jours-mois
  (lambda (n bissex)
    (cond ((and bissex (= n 2)) 29)
          ((and (not bissex) (= n 2)) 28)
          ((and (> n 7) (estPair n)) 31)
          ((and (> n 7) (not (estPair n))) 30)
          ((estPair n) 30)
          (else 31))))

(define nb-jours-au-1-jan
  (lambda (mois bissex)
    (cond ((= mois 1) 0)
          ((+ (nb-jours-mois (- mois 1) bissex) (nb-jours-au-1-jan (- mois 1) bissex))))))

;Ex18

(define nb-jours
  (lambda(x y z)
    (cond ((> z 1900) (+ (- x 1) (nb-jours-au-1-jan y (bissextile? z))  (nb-jours 1 13 (- z 1))))
          ((= z 1900) (nb-jours-au-1-jan y (bissextile? z))))))
;Ex19

(define jour-de-semaine
  (lambda(x y z)
    (cond((= (modulo (nb-jours x y z) 7) 0) 'Lundi)
         ((= (modulo (nb-jours x y z) 7) 1) 'Mardi)
         ((= (modulo (nb-jours x y z) 7) 2) 'Mercredi)
         ((= (modulo (nb-jours x y z) 7) 3) 'Jeudi)
         ((= (modulo (nb-jours x y z) 7) 4) 'Vendredi)
         ((= (modulo (nb-jours x y z) 7) 5) 'Samedi)
         ((= (modulo (nb-jours x y z) 7) 6) 'Dimanche))))

;Ex21

(define einstein
  (lambda (u v)
    (/ (+ u v) (+ 1 (/ (* u v) (puis2 300000))))))


;//////////////////// Contrôle TP1 /////////////////////


(define LEntiers '(-5 -4 -3 -2 -1 0 1 2 3 4 5))

(define ex1
  (lambda ()
    (map signalS LEntiers)))

(define ex2
  (lambda ()
    (begin (if (bissextile? 1408) (display "l'année 1408 est bien bissextile\n") (display "l'année 1408 n'est pas bissextile\n"))
           (if (bissextile? 1500) (display "l'année 1500 est bien bissextile\n") (display "l'année 1500 n'est pas bissextile\n"))
           (display "Le 13 janvier 2408 sera un ") (jour-de-semaine 13 1 2408))))


           