#include <iostream>

using namespace std;

int main()
{
    int T[10], valeur;


    for(int i = 0 ; i < 10 ; i++)
    {
    cout << "T[" << i << "] = ";
    cin >> valeur;
    cout << endl;
    T[i] = valeur;
    }

    for(int i = 9 ; i >= 0  ; i--)
    {
    cout << "T[" << i << "] = " << T[i];
    cout << endl;
    }

    return 0;
}
