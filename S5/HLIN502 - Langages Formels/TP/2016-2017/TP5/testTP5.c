
/*****************************************************************************
 *                              --- testTP5.c ---
 *****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pour une compilation séparée (via le makefile)
#include "tp5_interface.h"
// Pour une compilation globale (par un « gcc -Wall testTP5.c »)
// #include "tp5_implantation.c"
 

/*******************************
 * Pour un automate déterministe
 *******************************
 */

/* Calcul de delta*(e,m) pour l'automate A non forcément complet.
 * Retourne PAS_ETAT s'il n'y a pas d'état 
 */
Etat deltaEtoile(Automate A, Etat e, Mot m)
{
    printf("Fonction deltaEtoile à écrire...\n") ;
    exit ;
    return PAS_ETAT ;
}


/* Test si le mot m est reconnu par le langage défini par l'automate A */
int estAccepte(Automate A, Mot m)
{
    printf("Fonction estAccepte à écrire...\n") ;
    exit ;
    return (1==1);
}
                         



/*********************************
 * Pour un automate indéterministe
 *********************************
 */


// La fonction de transition delta étendue (pour un automate indéterministe)
ListeEtat deltaEtenduIND(Automate A, ListeEtat E, Lettre L)
{
    printf("Fonction deltaEtenduIND à écrire...\n") ;
    exit ;
    return NULL;
}


/* Calcul de delta*(E,m) pour l'automate A indéterministe, et E une liste
 * d'états. C'est la fonction de transition itérée étendue. 
 */
ListeEtat deltaEtoileIND(Automate A, ListeEtat E, Mot m)
{   
    printf("Fonction deltaEtoileIND à écrire...\n") ;
    exit ;
    return NULL;
}


/* Test si le mot m est reconnu par le langage défini par l'automate A */
int estAccepteIND(Automate A, Mot m)
{
    printf("Fonction  estAccepteIND à écrire...\n") ;
    exit ;
    return (1==1);
}                     



/**********************************************************
 * Pour un automate indéterministe avec epsilon-transitions
 **********************************************************
 *
 * On utilisera le caractère 'e' pour coder le mot vide.
 * 
 * Comme on ne vérifiait pas que les transitions n'avaient que des lettres
 * de l'alphabet, on peut ajouter des étiquettes portées par 'e', sans faire
 * attention de la cohérence ave l'alphabet. 
 * Toutefois, ce codage implique que la lettre « e » est désormais interdite
 * dans l'alphabet de l'automate. 
 * 
 */

ListeEtat epsilonChapeau(Automate A, ListeEtat E)
{
    printf("Fonction epsilonChapeau à écrire...\n") ;
    exit ;
    return NULL ;    
}


/* Les fonctions deltaIND et deltaEtenduIND sont les mêmes que dans le cas 
 * précédant des automates indéterministes sans epsilon-transitions.
 */



/* Calcul de delta*Epsilon(E,m) pour l'automate A avec epsilon-transitions.
 * C'est la fonction de transition itérée étendue. 
 */
ListeEtat deltaEtoileEpsilon(Automate A, ListeEtat E, Mot m)
{   
    printf("Fonction deltaEtoileEpsilon à écrire...\n") ;
    exit ;
    return NULL;
}


/* Test si le mot m est reconnu par le langage défini par l'automate A */
int estAccepteEpsilon(Automate A, Mot m)
{
    printf("Fonction estAccepteEpsilon à écrire...\n") ;
    exit ;
    return (1==1);
}                     







/********
 * Tester 
 ********
 */


