#include <stdio.h>

char *s;

void g(void) {
    printf(s);
} // génère signal SIGSEGV

void f(void) {
    g();
}

int main() {
    f();
}