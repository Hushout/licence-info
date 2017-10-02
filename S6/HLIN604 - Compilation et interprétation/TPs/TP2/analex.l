%{
  #define IF 300
  #define ELSE 301
  #define THEN 302
  #define ID 305
  #define LITENT 310
  #define LITDOUBLE 311

  union {int intValue ; float floatValue ; char * stringValue;}yylval;
%}

%option noyywrap

%%
if {return IF;}
else {return ELSE;}
then {return THEN;}
[1-9]+ {yylval.intValue = atoi(yytext); return LITENT;}
[1-9]+\.[1-9]+ {yylval.floatValue = atof(yytext); return LITDOUBLE;}
0[8-9][0-9]*\.[0-9]* {yylval.floatValue = atof(yytext); return LITDOUBLE;}
[a-zA-Z][a-zA-Z0-9_]*  {yylval.stringValue = strdup(yytext); return ID;}
\/\/.*\n  {}
[\t\n' ']+ {}
%%

int main() {
  int j;
  char * invite = "Saisissez un mot reconnu et finissez par EOF (CTRL-D)";
  printf("%s" , invite);
  while((j = yylex()) != 0) {
    printf("\nJeton : %i , de lexeme %s\n%s" , j , yytext , invite);
  }
  return 0;
}
