
/*****************************************************************************
 *                            --- tp5_interface.h ---
 *****************************************************************************
 *
 * L'interface publique pour travailler sur les automates.
 * 
 * Tout programme sur les automates devra inclure ce fichier et exploiter le
 * fichier tp5_implantation.c compilable s�par�ment (cf. makefile ou les
 * premi�res lignes du fichier testTP5.c). 
 */

#include "tp5_implantation.h"


/***********************
 * La structure des mots 
 ***********************
 */

/* TESTS */
int estMotVideP(Mot);

/* ACCESSEURS */
Lettre prem(Mot);
Mot suiv(Mot);

/* CONSTRUCTEURS */
Mot ajouterLettre(Lettre L, Mot m);




/*****************************
 * Les �tats et listes d'�tats 
 *****************************
 */

/* Les diff�rentes statuts possibles d'un �tat */
#define PAS_ETAT -1 		/* L'�tat n'a pas �t� trouv� */
#define ETAT_NORMAL 0
#define ETAT_INITIAL 1
#define ETAT_FINAL 10
#define ETAT_INITIAL_FINAL 11
#define ETAT_AU_MOINS_INITIAL(e)    (e & 1)
#define ETAT_AU_MOINS_FINAL(e) 	   (e & 10)


/* TESTS */
int estListeEtatVideP(ListeEtat L);

/* ACCESSEURS */
Etat premEtat(ListeEtat L);
ListeEtat suivEtats(ListeEtat L);

/* CONSTRUCTEUR */
ListeEtat ajouterEtat(Etat, ListeEtat);
ListeEtat unionEtat(ListeEtat, ListeEtat);

/* OUTILS */
int appart(Etat e, ListeEtat L);
int intersectionNonVide(ListeEtat L1, ListeEtat L2);
ListeEtat differenceEtat(ListeEtat L1, ListeEtat L2);
void afficherListeEtat(ListeEtat L);


/***********************
 * La structure Automate
 ***********************
 */

 /* TESTS */
int estEtatFinalP(Automate, Etat);
int existeTransitionP(Automate, Etat, Lettre);


/* CONSTRUCTEURS */
Automate creerAutomate(Mot alphabet);
void ajouterEtatAutomate(Automate A, Etat e, char statut);
void ajouterTransition(Automate, Etat,  Lettre, Etat);


/* ACCESSEURS */
Etat getEtatInitial(Automate);
ListeEtat getEtatsTerminaux(Automate A);
Etat delta(Automate A,Etat e, Lettre l);  // La fonction de transition delta


/* Pour les automates ind�terministes */
ListeEtat getEtatsInitiaux(Automate A);
ListeEtat deltaIND(Automate A, Etat e, Lettre L);
ListeEtat deltaEtenduIND(Automate A, ListeEtat E, Lettre L);


