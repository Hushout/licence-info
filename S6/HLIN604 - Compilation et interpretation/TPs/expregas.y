				/* expregas.y */
%{
#include <ctype.h>
#include "arbin.h"
#include "afnThomp.h"
void yyerror(char*);
int yylex();
int nombreEtat(Arbin);
char * invite="\nVeuillez saisir une expression régulière suivie de <Entrée> S.V.P.\n";
%}
%union {			/* YYSTYPE */
Arbin a;
int i;
}

%token<i> LETTRE         /* definition des jetons */
        
%type<a> expr           /* definition des types des non terminaux */

%left '|'     /* traitement des priorites sur les operateurs du moins au plus */
%left CONCAT LETTRE '('  /* symbole virtuel pour la concaténation (implicite) */
                          /* nécessaires pour conflits avec CONCAT */
%left '*'
%%

liste   :			/* chaine vide sur fin de fichier Ctrl-D */
        |       liste  ligne {printf(invite);}
        ;
ligne   :       '\n'            /* ligne vide : expression vide */
        |       error '\n'      {yyerrok; /* après la fin de ligne */}
        |       expr '\n'       
        {   int nbetat;
            affichera($1,0); 
            if (racine($1)=='0')
                printf("\nLe langage de l'expression régulière est vide !\n");
            else{
                printf("\nConstruction de l'Automate de %i états ...\n", nbetat=nombreEtat($1));
                initAfn(nbetat);
                construireAfn($1);
                afficherAfn();
            }
        }
        ;
expr    :       '(' expr ')'    {$$ = $2;}
        |       expr expr  %prec CONCAT
        {Arbin g,d;g=$1;d=$2; /* CONCAT */
         if (videa(d))
           $$= g;
         else { /* g et d non vides */
           if (racine(g)=='@'){ /* @.e=e.@=e */
             videra(&g);
             $$= d;
           }
           else if (racine(d)=='@'){
             videra(&d);
             $$= g;
           }
           else if (racine(g)=='0'){    /* 0.e=e.0=0 */
             videra(&d);
             $$= g;
           }
           else if (racine(d)=='0'){
             videra(&g);
             $$= d;
           }
           else $$= construire('.',g,d);
         }
       }
        |       expr '|' expr   
        {Arbin g,d;g=$1;d=$3; /* UNION */
         if (videa(d))
           $$= g;
         else { /* g et d non vides */
           if (racine(g)=='0'){ /* 0|e=e|0=e */
             videra(&g);
             $$= d;
           }
           else if (racine(d)=='0'){    /* e|0=e */
             videra(&d);
             $$= g;
           }
           else
             $$= construire('|',g,d);
         }
       }
        |       expr '*'
        {Arbin g=$1; /* ETOILE */
         if (racine(g)=='@'||racine(g)=='0'){   /* @*=0*=@ */
           videra(&g);  
           $$= construire('@',creerarbin(),creerarbin());
         }
         else                   /* ni epsilon ni ensemble vide */
           if (racine(g)=='*')
             $$=g;
           else
             $$= construire('*',g,creerarbin());
       }
        | LETTRE     {$$=construire($1,creerarbin(),creerarbin());}
        ;
%%
int yylex(){int i=getchar();
        if (islower(i)||i=='@'||i=='0') 
          {yylval.i=i;return LETTRE;} 
        else return i;
      }
void yyerror(char *s) {fprintf(stderr,"%s\n",s);}
int nombreEtat(Arbin a){        /* calcul du nombre d'état de l'afn */
  if (videa(a))
    return 0;
  else
    if (racine(a)=='.')         /* la concat ne rajoute pas d'état */
      return nombreEtat(sag(a))+nombreEtat(sad(a));
    else                /* union, *, symbole nécessitent 2 nouveaux états */
      return 2+nombreEtat(sag(a))+nombreEtat(sad(a));
}

int main(){/*yydebug=1;*/printf(invite);return yyparse();}
