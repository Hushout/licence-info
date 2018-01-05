
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

/* Conversion d'un arbre de d�rivation en une cha�ne de caract�res */
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
    printf("Erreur dans ArbreDerivation2Cha�ne \n") ;
    return NULL;
}


/* Concat�nation de deux cha�nes de caract�res pass�s en argument. 
 * Le r�sultat est une nouvelle cha�ne de caract�res qui ne d�truit pas les 
 * cha�nes initiales. 
 * Les pro de C devraient trouver cette fonction dans une biblioth�que...
 */
char *concat(char *ch1, char *ch2)
{
    char *res = malloc(strlen(ch1) + strlen(ch2) + 1) ;
    strcat(res, ch1) ;
    strcat(res+strlen(ch1), ch2) ;
    return res ;
}


/* Conversion d'une cha�ne de d�rivations en une cha�ne de caract�res. 
 * La Chaine de d�rivations est suppos�e non vide.
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



/* Cr�ation d'une copie (profonde) d'un arbre de d�rivation */
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


/* Boucle interactive pour tester les cha�nes de d�rivations et la fonction 
 * remplacerArbreDerivationGauche()
 */
ChaineDerivation consChaineDerivationInteractive()
{
    char *production[] = {"", "(S)*","(S+S)", "(SS)",  "a", "b"} ;
    int s ;   /* Le statut du remplacement : succ�s (1) ou �chec (0) */

    int choixProd = -1 ;
    ArbreDerivation ad = construire("S") ; // Le dernier arbre de d�rivation
    ArbreDerivation a2 = ad ;   // Le dernier arbre de d�rivation
    ChaineDerivation res = consChaineDerivation(ad,consChaineDerivationVide());
    while (choixProd != 0) {
        printf("Arbre courant : %s\n\n", ArbreDerivation2Chaine(a2)) ;
        printf("Production � appliquer au S le + � gauche [0, 1,2,3,4,5] ?\n");
        printf("  1 : S --> (S)*   \n  2 : S --> (S+S) \n  3 : S --> (SS) \n");
        printf("  4 : S --> a  \n  5 : S --> b \n  0 : arr�ter \n");
        scanf("%d", &choixProd) ;
        if (choixProd == 0) 
            return res ;
        else {
            a2 = dupliquerArbreDerivation(a2) ;
            s = remplacerArbreDerivationGauche(a2,
                                           construire(production[choixProd])) ;
            if (s == 0) {
                printf("Plus aucun non terminal S rempla�able, on arr�te\n") ;
                return res ;
            };
            res = consChaineDerivationFin(a2,res) ;
        }
    }
    return res ;
}




/******************************************************************************
 *                         Fonctions � d�finir 
 ******************************************************************************
 */

/* Construc(tion d'un arbre de d�rivation correspondant � une expression
 * r�guli�re donn�e en argument. 
 */
ArbreDerivation construire(ExpressionReguliere E)
{
    return NULL;
}



/* Remplacement (�crasement) du non terminal le plus � gauche dans ad par r
 * Retourne 1 en cas de succ�s. 
 * Retourne 0 si le non-terminal n'a pas �t� trouv�.
 */
int remplacerArbreDerivationGauche(ArbreDerivation ad, ArbreDerivation r)
{
    return 0;
}

/* Construire la cha�ne de d�rivation la plus � gauche pour obtenir l'arbre de
 * d�rivation adfinal.
 * adfinal ne doit pas avoir d'occurrences de S. 
 */
ChaineDerivation consChaineDerivationGauche(ArbreDerivation adfinal)
{
    return NULL ;
}


/* L'arbre de d�rivation ad donne r en appliquant les productions de la
 * grammaire. L'arbre ad contient des non terminaux S. L'arbre r ne contient
 * aucun S. 
 *    a) Rechercher le S le plus haut dans l'arbre et le plus � gauche. 
 *    b) Rechercher ce � quoi cela correspond dans r pour en d�duire la
 *       production � appliquer � ce S pour � rapprocher � ad de r.
 *    c) Faire le remplacement (physique). 
 *
 * Remarque : il suffit de repartir de la fonction
 *            remplacerArbreDerivationGauche() 
 */
int remplacerSGauche(ArbreDerivation ad, ArbreDerivation r);



/* Construire la cha�ne de d�rivation la plus � droite pour l'arbre de
 * d�rivation ad
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
    printf("Chaine de d�rivation : %s\n", chaineDerivation2Chaine(cdi));
    
    ArbreDerivation aa = construire(Expr) ;
    printf("Arbre : %s\n", ArbreDerivation2Chaine(aa)) ;
    ChaineDerivation cdg = consChaineDerivationGauche(aa);
    printf("Chaine de d�rivations + � gauche : %s\n", 
           chaineDerivation2Chaine(cdg)); 

    return 1;
}
