
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"


ArbreDerivation construire(ExpressionReguliere E);
int remplacerArbreDerivationGauche(ArbreDerivation ad, ArbreDerivation r);
ChaineDerivation consChaineDerivationGauche(ArbreDerivation adfinal);
int remplacerSGauche(ArbreDerivation ad, ArbreDerivation r);



/******************************************************************************
 *                         Utilitaires
 ******************************************************************************
 */

/* Conversion d'un arbre de dérivation en une chaîne de caractères */
char *ArbreDerivation2Chaine(ArbreDerivation a)
{    
    if (estArbreCaractereP(a)) {   
        char *res = malloc(sizeof(char)*2) ;
        sprintf(res, "%c", a->typeNoeud) ;    
        return res ;
    }
    if (estArbreEtoileP(a)) {
        char *rec = ArbreDerivation2Chaine(getArbreEtoile(a)) ;
        char *res = malloc(sizeof(char)*(strlen(rec)+4));
        sprintf(res, "(%s)*", rec);
        return res ;
    }
    if (estArbreUnionP(a)) {
        char *rec1 = ArbreDerivation2Chaine(getArbreUnion1(a)) ;
        char *rec2 = ArbreDerivation2Chaine(getArbreUnion2(a)) ;
        char *res = malloc(sizeof(char)*(strlen(rec1)+strlen(rec2)+5));
        sprintf(res, "(%s+%s)", rec1,rec2);
        return res ;
    }
    if (estArbreConcatenationP(a)) {
        char *rec1 = ArbreDerivation2Chaine(getArbreConcatenation1(a)) ;
        char *rec2 = ArbreDerivation2Chaine(getArbreConcatenation2(a)) ;
        char *res = malloc(sizeof(char)*(strlen(rec1)+strlen(rec2)+5));
        sprintf(res, "(%s.%s)", rec1,rec2);
        return res ;
    }
    printf("Erreur dans ArbreDerivation2Chaîne \n") ;
    return NULL;
}


/* Concaténation de deux chaînes de caractères passés en argument. 
 * Le résultat est une nouvelle chaîne de caractères qui ne détruit pas les 
 * chaînes initiales. 
 * Les pro de C devraient trouver cette fonction dans une bibliothèque...
 */
char *concat(char *ch1, char *ch2)
{
    char *res = malloc(strlen(ch1) + strlen(ch2) + 1) ;
    strcat(res, ch1) ;
    strcat(res+strlen(ch1), ch2) ;
    return res ;
}


/* Conversion d'une chaîne de dérivations en une chaîne de caractères. 
 * La Chaine de dérivations est supposée non vide.
 */
char *chaineDerivation2Chaine(ChaineDerivation cd)
{
    if (estChaineVideP(suivDerivation(cd)))
        return ArbreDerivation2Chaine(premDerivation(cd)) ;
    else
        return concat(ArbreDerivation2Chaine(premDerivation(cd)) , 
                      concat(" \n --> " , 
                             chaineDerivation2Chaine(suivDerivation(cd)))) ;
}



/* Création d'une copie (profonde) d'un arbre de dérivation */
ArbreDerivation dupliquerArbreDerivation(ArbreDerivation a)
{
    if (estArbreCaractereP(a)) {
        return consArbreCaractere(getArbreCaractere(a)) ;
    }
    if (estArbreEtoileP(a)) {    
        return consArbreEtoile(dupliquerArbreDerivation(getArbreEtoile(a))) ;
    }
    if (estArbreUnionP(a)) {    
        return consArbreUnion(dupliquerArbreDerivation(getArbreUnion1(a)),
                              dupliquerArbreDerivation(getArbreUnion2(a))) ;
    }
 
    if (estArbreConcatenationP(a)) {    
        return consArbreConcatenation(
                     dupliquerArbreDerivation(getArbreConcatenation1(a)),
                     dupliquerArbreDerivation(getArbreConcatenation2(a))) ;
    }
    printf("Erreur dans dupliquerArbreDerivation\n");
    return NULL ;
}


/* Boucle interactive pour tester les chaînes de dérivations et la fonction 
 * remplacerArbreDerivationGauche()
 */
