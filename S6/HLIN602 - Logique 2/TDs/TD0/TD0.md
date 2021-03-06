Definition:

-Satisfiable => il existe une interprétation tel que V(F, I) = 1

-(Universelement) Valide => pour toute interpretation I, V(F, I) = 1

-Contingente => il existe une interpretation I tel que V(F, I) = 1 et il existe une interpretation I' tel que V(F, I') = 0

Question 1:

si V(p,I1) = V(q,I1) = V(r,I1) = 1, V(F, I1) = 1

modèle: p = q = r = 1

((p <-> r) <-> q) <-> (p <-> q)
  1		1	   1	   1  	 1
  -------			   -------
  	 1					  1
  	 -----------
  	 	  1	
  	 	  -----------------
  	 	  		  1

contre modèle: p = q = 1 et r = 0

((p <-> r) <-> q) <-> (p <-> q)
  1		0	   1	   1  	 1
  -------			   -------
  	 0					  1
  	 -----------
  	 	  0	
  	 	  -----------------
  	 	  		  0

Question 2:

(p <-> q) <-> (p <-> q) => Valide
(p <-> q) <-> (p <-> !q) => Insatisfiable
(p <-> q) <-> q => Contingente
((p <-> q) <-> !q) <-> !p => Valide 

Question 3:

p q r (q <-> r)	(p <-> (q <-> r)) (p <-> r) ((p <-> r) <-> (q <-> r)) 
0 0 0 	  1			   0			  1					1			
0 0 1	  0            1			  0					0			
0 1 0     0            1              1					0			
0 1 1     1            0              0					0		
1 0 0     1            1              0					0			
1 0 1     0            0           	  1					0		
1 1 0     0            0              0					1			
1 1 1     1            1              1					1		

Non equivalent exemple avec  p = q = r = 0

p q r (q <-> r)	(p <-> (q <-> r)) (p <-> q) ((p <-> q) <-> r) 
0 0 0 	  1			   0			  1				0			
0 0 1	  0            1			  1				1			
0 1 0     0            1              0				1			
0 1 1     1            0              0				0		
1 0 0     1            1              0				1			
1 0 1     0            0           	  0				0		
1 1 0     0            0              1				0			
1 1 1     1            1              1				1

Les formules sont equivalentes ici

Question 4:

A <-> B equivalent à: (A ^ B) v (!A ^ !B) 
!A <-> !B equivalent à: (!A ^ !B) v (!!A ^ !!B) = (!A ^ !B) v (A ^ B)
donc A <-> B equivalent à !A <-> !B

!(p <-> !q)
!(p -> !q) ^ (!q -> p)
!((!p v !q) ^ (!!q v p))
!(!p v !q) v !(q v p)
(!!p ^ !!q) v (!q ^ !p)
(p <-> q)

Question 5:

1)     
		A          B         C       X
(p <-> q) <-> s, s <-> p, p <-> q |= q

Ou encore A ^ B ^ C => X universellement valide

p -> q = 1
donc s = 1
donc p = 1
donc q = 1

donc la consequence logique est vérifiée.

2)
(p <-> q), (p <-> r) |= (r <-> q)

comme q -> p et p -> r, on a q -> r
comme r -> p et p -> q on a r -> p

donc la consequence logique est véfifiée

Question 6:

1) ouvrir_porte -> (possède_clé v possède_couteau)
2) (coupure ^ !vacciné) -> risque_tetanos
3) conduit -> majeur
4) velo -> (!vtt -> !ammortisseur)