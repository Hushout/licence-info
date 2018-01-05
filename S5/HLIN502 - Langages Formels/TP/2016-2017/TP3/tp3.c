
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
 * La structure de l'arbre de d�rivation 
 ***************************************
 */


/* TESTS */

/* Un caract�re a,b,c,... , y compris le non terminal S */
int estArbreCaractereP(ArbreDerivation a)
{
    return !(estArbreEtoileP(a)) && !(estArbreUnionP(a))
            && !(estArbreConcatenationP(a)) ;
};

/* Test si l'arbre de d�rivation repr�sente juste le non terminal S
 * L'arbre est suppos� non vide. 
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

/* Le caract�re est mis dans typeNoeud.
 * Le caract�re ne doit �tre ni '+', ni '*', ni '.'
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

/* Une expression r�guli�re est un mot (cha�ne de caract�res) reconnu par la
 * grammaire. 
 * Une expression r�guli�re est cod�e par une cha�ne de caract�res.
 * Elle est suppos�e bien parenth�s�e. Il n'y a pas de v�rification que les
 * expressions soient bien form�es. 
 * Les caract�res sp�ciaux sont : +, * et les parenth�ses ( et )
 * Tous les autres caract�res sont consid�r�s comme des "caract�res normaux".
 * Remarque :  Les espaces sont consid�r�s comme des caract�res normaux. 
 */

/********************** 
 * Quelques utilitaires 
 **********************
 */

/* L'indice du dernier �l�ment de E : strlen(E)-1.
 * L'indice du premier caract�re est compt� � 0. 
 */
#define inder(E) (strlen(E)-1)

/* Construction d'une nouvelle expression r�guli�re extraite de E 
 * en ne conservant que les caract�res de indeDeb � indeFin (les 2 inclus).
 * Le premier caract�re est � l'indice 0.
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

/* Recherche de l'indice de la fin de l'expression r�guli�re commen�ant en E[0]
 * Si E[0] = '(', alors l'indice de la fin de l'expression correspondra � une
 * parenth�se fermante OU l'�toile qui suivrait. 
 * Sinon c'est que l'expression est r�duite � un caract�re. 
 *
 * Remarque : Cette fonction est li�e � la grammaire �tudi�e car elle d�pend du
 *            parenth�sage d�fini par la grammaire. 
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

/* Parcourt de la cha�ne de caract�re E (un morceau d'une expression r�guli�re)
 * en comptant successivement : 
 *
 *   d = (le nombre de "(" rencontr�es) - (le nombre de ")" rencontr�es)
 * 
 * Rendre en valeur le premier indice i tel que d = deltaPar
 * L'expression doit �tre bien parenth�s�e. 
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

/* Test si E = "c". Il n'y pas de parenth�ses englobantes  */
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

/* Il n'y a pas de point de concat�nation. Pour identifier une concat�nation,
 * il faut en fait identifier que l'on n'est pas dans un autre des 3 cas.
 *     a) On ne doit pas �tre juste un caract�re c
 *     b) Ce qui suit le premier S de (SS) ne doit pas �tre
 *            ni un '+'      (S+S)
 *            ni un  ')'     (S)*
 * Remarque : "abc" n'est pas un mot accept� mais "(ab)c" l'est.
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

/* Renvoie l'expression apr�s le signe + de plus haut niveau
 * E = "(expReg1+expReg2)" ----> renvoie expReg2
 */
ExpressionReguliere getUnion2(ExpressionReguliere E)
{
    return creerSousChaine(E, 1+indFinExpressionReguliere(E+1)+ 2, inder(E)-1) ;
}


// Renvoie l'expression avant le premier signe de concat�nation
// Remarque : c'est la m�me chose que union1
ExpressionReguliere getConcatenation1(ExpressionReguliere E)
{ 
    return creerSousChaine(E+1,0, indFinExpressionReguliere(E+1) ) ;
}

/* Renvoie l'expression apr�s la premi�re sous expression r�guli�re 
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

/* Ajouter un arbre de d�rivation � la fin de la cha�ne de d�rivation cd.
 * Cette fonction reconstruit une nouvelle cha�ne sans d�truire la chaine cd en
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



