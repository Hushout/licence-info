#include <signal.h>
#include <stdio.h>
#include "debug.h"

void g();
void f();

char * s;

int main() {
    int signals[] = {SIGSEGV , SIGFPE , -1};
    debug(signals);
}

void g() {
    printf(s);
}

void f() {
    g();
}