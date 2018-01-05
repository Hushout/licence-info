#include <stdlib.h>
#include <stdio.h>

char* s;
void g(void){printf("%c\n",s[0]);} //gènère signal Sigsegv
void f(void){g();}

int main(){
  f();
  return 0;
}
