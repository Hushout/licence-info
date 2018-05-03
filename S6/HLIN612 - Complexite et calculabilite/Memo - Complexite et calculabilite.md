# INTRODUCTION

**La théorie de la calculabilité traite la question suivante:**

Etant donnée un problème, existe t-il un algorithme qui resout ce problème ? 
Si c'est le cas, le problème est dit **décidable** sinon le problème est dit **indécidable**.

Si un problème est décidable la théorie de la complexité va ensuite determiné si il existe un algorithme efficace à ce problème.

**La théorie de la complexité traite la question suivante:**

Etant donnée un problème, existe t-il un algorithme **efficace** qui resout ce problème ?

La notion d'efficacité est traité de la manière suivante:

Quand la resolution du problème ce fait en temps polynomial par rapport a la taille de la donnée,
le problème est alors dit **facile**, sinon il est dit **difficile**

Dans un problème facile, on peut multiplier la taille de la donnée traiter par unité de temps si on multiplie egalement la puissance de l'ordinateur, ce n'est pas le cas avec un problème difficile.

# DETERMINER SI UN PROBLÈME EST DÉCIDABLE OU PAS ET FACILE OU PAS

**LA REDUCTION:**

Soient P et Q, deux problèmes. Supposons que ProcQ résout le problème Q et que l’on puisse écrire procP
qui résout P de la façon suivante :

```
procP(D):
	début
	...
	procQ(f(D))
	...
	end
```

**Q est calculable => P calculable**

(si f est calculable et tout ce qui est extérieur à l’appel à procQ est calculable).

En effet il suffit d'avoir une procédure qui résout Q pour avoir une procédure qui résout P.

**Q facile => P facile**

(si évidemment f est calculable en temps polynomial, si le nombre d'appels à procQ est polynomial et tout ce qui est extérieur à cet appel s'exécute en temps polynomial).

En effet une procédure avec les bonnes propriétés pour Q (exécution en temps polynomial) entraîne la connaissance d’une procédure avec les bonnes propriétés pour P.

De même sous les mêmes hypothèses :

**P non calculable => Q non calculable**

(si Q était calculable, on aurait une procédure pour P ce qui est faux
par hypothèse).

**P difficile => Q difficile**

(un algorithme polynomial pour Q entraînerait un algorithme polynomial pour P).

# CALCULABILITÉ

Le premier principe sur lequel repose la théorie de la calculabilité est le suivant :
Tout objet informatique est représentable (codable) par un entier naturel

# THEORÈME DE CANTOR

Une fonction f est dite totale si elle est définie pour toute valeur (pour tout x, f(x) a une valeur).

Théorème de Cantor: L’ensemble des fonctions totales de N dans N n’est pas dénombrable.

Preuve: Suposons que l’on puisse numéroter les fonctions totales de N dans N : 
f0 , f1 , f2, ..., fi, ... et définissons la fonction Y(n) = fn(n) + 1. 
Cette fonction est bien une fonction totale de N dans N donc par
hypothèse il existe fm telle que Y = fm. Que vaut Y(m) ?
fm(m) par hypothèse et fm(m) + 1 par définition. D’où la contradiction.

# THEORÈME DE RICE

On a vu que le théorème de l’arrêt est indécidable.
L’usage de la récursion donne une autre preuve. Supposons que h soit calculable par une procédure hp.

Soit gamma la procédure suivante :

```
int gamma(int x) {
	if(hp(gamma, x)) 
		while (1);
	else
		return 0;
}
```

Si gamma(x) est défini on en déduit que gamma(x) boucle et si gamma(x) est non défini que
gamma(x)=0. Donc par l’absurde il n’existe pas de procédure qui calcule h.

Pourquoi limiter la méthode précédente au problème de l’arrêt ?

Soit Y(p) = 1 si Pour tout x, p(x) = x et 0 sinon.

Si Y est calculable par une procédure delta alors on peut écrire :

``` 
int gamma(int x) {
	if(delta(gamma)) 
		return 0;
	else 
		return x;
}
```

On en déduit :

Si Pour tout x, gamma(x) = x => Y(gamma) = 1 => Pour tout x, gamma(x) = 0

Si Il existe x, gamma(x) != x => Y(gamma) = 0 => Pour tout x, gamma(x) = x

Dans tous les cas on arrive donc à une contradiction qui implique que delta n’existe pas.
On peut donc facilement généraliser :

**Théorème de Rice:** 

Soit P un prédicat tel que, Pour tout x, p(x) = q(x) => P(p) = P(q), 
alors P est indécidable s’il n’est pas trivial.

**Preuve:**

Rappel : un prédicat est une fonction totale booléenne.
P non trivial donc il existe p0 et p1 tels que P(p0) = 0 et P(p1) = 1.

Supposons qu’il existe procP qui calcule P alors on peut écrire

```
int gamma(int x) {
	if(procP(gamma))
		return p0(x);
	else
		return p1(x);
}
```

Que vaut P(gamma) ? Toutes les hypothèses mènent à une absurdité.

Remarque : L’indécidabilité du problème de l’arrêt est une bonne nouvelle pour les informaticiens. Ecrire
des programmes corrects qui calculent ce que l’on attend d’eux sera toujours une activité nécessitant de la
réflexion et de l’expérience.

**Application:**

Soit p une procédure. Montrez que savoir si pour tout x, p(x) < x + 1 est un problème indécidable.
Soit q une procédure. Montrer que savoir si pour tout x, q(x) est pair est indécidable.

On donne à chaque fois deux preuves différentes, l'une utilisant le théorème de Rice et l'autre le principe
de récursion.

# COMPLEXITÉ

si resultat est de type oui/non => problème de decision
sinon => problème d'optimisation

# PROBLÈME NP-COMPLET

Un problème X se réduit (polynomialement) à un problème Y si étant donné un algorithme efficace pour
résoudre Y, on peut trouver un algorithme efficace pour résoudre X (efficace = qui s’exécute en temps
polynomial par rapport à la taille de la donnée).

Un problème M est NP-complet si et seulement si :

* Il est dans NP.
* Tout problème de NP se réduit polynomialement à lui.

Les problèmes NP-complets sont donc les plus difficiles de la classe NP.

Avec la connaissance d’un problème NP-complet, on va facilement pouvoir prouver l’existence d’autres
problèmes NP-complets. En effet pour montrer que M est NP-complet il faut :

* Montrer qu’il est dans NP (existence d’un certificat polynomial pour une réponse positive)
* Trouver un problème M’ connu NP-complet et trouver une réduction de M’ à M. C’est-à-dire pour
chaque donnée D de M’ trouver une donnée D' = f(D) telle que M(D') = M’(D) et f se calcule en
temps polynomial par rapport à la taille de D.


# NP:

NP = non deterministic polynomial

Un problème est dans NP si :

Il est facile (peut être résolu en temps polynomial par rapport à la taille de la donnée, avec un algorithme)

# NP-COMPLET:

Un problème est NP-complet si et seulement si :

* Il est dans NP (facile).
* Tout problème de NP se réduit polynomialement à lui.

# NP-DIFFICILE:

Un problème NP-difficile est un problème qui remplit la seconde condition, et donc peut être dans une classe de problème plus large et donc plus difficile que la classe NP.