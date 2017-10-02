
/*******************************************************************************
 *
 *                        Implantation de tp3.h 
 *
 *******************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp3.h"


/***************************************
 * La structure de l'arbre de dérivation 
 ***************************************
 */


/* TESTS */

/* Un caractère a,b,c,... , y compris le non terminal S */
int estArbreCaractereP(ArbreDerivation a)
{
    return !(estArbreEtoileP(a)) && !(estArbreUnionP(a))
            && !(estArbreConcatenationP(a)) ;
};

/* Test si l'arbre de dérivation représente juste le non terminal S
 * L'arbre est supposé non vide. 
 */
int estArbreSP(ArbreDerivation a)
{
    return a->typeNoeud =='S'  ;
}

int estArbreEtoileP(ArbreDerivation a)
{
    return a->typeNoeud =='*' ;
}

int estArbreUnionP(ArbreDerivation a)
{
    return a->typeNoeud =='+' ;
}

int estArbreConcatenationP(ArbreDerivation a)
{
    return (char)(a->typeNoeud) == '.' ;
}


/* ACCESSEURS */

char getArbreCaractere(ArbreDerivation d)
{
    return d->typeNoeud ;
}

ArbreDerivation getArbreEtoile(ArbreDerivation d)
{
    return d->sa1 ;
}

ArbreDerivation getArbreUnion1(ArbreDerivation d)
{
    return d->sa1 ;
}

ArbreDerivation getArbreUnion2(ArbreDerivation d)
{
    return d->sa2 ;
}

ArbreDerivation getArbreConcatenation1(ArbreDerivation d)
{
    return d->sa1 ;
}

ArbreDerivation getArbreConcatenation2(ArbreDerivation d)
{
    return d->sa2 ;
}

/* CONSTRUCTEURS */

/* Le caractère est mis dans typeNoeud.
 * Le caractère ne doit être ni '+', ni '*', ni '.'
 */
ArbreDerivation consArbreCaractere(char c)
{
    ArbreDerivation a = (ArbreDerivation)malloc(sizeof(struct noeudDerivation));
    a->typeNoeud = c ;
    return a ;
}


/* typeNoeud = '*' et getEtoile est mis dans sa1 */
ArbreDerivation consArbreEtoile(ArbreDerivation d)
{
    ArbreDerivation a = (ArbreDerivation)malloc(sizeof(struct noeudDerivation));
    a->typeNoeud = '*' ;
    a->sa1 = d ;
    return a ;
}

/* typeNoeud = '+' */
ArbreDerivation consArbreUnion(ArbreDerivation d1, ArbreDerivation d2)
{
    ArbreDerivation a = (ArbreDerivation)malloc(sizeof(struct noeudDerivation));
    a->typeNoeud = '+' ;
    a->sa1 = d1 ;
    a->sa2 = d2 ;
    return a ;
}

/* typeNoeud = '.' */
ArbreDerivation consArbreConcatenation(ArbreDerivation d1, ArbreDerivation d2)
{
    ArbreDerivation a = (ArbreDerivation)malloc(sizeof(struct noeudDerivation));
    a->typeNoeud = '.' ;
    a->sa1 = d1 ;
    a->sa2 = d2 ;
    return a ;
}


/**********************************
 * La structure ExpressionReguliere
 **********************************
 */

/* Une expression régulière est un mot (chaîne de caractères) reconnu par la
 * grammaire. 
 * Une expression régulière est codée par une chaîne de caractères.
 * Elle est supposée bien parenthésée. Il n'y a pas de vérification que les
 * expressions soient bien formées. 
 * Les caractères spéciaux sont : +, * et les parenthèses ( et )
 * Tous les autres caractères sont considérés comme des "caractères normaux".
 * Remarque :  Les espaces sont considérés comme des caractères normaux. 
 */

/********************** 
 * Quelques utilitaires 
 **********************
 */

/* L'indice du dernier élément de E : strlen(E)-1.
 * L'indice du premier caractère est compté à 0. 
 */
#define inder(E) (strlen(E)-1)

/* Construction d'une nouvelle expression régulière extraite de E 
 * en ne conservant que les caractères de indeDeb à indeFin (les 2 inclus).
 * Le premier caractère est à l'indice 0.
 * Exemple : creerSousChaine("0123456", 2,4) ---> "234"
 */
ExpressionReguliere creerSousChaine(ExpressionReguliere E, 
                                    int indDeb, int indFin)
{
    int nbCaractereSousChaine = indFin - indDeb + 1 ;
    char *dest = malloc(sizeof(char)*(nbCaractereSousChaine+1)) ; // +1 pour \n
    strncpy(dest, (E+indDeb),nbCaractereSousChaine );
    dest[nbCaractereSousChaine] = '\0' ;
    return dest ;
}


int indParentheseFermante(ExpressionReguliere E, int deltaPar);

/* Recherche de l'indice de la fin de l'expression régulière commençant en E[0]
 * Si E[0] = '(', alors l'indice de la fin de l'expression correspondra à une
 * parenthèse fermante OU l'étoile qui suivrait. 
 * Sinon c'est que l'expression est réduite à un caractère. 
 *
 * Remarque : Cette fonction est liée à la grammaire étudiée car elle dépend du
 *            parenthèsage défini par la grammaire. 
 */
