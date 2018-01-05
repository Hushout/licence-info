#include <iostream>

using namespace std;

int nbOcc(int T[10], int occ);

int main()
{
    int O = 3;
    int T[10] = {2, 3, 4, 2, 3, 1, 8, 2, 5, 9};

    cout << "nb occurrence O = " << nbOcc(T, O) << endl;
    return 0;
}

int nbOcc(int T[10], int occ)
{
    int nbOccurence = 0;

    for(int i = 0 ; i < 10 ; i++)
    {
        if(T[i] == occ)
        nbOccurence++;
    }

    return nbOccurence;
}
