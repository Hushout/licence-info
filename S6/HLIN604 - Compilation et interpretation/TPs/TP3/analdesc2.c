/** @file analdesc.c        
 *@author Michel Meynard
 *@brief Analyse descendante récursive d'expression arithmétique
 *
 * Ce fichier contient un reconnaisseur d'expressions arithmétiques composée de 
 * littéraux entiers sur un car, des opérateurs +, * et du parenthésage ().
 * Remarque : soit rediriger en entrée un fichier, soit terminer par deux 
 * caractères EOF (Ctrl-D), un pour lancer la lecture, l'autre comme "vrai" EOF.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

                             /* les macros sont des blocs : pas de ';' apres */
#define AVANCER {jeton=getchar();numcar++;}
#define TEST_AVANCE(prevu) {if (jeton==(prevu)) AVANCER else ERREUR_SYNTAXE}
#define ERREUR_SYNTAXE {printf("\nMot non reconnu : erreur de syntaxe \
au caractère numéro %d \n",numcar); exit(1);} 

int E(void);int R(int);int T(void);int S(int);int F(void); /* déclars */

int jeton;                       /* caractère courant du flot d'entrée */
int numcar=0;                    /* numero du caractère courant (jeton) */

int E(void){
  return R(T());
}
int R(int g){
  if (jeton=='+') {             /* regle : R->+TR */
    AVANCER
    return R(g+T());
  }
  else if (jeton=='-'){		/* regle : R->-TR */
	AVANCER
    return R(g - T());
  }
  else
 return g;                        /* regle : R->epsilon */
}
int T(void){
return S(F());                          /* regle : T->FS */
}
int S(int g){
  if (jeton=='*') {             /* regle : S->*FS */
    AVANCER
    return S(g*F());
  }else if(jeton=='/'){
	AVANCER
    return S(g/F());
  }else return g;                        /* regle : S->epsilon */
}
int F(void){
  if(isdigit(jeton)){		/* regle : F->0|1|...|9 */
	int r=jeton-'0';
	AVANCER
	return r;
  }else if (jeton=='(') {             /* regle : F->(E) */
    AVANCER
    int r=E();
    TEST_AVANCE(')')
    return r;
  }
  else ERREUR_SYNTAXE
}
int main(void){                 /* Fonction principale */
  while(1){
  AVANCER			/* initialiser jeton sur le premier car */
  int r=E();                          /* axiome */
  if (jeton=='\n')               /* expression reconnue et rien après */
    printf("\nMot reconnu de valeur %d\n",r); 
  else ERREUR_SYNTAXE           /* expression reconnue mais il reste des car */
  }
  return 0;
}