ChaineDerivation consChaineDerivationInteractive()
{
    char *production[] = {"", "(S)*","(S+S)", "(SS)",  "a", "b"} ;
    int s ;   /* Le statut du remplacement : succès (1) ou échec (0) */

    int choixProd = -1 ;
    ArbreDerivation ad = construire("S") ; // Le dernier arbre de dérivation
    ArbreDerivation a2 = ad ;   // Le dernier arbre de dérivation
    ChaineDerivation res = consChaineDerivation(ad,consChaineDerivationVide());
    while (choixProd != 0) {
        printf("Arbre courant : %s\n\n", ArbreDerivation2Chaine(a2)) ;
        printf("Production à appliquer au S le + à gauche [0, 1,2,3,4,5] ?\n");
        printf("  1 : S --> (S)*   \n  2 : S --> (S+S) \n  3 : S --> (SS) \n");
        printf("  4 : S --> a  \n  5 : S --> b \n  0 : arrêter \n");
        scanf("%d", &choixProd) ;
        if (choixProd == 0) 
            return res ;
        else {
            a2 = dupliquerArbreDerivation(a2) ;
            s = remplacerArbreDerivationGauche(a2,
                                           construire(production[choixProd])) ;
            if (s == 0) {
                printf("Plus aucun non terminal S remplaçable, on arrête\n") ;
                return res ;
            };
            res = consChaineDerivationFin(a2,res) ;
        }
    }
    return res ;
}




/******************************************************************************
 *                         Fonctions à définir 
 ******************************************************************************
 */

/* Construc(tion d'un arbre de dérivation correspondant à une expression
 * régulière donnée en argument. 
 */
ArbreDerivation construire(ExpressionReguliere E)
{
    return NULL;
}



/* Remplacement (écrasement) du non terminal le plus à gauche dans ad par r
 * Retourne 1 en cas de succès. 
 * Retourne 0 si le non-terminal n'a pas été trouvé.
 */
int remplacerArbreDerivationGauche(ArbreDerivation ad, ArbreDerivation r)
{
    return 0;
}

/* Construire la chaîne de dérivation la plus à gauche pour obtenir l'arbre de
 * dérivation adfinal.
 * adfinal ne doit pas avoir d'occurrences de S. 
 */
ChaineDerivation consChaineDerivationGauche(ArbreDerivation adfinal)
{
    return NULL ;
}


/* L'arbre de dérivation ad donne r en appliquant les productions de la
 * grammaire. L'arbre ad contient des non terminaux S. L'arbre r ne contient
 * aucun S. 
 *    a) Rechercher le S le plus haut dans l'arbre et le plus à gauche. 
 *    b) Rechercher ce à quoi cela correspond dans r pour en déduire la
 *       production à appliquer à ce S pour « rapprocher » ad de r.
 *    c) Faire le remplacement (physique). 
 *
 * Remarque : il suffit de repartir de la fonction
 *            remplacerArbreDerivationGauche() 
 */
int remplacerSGauche(ArbreDerivation ad, ArbreDerivation r);



/* Construire la chaîne de dérivation la plus à droite pour l'arbre de
 * dérivation ad
 */
ChaineDerivation consChaineDerivationDroite(ArbreDerivation ad)
{
    return NULL ;
}



int main()
{
    ExpressionReguliere Expr = "(((a(a)*)+((((bb)+c))*+d)))*" ;
    printf("Expression : %s\n", Expr);

    ArbreDerivation a = construire(Expr) ;
    printf("Arbre : %s\n", ArbreDerivation2Chaine(a)) ;

    ChaineDerivation cdi = consChaineDerivationInteractive() ;
    printf("Chaine de dérivation : %s\n", chaineDerivation2Chaine(cdi));
    
    ArbreDerivation aa = construire(Expr) ;
    printf("Arbre : %s\n", ArbreDerivation2Chaine(aa)) ;
    ChaineDerivation cdg = consChaineDerivationGauche(aa);
    printf("Chaine de dérivations + à gauche : %s\n", 
           chaineDerivation2Chaine(cdg)); 

    return 1;
}
