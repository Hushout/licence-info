
/****************************************************************************
 *                            --- tp5_implantation.c ---
 ****************************************************************************
 *
 * Implantation des fonctions de gestion des structures liées aux automates.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tp5_interface.h"

/***********************
 * La structure des mots 
 ***********************
 */

/* TESTS */
int estMotVideP(Mot m)
{
    return (strlen(m) == 0);
}

/* ACCESSEURS  (mot supposé non réduit au mot vide) */
Lettre prem(Mot m)     
{
    return *m ;
}

Mot suiv(Mot m)
{//
    return m+1 ;
}

Mot ajouterLettre(Lettre L, Mot m)
{
    char *res = malloc(sizeof(m)+2);
    sprintf(res,"%c%s",L,m);
    return res;
}




/*****************************************
 * La structure des automates (bas niveau)
 *****************************************
 */
Etat premEtat_ES(ListeEtatStatut L)   		{   return L->ident;  }
char premStatut_ES(ListeEtatStatut L)		{   return L->statut; }
ListeEtatStatut suivEtats_ES(ListeEtatStatut L)    {   return L->suiv;   }

ListeEtatStatut ajouterEtatStatut(Etat e, char statut, ListeEtatStatut les)
{
    ListeEtatStatut res = malloc(sizeof(struct noeudEtatStatut)) ;
    res->ident = e ;
    res->statut = statut ;
    res->suiv = les ;   
    return res ;
}


Etat premTripletEtatDebut(FonctionDelta d)	{    return d->deb ; }
Lettre premTripletLettre(FonctionDelta d)	{    return d->l ;   }
Etat premTripletEtatFin(FonctionDelta d)	{    return d->fin ; }
FonctionDelta suivDelta(FonctionDelta d)	{    return d->suiv; }

FonctionDelta ajouterTriplet(Etat e1,Lettre L, Etat e2, FonctionDelta d)
{
    FonctionDelta res = (FonctionDelta)
                        malloc(sizeof(struct noeudFonctionDelta));
    res->deb = e1 ;
    res->l = L ;
    res->fin = e2 ;
    res->suiv = d ;
    return res ;
}



/******************************************
 * La structure « abstraite » des automates 
 ******************************************
 */

 /* TESTS */
int estEtatFinalP(Automate A, Etat e)
{
    ListeEtatStatut etats =  getEtatStatut(A) ;
    
    while ( etats != NULL)
    {
        if (premEtat_ES(etats) == e)     
            return (ETAT_AU_MOINS_FINAL(premStatut_ES(etats)))  ;
        etats = suivEtats_ES(etats) ;
    };
    return (1==0) ;    /* e n'est pas un état final */
}


int existeTransitionP(Automate A, Etat e, Lettre L)
{
    FonctionDelta d =  getFonctionDelta(A) ;
    while ( d != NULL)
    {
        if ( (premTripletEtatDebut(d) == e) && (premTripletLettre(d) == L))
            return ( 1== 1) ;
        d = suivDelta(d) ;
    };
    return (1==0) ;
}



/* CONSTRUCTEURS */
Automate creerAutomate(Mot alphabet)  // Automate sans états 
{
    Automate A = (Automate)malloc(sizeof(*A));
    getAlphabet(A) = alphabet;
    getEtatStatut(A) = NULL;
    getFonctionDelta(A) = NULL;
    return A ;
}


/* Par exemple, ajouterEtat(A, 2, ETAT_FINAL)
 *    --> ajoute dans l'automate A l'état identifié par l'entier 2 et qui sera
 *        un état final (et non initial). 
 */
void ajouterEtatAutomate(Automate A, Etat e, char statut)
{
    if (e < 0) 
    {
        printf("Erreur : l'état %d non identifié par un entier positif\n",e);
        exit(-1);
    };
    getEtatStatut(A) = ajouterEtatStatut(e, statut, getEtatStatut(A));

}


/* Ajouter une transition (e1,L,e2) à l'automate A
 * On ne vérifie pas que les états e1 et e2 existent déjà dans l'automate. 
 */
void ajouterTransition(Automate A, Etat e1,Lettre L,Etat e2) 
{
    getFonctionDelta(A) = ajouterTriplet(e1,L,e2,getFonctionDelta(A) ) ;
}


/************************
 * La structure ListeEtat
 ************************
 */

int estListeEtatVideP(ListeEtat L)	{   return L == (ListeEtat)NULL; }
Etat premEtat(ListeEtat L)	     	{   return L->ident; }
ListeEtat suivEtats(ListeEtat L)	{   return L->suiv;  }