int indFinExpressionReguliere(ExpressionReguliere E)
{
    if (E[0] != '(')
        return 0 ;
    else {
        int i = indParentheseFermante(E+1,-1) ;
        return i + ( (E[i+1] == '*') ? 1: 0) ;
    }
}

/* Parcourt de la chaîne de caractère E (un morceau d'une expression régulière)
 * en comptant successivement : 
 *
 *   d = (le nombre de "(" rencontrées) - (le nombre de ")" rencontrées)
 * 
 * Rendre en valeur le premier indice i tel que d = deltaPar
 * L'expression doit être bien parenthésée. 
 * Remarque :  E[i] = ')' 
 */
int indParentheseFermante(ExpressionReguliere E, int deltaPar)
{
    if (deltaPar == 0) {
        return 0 ;
    } else {
        switch (*E) {
            case '(' : return indParentheseFermante(E+1, deltaPar-1) + 1 ;
            case ')' : return indParentheseFermante(E+1, deltaPar+1) + 1 ;
            default :  return indParentheseFermante(E+1, deltaPar) + 1 ;
        }
    }
}


/*********************** 
 * Les fonctions de base 
 ***********************
 */


/* TESTS */

/* Test si E = "c". Il n'y pas de parenthèses englobantes  */
int estCaractereP(ExpressionReguliere E)
{
    return (strlen(E) == 1) ;
}

/* Test si E = "(expReg)*"  */
int estEtoileP(ExpressionReguliere E)
{
    return ( E[inder(E)] == '*' ) ;
}

/* Test si E = "(expReg1+expReg2)"  */
int estUnionP(ExpressionReguliere E)
{
    return E[indFinExpressionReguliere(E+1) + 2] == '+' ;
}

/* Il n'y a pas de point de concaténation. Pour identifier une concaténation,
 * il faut en fait identifier que l'on n'est pas dans un autre des 3 cas.
 *     a) On ne doit pas être juste un caractère c
 *     b) Ce qui suit le premier S de (SS) ne doit pas être
 *            ni un '+'      (S+S)
 *            ni un  ')'     (S)*
 * Remarque : "abc" n'est pas un mot accepté mais "(ab)c" l'est.
 */
int estConcatenationP(ExpressionReguliere E)
{
    if (estCaractereP(E))
        return (1==0) ;
    else {
        int indSuivant = indFinExpressionReguliere(E+1) + 1 ;
        return (E[indSuivant] != '+') && (E[indSuivant] != ')') ; 
    }
}


/* ACCESSEURS */

char getCaractere(ExpressionReguliere E)
{
    return *E ;
}

/* Pour  E = "(expReg)*" ---> construit "expReg"  */
ExpressionReguliere getEtoile(ExpressionReguliere E)
{
    return creerSousChaine(E,1,inder(E)-2) ;
}

/* Renvoie l'expression avant le signe + de plus haut niveau
 * E = "(expReg1+expReg2)" ----> renvoie expReg1
 */
ExpressionReguliere getUnion1(ExpressionReguliere E)
{
    return creerSousChaine(E+1,0, indFinExpressionReguliere(E+1) ) ;
}

/* Renvoie l'expression après le signe + de plus haut niveau
 * E = "(expReg1+expReg2)" ----> renvoie expReg2
 */
ExpressionReguliere getUnion2(ExpressionReguliere E)
{
    return creerSousChaine(E, 1+indFinExpressionReguliere(E+1)+ 2, inder(E)-1) ;
}


// Renvoie l'expression avant le premier signe de concaténation
// Remarque : c'est la même chose que union1
ExpressionReguliere getConcatenation1(ExpressionReguliere E)
{ 
    return creerSousChaine(E+1,0, indFinExpressionReguliere(E+1) ) ;
}

/* Renvoie l'expression après la première sous expression régulière 
 * E = "(expReg1 expReg2)" ----> renvoie expReg2
 */
ExpressionReguliere getConcatenation2(ExpressionReguliere E)
{ 
    return creerSousChaine(E, 1+indFinExpressionReguliere(E+1)+ 1, inder(E)-1);
};



/*******************************
 * La structure ChaineDerivation
 *******************************
 */


/* TESTS */

int estChaineVideP(ChaineDerivation cd)
{
    return (cd == consChaineDerivationVide() ) ;
}


/* ACCESSEURS */

ArbreDerivation premDerivation(ChaineDerivation cd)
{
    return cd->prem ;
}

ChaineDerivation suivDerivation(ChaineDerivation cd)
{
    return cd->suiv ;
}


/* CONSTRUCTEURS */

ChaineDerivation consChaineDerivationVide()
{
    return NULL ;
}

ChaineDerivation consChaineDerivation(ArbreDerivation ad, ChaineDerivation cd)
{
    ChaineDerivation res = malloc(sizeof(struct noeudChaineDerivation));
    res->prem = ad ;
    res->suiv = cd ;
    return res ;
}

/* Ajouter un arbre de dérivation à la fin de la chaîne de dérivation cd.
 * Cette fonction reconstruit une nouvelle chaîne sans détruire la chaine cd en
 * argument. 
 */
ChaineDerivation consChaineDerivationFin(ArbreDerivation ad,ChaineDerivation cd)
{
    if (estChaineVideP(cd))
        return consChaineDerivation(ad,cd) ;
    else
        return consChaineDerivation(
                       premDerivation(cd),  
                       consChaineDerivationFin(ad, suivDerivation(cd)));
}



