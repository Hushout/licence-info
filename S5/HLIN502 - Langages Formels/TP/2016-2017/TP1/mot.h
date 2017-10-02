/** mot est une chaîne non mutable : pas d'op permettant de modifier un mot
 * on en crèe toujours un nouveau
 */
typedef char* mot;
typedef char symbole;
/** toutes les fonctions de base sur mot commencent par motMajuscule...
 */
/** retourne un mot vide */
mot motCreer();
/** concatène un symbole et un mot pour former un nouveau mot
 * retourne le mot c.m
 * ne modifie pas le mot m
 */
mot symboleConcatMot(symbole c, mot m);
mot motConcatSymbole(mot m, symbole c);
mot motCopier(mot m);
/** retourne vrai ssi m est vide
 */
int motEstVide(mot m);
/** retourne ce mot sans sa première lettre
 * prérequis : ce mot n'est pas vide
 */
mot motQueue(mot m);
/** retourne la première lettre de ce mot
 * prérequis : ce mot n'est pas vide
 */
symbole motTete(mot m); 
mot motConcatMot(mot un, mot deux);
mot motMiroir(mot m);
int motEgalMot(mot un, mot deux);


struct cellule;			/* composée d'un mot et d'un ptr */
typedef struct cellule* langage; /* un langage est un ptr sur le 1er mot */
struct cellule {
  mot m;
  langage suiv;
};
/** crèe un langage vide : une liste vide.
 */
langage langageCreer();
int langageEstVide(langage l);
int langageContientMot(langage l, mot m);
/** retourne un nouveau langage contenant m et l
 */
langage langageAjouterMot(langage l, mot m);
/** retourne le premier mot du langage
 * prérequis : l est non vide
 */
mot langagePremierMot(langage l);
/** retourne le langage privé de son premier mot
 * prérequis : l est non vide
 */
langage langageReste(langage l);
void langageAfficher(langage l);
langage langageUnionLangage(langage l1, langage l2);
