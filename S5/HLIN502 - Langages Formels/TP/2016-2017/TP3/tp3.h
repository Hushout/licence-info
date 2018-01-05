


/**********************************
 * La structure ExpressionReguliere
 **********************************
 */

typedef  char  *ExpressionReguliere ;


/* Une expression régulière est un mot (chaîne de caractères) reconnu par la
 * grammaire. 
 * Une expression régulière est codée par une chaîne de caractères.
 * Elle est supposée bien parenthésée. Il n'y a pas de vérification que les
 * expressions soient bien formées. 
 * Les caractères spéciaux sont : +, * et les parenthèses ( et )
 * Tous les autres caractères sont considérés comme des "caractères normaux".
 * Remarque :  Les espaces sont considérés comme des caractères normaux. 
 */

/* TESTS */
int estCaractereP(ExpressionReguliere E);
int estEtoileP(ExpressionReguliere E);
int estUnionP(ExpressionReguliere E);
int estConcatenationP(ExpressionReguliere E);

/* ACCESSEURS */
char getCaractere(ExpressionReguliere E);
ExpressionReguliere getEtoile(ExpressionReguliere E);
ExpressionReguliere getUnion1(ExpressionReguliere E);
ExpressionReguliere getUnion2(ExpressionReguliere E);
ExpressionReguliere getConcatenation1(ExpressionReguliere E);
ExpressionReguliere getConcatenation2(ExpressionReguliere E);



/***************************************
 * La structure de l'arbre de dérivation 
 ***************************************
 */

/* La structure d'arbre de dérivation
 * Le type du noeud sera : 
 *         '+', '*', ou '.'    pour un noeud union, étoile ou concaténation.
 *         'a','b','c',...     pour les lettres de l'alphabet de la grammaire.
 *         'S'                 pour l'axiome S (présent dans le langage étendu)
 *
 * Les sous termes sont mis dans sa1 s'il n'y en a qu'un seul (pour l'étoile)
 * ou deux pour les noeuds union et concaténation.
 * Les lettres et l'axiome S n'ont pas de sous terme. 
 */
struct noeudDerivation
{
    char typeNoeud ;
    struct noeudDerivation *sa1 ;
    struct noeudDerivation *sa2 ;
};

typedef struct noeudDerivation  *ArbreDerivation ;


/* TESTS  (L'arbre est supposé non vide) */

/* Un caractère a,b,c,... , y compris le non terminal S */
int estArbreCaractereP(ArbreDerivation a) ;
/* Test si l'arbre de dérivation représente juste le non terminal S */
int estArbreSP(ArbreDerivation a);
int estArbreEtoileP(ArbreDerivation a);
int estArbreUnionP(ArbreDerivation a);
int estArbreConcatenationP(ArbreDerivation a);

/* ACCESSEURS */
char getArbreCaractere(ArbreDerivation d);
ArbreDerivation getArbreEtoile(ArbreDerivation d);
ArbreDerivation getArbreUnion1(ArbreDerivation d);
ArbreDerivation getArbreUnion2(ArbreDerivation d);
ArbreDerivation getArbreConcatenation1(ArbreDerivation d);
ArbreDerivation getArbreConcatenation2(ArbreDerivation d);

/* CONSTRUCTEURS */

/* Le caractère est mis dans typeNoeud. Il ne doit être ni '+', ni '*', ni '.'
 */
ArbreDerivation consArbreCaractere(char c);
/* typeNoeud = '*' et getEtoile est mis dans sa1 */
ArbreDerivation consArbreEtoile(ArbreDerivation d);
/* typeNoeud = '+' */
ArbreDerivation consArbreUnion(ArbreDerivation d1, ArbreDerivation d2);
/* typeNoeud = '.' */
ArbreDerivation consArbreConcatenation(ArbreDerivation d1, ArbreDerivation d2);


/*******************************
 * La structure ChaineDerivation
 *******************************
 */


/* Une chaine de dérivation est une liste d'arbres de dérivation. 
 * Le délimiteur de fin de liste sera NULL. 
 */
struct noeudChaineDerivation
{
    ArbreDerivation prem ;
    struct noeudChaineDerivation *suiv ;
};


typedef struct noeudChaineDerivation  *ChaineDerivation ;
   

/* TESTS */

int estChaineVideP(ChaineDerivation cd) ;

/* ACCESSEURS */

/* Le premier arbre de dérivation de la chaîne de dérivation */
ArbreDerivation premDerivation(ChaineDerivation cd);
/* La chaîne de dérivation privée du premier arbre de dérivation */
ChaineDerivation suivDerivation(ChaineDerivation cd);


/* CONSTRUCTEURS */

/* Création d'une chaîne de dérivation vide */
ChaineDerivation consChaineDerivationVide() ;
/* Ajout d'un arbre de dérivation ad en tête de la chaine de dérivation cd */
ChaineDerivation consChaineDerivation(ArbreDerivation ad, ChaineDerivation cd);
/* Ajouter un arbre de dérivation à la fin de la chaîne de dérivation cd.
 * Cette fonction reconstruit une nouvelle chaîne sans détruire la chaine cd en
 * argument. 
 */
ChaineDerivation consChaineDerivationFin(ArbreDerivation ad,
                                         ChaineDerivation cd);

