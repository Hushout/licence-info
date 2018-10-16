# TD2

```
f0 = £
f1 = b
f2 = a
f3 = f2f1 = ab
f4 = aba
f5 = abaab
...

F0 = 0
F1 = 1
F2 = 1

K(fn) = gn = fn-2 dernières
B(fn) = (fn avec 2 dernières inversées)

1) B(fn) = fn-2 + n-1

2) gn = (fn-2)² + gn-3

3) gn prefixe de (fn-1)^2 et (fn-2)^3

4) selon 3), gn est facteur de (fn-1)^2 donc comme pour n >= 5, |gn| >= |fn-1|, 
selon le cours, |fn-1| = Fn-1 est période de gn, idem pour |fn-2| = Fn-2
								
5) On note, pour n >= 2, Pn <=> Fn-1 ^ Fn-2 = 1
							   	   (pgcd)
Initialisation:

Pour n = 2 : F0 ^ F1 = 0 ^ 1 = 1 => donc P2 est vrai

Reccurence:

Pour n >= 2 on suppose pn vraie = Fn-1 ^ Fn-2 = 1

Soit d un diviseur de Fn et Fn-1 Alors 
il existe a,b appartenant à N tels que Fn = d x a et Fn-1 = d x b
Or Fn = Fn-1 + Fn-2 <=> d x a = d x b + Fn-2
					<=> Fn-2 = d(a-b)

Donc d est un diviseur de Fn-2 et Fn-1, donc par hypothèse de reccurence d = 1
Pn est initialisée et héréditaire donc vraie Vn >= 2

6) Pour p = Fn-2, q = Fn-1, x = gn (n >= 5)
On a (p + q) - pgcd(p, q) = Fn-1 
	(<=> Fn)
et |x| = Fn-2

donc p + q - pgcd(p, q) = |x| + 1 	(1)

et p et q sont 2 périodes de x 		(2)

pour autant pgcd(p, q) n'est pas une période de x

Les mots de Fibonacci fournissent une famille infini de mots pour lesquels le lemne de périodicité est optimal

EXERCICES SUR L'ALIGNEMENT:

x = ACT 	(m = 3)
y = ACGGC 	(n = 5) 

match = 2, mismatch = -1, indel = -1

T	-1	A 	C 	G 	G 	C

-1	0	-1	-2	-3	-4	-5	

A 	-1	2	1	0	-1	-2	

C 	-2	1	4	3->	2	1
					  \
T 	-3	0	3	3	2	1


E 	-1					(n-1)		(M) -> (0)

-1	*






				*	*

(m-1) 

L'automate reconnaît tous les alignements optimaux entre les deux séquences
```