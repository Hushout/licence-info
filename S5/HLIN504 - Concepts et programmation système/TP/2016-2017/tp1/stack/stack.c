#include <stdio.h>

void f1(void);
void f2(void);

int main() {
    f1();
    f1();
    return 0;
}

void f1(void) {
    int arr[10] = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9};
    for(int i = 0 ; i < 10 ; i++)
        printf("%d " , arr[i]);
    printf("\n");
}

void f2(void) {
    int arr[10];
    for(int i = 0 ; i < 10 ; i++)
        printf("%d " , arr[i]);
    printf("\n");
}