ListeEtat ajouterEtat(Etat e, ListeEtat le)
{
    ListeEtat res = (ListeEtat)malloc(sizeof(struct noeudEtat));
    res->ident = e ;
    res->suiv = le ;
    return res ;
}

/* Appartenance d'un élément à une liste (d'états) */
int appart(Etat e, ListeEtat L)
{
    if (estListeEtatVideP(L))
        return (1 ==0) ;
    if (premEtat(L) == e)
        return ( 1 == 1) ;
    else
        return appart(e, suivEtats(L)) ;        
}

/* Test si intersection non vide entre deux listes d'états L1 et L2 */
int intersectionNonVide(ListeEtat L1, ListeEtat L2)
{
    if (estListeEtatVideP(L1))
        return (1 == 0) ;
    if (appart(premEtat(L1), L2))
        return (1 ==1);
    else
        return intersectionNonVide(suivEtats(L1), L2) ;
}

/* Union ensembliste de deux listes supposées sans doublons */
ListeEtat unionEtat(ListeEtat L1, ListeEtat L2)
{
    if (estListeEtatVideP(L1))
        return L2 ;
    if (appart(premEtat(L1), L2))
        return unionEtat(suivEtats(L1), L2) ;
    else
        return ajouterEtat(premEtat(L1), unionEtat(suivEtats(L1), L2) );
}


/* Difference ensembliste de deux listes supposées sans doublons
 * differenceEtat(L1, L2)  ---> L1 - L2   (les éléments de L1 qui ne sont pas
 * dans L2. 
 */
ListeEtat differenceEtat(ListeEtat L1, ListeEtat L2)
{
    if (estListeEtatVideP(L1))
        return L1 ;
    if (appart(premEtat(L1) , L2))
        return differenceEtat(suivEtats(L1),L2);
    else
        return ajouterEtat(premEtat(L1), differenceEtat(suivEtats(L1),L2));
}


void afficherListeEtat(ListeEtat L)
{
    if (estListeEtatVideP(L))
    {
        printf("\n");
        return ;
    };
    printf("%d ", premEtat(L)) ;
    afficherListeEtat(suivEtats(L));    
}


/*******************************
 * Pour un automate déterministe
 *******************************
 */ 

Etat getEtatInitial(Automate A)
{  // Recherche de l'état dans la liste des états.
   // Autre implantation possible : placer l'état initial dans un coin
   // directement accessible !

    ListeEtatStatut L = getEtatStatut(A) ;
    while (L != NULL)
    {
        if (ETAT_AU_MOINS_INITIAL(premStatut_ES(L)))
            return premEtat_ES(L) ;
        L = suivEtats_ES(L) ;
    }
    printf("Attention : pas d'état initial dans l'automate\n") ;
    return PAS_ETAT ;
}


// La fonction de transition delta
Etat delta(Automate A,Etat e, Lettre L)
{
    FonctionDelta d = getFonctionDelta(A) ;
    
    while (d != NULL)
    {
        if ((premTripletEtatDebut(d) == e) && (premTripletLettre(d) == L))
            return premTripletEtatFin(d) ;
        d = suivDelta(d) ;
    }
    return PAS_ETAT ;
}



/*********************************
 * Pour un automate indéterministe
 *********************************
 */

ListeEtat getEtatsInitiaux(Automate A)
{  // Recherche des états initiaux dans la liste des états.

    ListeEtatStatut L = getEtatStatut(A) ;
    ListeEtat res = NULL ;
    while (L != NULL)
    {
        if (ETAT_AU_MOINS_INITIAL(premStatut_ES(L)))
            res = ajouterEtat(premEtat_ES(L), res) ;
        L = suivEtats_ES(L) ;
    }
    return res ;
}

ListeEtat getEtatsTerminaux(Automate A)
{
    ListeEtatStatut L = getEtatStatut(A) ;
    ListeEtat res = NULL ;
    while (L != NULL)
    {
        if (ETAT_AU_MOINS_FINAL(premStatut_ES(L)))
            res = ajouterEtat(premEtat_ES(L), res) ;
        L = suivEtats_ES(L) ;
    }
    return res ;
}


// La fonction de transition delta (pour un automate indéterministe)
ListeEtat deltaIND(Automate A, Etat e, Lettre L)
{
    FonctionDelta d = getFonctionDelta(A) ;
    ListeEtat res = NULL ;    

    while (d != NULL)
    {
        if ((premTripletEtatDebut(d) == e) && (premTripletLettre(d) == L))
            res = ajouterEtat(premTripletEtatFin(d), res);
        d = suivDelta(d) ;
    }
    return res ;
}
