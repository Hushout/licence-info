#include <iostream>

using namespace std;

float moyTab(int T[], int tailleTab);

int main()
{
    int A[3] = {2, 4, 18};
    cout << "Moyenne = " << moyTab(A, 3) << endl;
    return 0;
}

float moyTab(int T[], int tailleTab)
{
    int somme = 0;
    float moyenne;

    for(int i = 0 ; i < tailleTab ; i++)
    {
        somme = somme + T[i];
        cout << "tour = " << i << endl;
    }

    moyenne = ((float)(somme / tailleTab));

    return moyenne;
}
