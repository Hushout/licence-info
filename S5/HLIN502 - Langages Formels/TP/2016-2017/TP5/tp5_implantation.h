
/****************************************************************************
 *                            --- tp5_implantation.h ---
 ****************************************************************************
 *
 * D�finition des structures li�es aux automates et d�clarations des fonctions
 * de gestion de ces structures.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***********************
 * La structure des mots 
 ***********************
 */

/* Un mot est une cha�nes de lettres (o� chaque lettre est un caract�re) */ 
typedef char  Lettre;
typedef char* Mot;


/***************************************************
 * Les structures Etat, ListeEtat et ListeEtatStatut
 ***************************************************
 */

#define  Etat int	// Un �tat est identifi� par un entier positif ou nul


/* Liste des �tats avec leur statut associ�.
 * 
 * Le statut d'un �tat indique si c'est un �tats INITIAL et/ou FINAL. 
 * Le statut d'un �tat sera cod� par un entier (cf. les #define ETAT_xxx du 
 * fichier tp5_interface.h, avec le cas particulier de PAS_ETAT qui
 * correspondra au cas o� l'�tat recherch� n'existe pas.
 * 
 * La liste se termine par NULL
 */
struct noeudEtatStatut 
{
    Etat ident ;	// Un entier identifiant l'�tat
    int statut;		// normal, initial, final ou � initial+final �
    struct noeudEtatStatut  *suiv ;
};

typedef struct noeudEtatStatut *ListeEtatStatut ;

/* ACCESSEURS */
Etat premEtat_ES(ListeEtatStatut L);
char premStatut_ES(ListeEtatStatut L);
ListeEtatStatut suivEtats_ES(ListeEtatStatut L);

/* CONSTRUCTEUR */
ListeEtatStatut ajouterEtatStatut(Etat e, char statut, ListeEtatStatut les);




/* Liste des �tats.
 * La liste se termine par NULL
 *
 * Remarque : cette stucture est une simplification de ListeEtatStatut et sera
 *            utile pour les automates ind�terministes.
 */
struct noeudEtat 
{
    Etat ident ;
    struct noeudEtat  *suiv ;
};

typedef struct noeudEtat *ListeEtat ;




/*********************************************************
 * La structure implantant la fonction de transition delta 
 *********************************************************
 */

/* La fonction de transition delta est implant�e par une liste de 
 * triplet (e,x,e') o� e et e' sont des �tats et x une lettre. 
 *
 * La liste se termine par NULL
 */
struct noeudFonctionDelta
{
    Etat deb ;
    Lettre l ;
    Etat fin ;
    struct noeudFonctionDelta *suiv;
};

typedef struct noeudFonctionDelta *FonctionDelta ;

/* ACCESSEURS */
Etat premTripletEtatDebut(FonctionDelta d);
Lettre premTripletLettre(FonctionDelta d);
Etat premTripletEtatFin(FonctionDelta d);
FonctionDelta suivDelta(FonctionDelta d);

/* CONSTRUCTEUR */
FonctionDelta ajouterTriplet(Etat e1,Lettre L, Etat e2, FonctionDelta d);



/***********************
 * La structure Automate
 ***********************
 */

/* Un automate A est la donn�e de :
 *	� Un mot dont l'ensemble des lettres constituera l'alphabet de A.
 *      � Une liste de couples (e,s) o� e est un �tat de A et s le statut
 *        de l'�tat : (normal, initial, final, initial+final), implant� par
 *        un entier. 
 *	� Une liste de triplet (e,x,e') o� e et e' sont des �tats et x une 
 *      � lettre ; cette liste repr�sentant la fonction de transition delta.
 * 
 * Remarque : la liste des �tats est n�cessaire en th�orie car elle ne peut 
 *            se d�duire du reste. De m�me, l'alphabet n'est pas forc�ment
 *	      limit� aux lettres pr�sentes dans la fonction delta, ce qui
 *            n�cessite de donner explicitement l'alphabet dans la structure.
 *	      Toutefois les tests de coh�rence ne seront pas fait ici. Les
 *            exemples d'automates construits devront �tre coh�rents. 
 */


struct noeudAutomate
{
    Mot alphabet ;
    ListeEtatStatut etats;
    FonctionDelta delta ;
};
typedef struct noeudAutomate  *Automate ;
   

/* ACCESSEURS */
#define getEtatStatut(A)	(A)->etats
#define getFonctionDelta(A)	(A)->delta
#define getAlphabet(A)		(A)->alphabet


