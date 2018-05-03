# RAPPEL LOGIQUE

Une fbf est **satisfiable** s’il existe au moins une interprétation dans laquelle elle est vraie
Une fbf est **contingente** s’il existe au moins une interprétation dans laquelle elle est vraie et une dans laquelle elle est fausse
Une fbf est **valide** si dans toute interprétation elle est vraie
Une fbf est **insatisfiable** si elle est fausse dans toute interprétation

Une interpretation I qui donne la valeur vrai a une fbf est appelée **modèle**
Une interpretation I qui donne la valeur faux a une fbf est appelée **contre-modèle**

Deux fbf P et Q sont logiquement équivalentes ssi elles ont la même valeur pour toute
interprétation i.e. pour toute interprétation I v(P, I) = v(Q, I).

P eq (equivalente à) Q ssi P <=> Q est valide

T eq Toujours vrai
B eq Toujours faux

**Idempotence de ^ et v**

(A ^ A) eq A (A v A) eq A

**Associativité et commutativité de ^ et v**

((A ^ B) ^ C) eq (A ^ (B ^ C)) 			((A v B) v C) eq (A v (B v C))
(A ^ B) eq (B ^ A) 						(A v B) eq (B v A)

**Distributivité**

((A ^ (B v C) eq ((A ^ B) v (A ^ C)) 	((A v (B ^ C) eq ((A v B) ^ (A v C))

**Double négation**

!!A eq A

**Lois de De Morgan**

!(A ^ B) eq (!A v !B) 					!(A v B) eq (!A ^ !B)

**Implication**

(A => B) eq (!A v B) 					(A <= B) eq ((A => B) ^ (B => A))
!A eq (A => T)

**Absurde**

B eq (A ^ !A)

**Clauses:**

{P1, P2, ..., Pk} est consistant ssi (P1 ^ (P2 ^ ... (Pk-1 ^ Pk) ...) est satisfiable
{P1, P2, ..., Pk} est inconsistant, ou contradictoire, ssi (P1 ^ (P2 ^ ... (Pk-1 ^ Pk) ...) est insatisfiable

Une fbf C est une conséquence logique de l'ensemble de fbf {H1, ..., Hk} ssi pour toute
interprétation I telle que pour tout i v(Hi, I) = 1 (ou vrai) alors v(C, I) = 1 (ou vrai).

Dans ce cas on utilise la notation {H1, ..., Hk} |= C.

{H1, ..., Hk} |= C ssi
H1 ^ ... ^ Hk |= C ssi
H1 ^ ... ^ Hk => C valide ssi
H1 ^ ... ^ Hk ^ !C insatisfiable

# EVALUATION DE FORMULES

**ASSIGNATION**

Donnez la valeur d'unr formule selon une interpretation I

val(F, I) = ...

# FORMALISATION EN LOGIQUE

**On veut formaliser les phrase suivantes avec un langage du premier ordre** (Predicats)

1. Hamlet a été écrit par Shakespeare.
2. Homère a écrit l’Illiade et l’Oyssée.
3. Seul un être humain peut avoir écrit un livre.

**Pour cela on doit definir un langage L = C u P** (langage = constantes union predicats)

C = { Homère, Shakespeare, Hamlet, Illiade, Odyssee }
P = { humain/1, livre/1, ecrit/2 }

L'arité des predicats est indiquée après le symbole "/".
La signification des predicats unaire est immediate, celle de ecrit(x, y) est x à ecrit y 

**On procède ensuite à la formalisation**

1. ecrit(Shakespeare, Hamlet)
2. ecrit(Homère, Illiade) ^ ecrit(Homère, Odyssee)
3. Vx Vy ((livre(y) ^ ecrit(x, y)) => humain(x))

# VALIDITE D'UNE FORMULE

(E = Il existe)
(V = Pour tout)

F = Vx Vy [p(x, y) v Ez(r(x, z) ^ r(z, y))] => Vu Ev [p(u, v) v r(u, v)]

**METHODE DE RESOLUTION**

F est valide ssi !F est insatisfiable. 
Puisque F est de la forme A => B, !F est de la forme A ^ !B.

On peut skolémiser A et B "indépendamment" (tout en faisant attention à ne pas réutiliser des symboles de fonctions)

**Voici une forme prénexe de !F** (déjà sous forme de conjonction de disjonction)

Eu Vv Vx Vy Ez [(p(x, y) v r(x, z)) ^ (p(x, y) v r(z, y)) ^ !p(u, v) ^ !r(u, v)]

**On obtient donc 4 clauses:** (en remplaçant u par la constante a et z par le terme f(v, x, y))

C1 : p(x, y) v r(x, f(v, x, y))
C2 : p(x, y) v r(f(v, x, y), y)
C3 : !p(a, v)
C4 : !r(a, v)

Ne pas oublier de renommer les variables communes à deux clauses avant d'effectuer un pas de résolution (sinon on ne pourra pas effectuer certaines unifications).

En considérant C1 et C3 = !p(a, v') et l'unificateur {x <- a, v' <- y}, on obtient la clause résolvante C5 = r(a, f(v, x, y)).

En considérant C5 et C4 = !r(a, v') et l'unificateur {v' <- f(v, x, y)}, on obtient la clause vide. 

On en conclut que !F est insatisfiable, donc F valide.

**METHODE DES MODELES**

(E = Il existe)
(V = Pour tout)
(€ = appartient à)

F s’écrit A => B. Soit I une interprétation quelconque. Si I n’est pas un
modèle de A, c’est un modèle de F par définition de "=>". Sinon, pour tout
d € D, on a deux cas :

1. soit Ed' € D avec (d, d') € I(p).
2. soit Ed' et d'' dans D, avec (d, d') € I(r) et (d', d'') € I(r).

Dans les deux cas, on a val(p(u, v) ^ r(u, v), I, [u <- d, v <- d']) = vrai.

Donc Vd € D, Ed' € D tel que val(p(u, v) ^ r(u, v), I, [u <- d, v <- d']) = vrai.

Donc val(B, I) = vrai. I est donc un modèle de F.

## THEORIE DES MODELES

