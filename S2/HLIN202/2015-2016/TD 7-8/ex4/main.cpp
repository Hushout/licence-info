#include <iostream>

using namespace std;

int sommeTab();

int main()
{
    int A[8] = {2, 0, 1, 4, 6, 3, 12, 9};
    int B[8], valeur;


    for(int i = 0 ; i < 8 ; i++)
    {
        if(i > 0)
        A[i] = A[i] + A[i-1];
        B[i] = A[i];
    }

    for(int i = 0 ; i < 8  ; i++)
    {
    cout << "B[" << i << "] = " << B[i];
    cout << endl;
    }
    cout << endl;

    for(int k = 0 ; k < 10 ; k++)
    {
        for(int i = 0 ; i < 7 ; i++)
        {
            if(B[i] % 2 != 0)
            {
                valeur = A[i];
                B[i] = A[i+1];
                B[i+1] = valeur;
            }
        }
    }

    for(int i = 0 ; i < 8  ; i++)
    {
    cout << "B[" << i << "] = " << B[i];
    cout << endl;
    }

    return 0;
}
