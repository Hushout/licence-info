
/****************************************************************************
 *                            --- tp5_implantation.h ---
 ****************************************************************************
 *
 * Définition des structures liées aux automates et déclarations des fonctions
 * de gestion de ces structures.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***********************
 * La structure des mots 
 ***********************
 */

/* Un mot est une chaînes de lettres (où chaque lettre est un caractère) */ 
typedef char  Lettre;
typedef char* Mot;


/***************************************************
 * Les structures Etat, ListeEtat et ListeEtatStatut
 ***************************************************
 */

#define  Etat int	// Un état est identifié par un entier positif ou nul


/* Liste des états avec leur statut associé.
 * 
 * Le statut d'un état indique si c'est un états INITIAL et/ou FINAL. 
 * Le statut d'un état sera codé par un entier (cf. les #define ETAT_xxx du 
 * fichier tp5_interface.h, avec le cas particulier de PAS_ETAT qui
 * correspondra au cas où l'état recherché n'existe pas.
 * 
 * La liste se termine par NULL
 */
struct noeudEtatStatut 
{
    Etat ident ;	// Un entier identifiant l'état
    int statut;		// normal, initial, final ou « initial+final »
    struct noeudEtatStatut  *suiv ;
};

typedef struct noeudEtatStatut *ListeEtatStatut ;

/* ACCESSEURS */
Etat premEtat_ES(ListeEtatStatut L);
char premStatut_ES(ListeEtatStatut L);
ListeEtatStatut suivEtats_ES(ListeEtatStatut L);

/* CONSTRUCTEUR */
ListeEtatStatut ajouterEtatStatut(Etat e, char statut, ListeEtatStatut les);




/* Liste des états.
 * La liste se termine par NULL
 *
 * Remarque : cette stucture est une simplification de ListeEtatStatut et sera
 *            utile pour les automates indéterministes.
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

/* La fonction de transition delta est implantée par une liste de 
 * triplet (e,x,e') où e et e' sont des états et x une lettre. 
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

/* Un automate A est la donnée de :
 *	° Un mot dont l'ensemble des lettres constituera l'alphabet de A.
 *      ° Une liste de couples (e,s) où e est un état de A et s le statut
 *        de l'état : (normal, initial, final, initial+final), implanté par
 *        un entier. 
 *	° Une liste de triplet (e,x,e') où e et e' sont des états et x une 
 *      ° lettre ; cette liste représentant la fonction de transition delta.
 * 
 * Remarque : la liste des états est nécessaire en théorie car elle ne peut 
 *            se déduire du reste. De même, l'alphabet n'est pas forcément
 *	      limité aux lettres présentes dans la fonction delta, ce qui
 *            nécessite de donner explicitement l'alphabet dans la structure.
 *	      Toutefois les tests de cohérence ne seront pas fait ici. Les
 *            exemples d'automates construits devront être cohérents. 
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


