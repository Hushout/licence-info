# AUTOMATES

Automates complet => si sur chaque etat on a toutes les lettres de l'alphabet sortante.
Rendre automates complets => ajouter un puits inutiles avec les lettres manquantes en transition.

Automates £-transition => transition etiqueté avec le mot vide.
supression des £-transition => pour chaque états on calcule les £-successeurs (SUCC£(q0) = {q1, q2})
si j'ai un £-successeur qui est final rendre mon etat final
pour toutes les transition partant de (q,a,r) creer la transition (p,a,r) si elle n'existe pas


# LANGAGES

Grammaires embiguë => on peut obtenir le resultat avec deux derivations differentes (utilliser un arbre pour demontrer)

