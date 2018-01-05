


/**********************************
 * La structure ExpressionReguliere
 **********************************
 */

typedef  char  *ExpressionReguliere ;


/* Une expression r�guli�re est un mot (cha�ne de caract�res) reconnu par la
 * grammaire. 
 * Une expression r�guli�re est cod�e par une cha�ne de caract�res.
 * Elle est suppos�e bien parenth�s�e. Il n'y a pas de v�rification que les
 * expressions soient bien form�es. 
 * Les caract�res sp�ciaux sont : +, * et les parenth�ses ( et )
 * Tous les autres caract�res sont consid�r�s comme des "caract�res normaux".
 * Remarque :  Les espaces sont consid�r�s comme des caract�res normaux. 
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
 * La structure de l'arbre de d�rivation 
 ***************************************
 */

/* La structure d'arbre de d�rivation
 * Le type du noeud sera : 
 *         '+', '*', ou '.'    pour un noeud union, �toile ou concat�nation.
 *         'a','b','c',...     pour les lettres de l'alphabet de la grammaire.
 *         'S'                 pour l'axiome S (pr�sent dans le langage �tendu)
 *
 * Les sous termes sont mis dans sa1 s'il n'y en a qu'un seul (pour l'�toile)
 * ou deux pour les noeuds union et concat�nation.
 * Les lettres et l'axiome S n'ont pas de sous terme. 
 */
struct noeudDerivation
{
    char typeNoeud ;
    struct noeudDerivation *sa1 ;
    struct noeudDerivation *sa2 ;
};

typedef struct noeudDerivation  *ArbreDerivation ;


/* TESTS  (L'arbre est suppos� non vide) */

/* Un caract�re a,b,c,... , y compris le non terminal S */
int estArbreCaractereP(ArbreDerivation a) ;
/* Test si l'arbre de d�rivation repr�sente juste le non terminal S */
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

/* Le caract�re est mis dans typeNoeud. Il ne doit �tre ni '+', ni '*', ni '.'
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


/* Une chaine de d�rivation est une liste d'arbres de d�rivation. 
 * Le d�limiteur de fin de liste sera NULL. 
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

/* Le premier arbre de d�rivation de la cha�ne de d�rivation */
ArbreDerivation premDerivation(ChaineDerivation cd);
/* La cha�ne de d�rivation priv�e du premier arbre de d�rivation */
ChaineDerivation suivDerivation(ChaineDerivation cd);


/* CONSTRUCTEURS */

/* Cr�ation d'une cha�ne de d�rivation vide */
ChaineDerivation consChaineDerivationVide() ;
/* Ajout d'un arbre de d�rivation ad en t�te de la chaine de d�rivation cd */
ChaineDerivation consChaineDerivation(ArbreDerivation ad, ChaineDerivation cd);
/* Ajouter un arbre de d�rivation � la fin de la cha�ne de d�rivation cd.
 * Cette fonction reconstruit une nouvelle cha�ne sans d�truire la chaine cd en
 * argument. 
 */
ChaineDerivation consChaineDerivationFin(ArbreDerivation ad,
                                         ChaineDerivation cd);

