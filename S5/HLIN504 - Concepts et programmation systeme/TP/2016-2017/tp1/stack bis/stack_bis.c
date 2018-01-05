#include <stdio.h>

int main() {
    int arr1[10] = {0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9};
    for(int i = 0 ; i < 10 ; i++)
        printf("%d " , arr1[i]);
    printf("\n");

    int arr2[10];
    for(int i = 0 ; i < 10 ; i++)
        printf("%d " , arr2[i]);
    printf("\n");

    return 0;
}