%{
#define LITENT 310

union {int intValue ; float floatValue ; char * stringValue;}yylval;
%}

%option noyywrap

%%
[1-9]+ {yylval.intValue = atoi(yytext); return LITENT;}
%%

int getyylex() {
  int j;
  char * invite = "Saisissez un mot reconnu et finissez par EOF (CTRL-D)";
  printf("%s" , invite);
  while((j = yylex()) != 0) {
    printf("\nJeton : %i , de lexeme %s\n%s" , j , yytext , invite);
  }
  return 0;
}