int main()
{
    char m[80] ;   // Le mot à reconnaître par l'automate

    printf("\n*************\n Automate déterministe\n\n");

    Automate A = creerAutomate("ab");

    ajouterEtatAutomate(A,1, ETAT_INITIAL) ;
    ajouterEtatAutomate(A,2, ETAT_NORMAL) ;
    ajouterEtatAutomate(A,3, ETAT_FINAL) ;
    ajouterTransition(A, 1,'a', 2) ;
    ajouterTransition(A, 1,'b', 1) ;
    ajouterTransition(A, 2,'a', 2) ;
    ajouterTransition(A, 2,'b', 3) ;
    ajouterTransition(A, 3,'a', 3) ;
    ajouterTransition(A, 3,'b', 3) ;

    if (estAccepte(A,""))
        printf("Le mot vide appartient au langage \n");
    else
        printf("Le mot vide n'appartient pas au langage \n");

    while ( 1 == 1)
    {
        printf("Saisi d'un mot à tester (0 pour arrêter) : ");fflush(stdout);
        scanf("%s", m); fflush(stdin);
        if (strcmp(m,"0")==0)
            break ; 
        if (estAccepte(A,m))
            printf("« %s » appartient au langage \n",m);
        else
            printf("« %s » n'appartient pas au langage \n",m);

    };

    printf("\n*************\n Automate indéterministe\n\n");

    A = creerAutomate("ab");
    ajouterEtatAutomate(A,1, ETAT_INITIAL) ;
    ajouterEtatAutomate(A,2, ETAT_NORMAL) ;
    ajouterEtatAutomate(A,3, ETAT_FINAL) ;
    ajouterTransition(A, 1,'a', 1) ;
    ajouterTransition(A, 1,'b', 1) ;
    ajouterTransition(A, 1,'a', 2) ;

    ajouterTransition(A, 2,'b', 3) ;

    ajouterTransition(A, 3,'a', 3) ;
    ajouterTransition(A, 3,'b', 3) ;


    if (estAccepteIND(A,""))
        printf("Le mot vide appartient au langage \n");
    else
        printf("Le mot vide n'appartient pas au langage \n");


    while ( 1 == 1)
    {
        printf("Saisi d'un mot à tester (0 pour arrêter) : ");fflush(stdout);
        scanf("%s", m); fflush(stdin);
        if (strcmp(m,"0")==0)
            break ; 
        if (estAccepteIND(A,m))
            printf("« %s » appartient au langage \n",m);
        else
            printf("« %s » n'appartient pas au langage \n",m);

    };

    printf("\n*************\n Automate avec epsilon-transitions \n\n");

    A = creerAutomate("ab");
    ajouterEtatAutomate(A,1, ETAT_INITIAL) ;
    ajouterEtatAutomate(A,2, ETAT_NORMAL) ;
    ajouterEtatAutomate(A,3, ETAT_NORMAL) ;
    ajouterEtatAutomate(A,4, ETAT_NORMAL) ;
    ajouterEtatAutomate(A,5, ETAT_FINAL) ;
    ajouterTransition(A, 1,'a', 1) ;
    ajouterTransition(A, 1,'e', 2) ;
    ajouterTransition(A, 2,'b', 2) ;
    ajouterTransition(A, 2,'e', 1) ;
    ajouterTransition(A, 2,'a', 3) ;
    ajouterTransition(A, 3,'b', 4) ;
    ajouterTransition(A, 4,'e', 5) ;
    ajouterTransition(A, 5,'a', 5) ;
    ajouterTransition(A, 5,'b', 5) ;


    if (estAccepteEpsilon(A,""))
        printf("Le mot vide appartient au langage \n");
    else
        printf("Le mot vide n'appartient pas au langage \n");


    while ( 1 == 1)
    {
        printf("Saisi d'un mot à tester (0 pour arrêter) : ");fflush(stdout);
        scanf("%s", m); fflush(stdin);
        if (strcmp(m,"0")==0)
            break ; 
        if (estAccepteEpsilon(A,m))
            printf("« %s » appartient au langage \n",m);
        else
            printf("« %s » n'appartient pas au langage \n",m);

    };


    printf("Au revoir \n");
    return EXIT_SUCCESS ;
}

