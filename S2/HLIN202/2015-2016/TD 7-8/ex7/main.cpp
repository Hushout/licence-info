#include <iostream>

using namespace std;

void converBin(int nb, int T[32])
{
    int nbRentrer;

    for(int i = 31 ; i >= 0 ; i--)
    {
        if(i = 31)
        {
            if(nb % 2 == 0)
                T[i] = 0;
            else
                T[i] = 1;

            nbRentrer = nb/2;
        }

        else
        {
            if(nbRentrer % 2 == 0)
                T[i] = 0;
            else
                T[i] = 1;

            nbRentrer/2;
        }
    }
}


int main()
{
    int T[32];

    converBin(1234, T);

    for(int i = 0 ; i < 32 ; i++)
    {
        cout << T[i];
    }

    return 0;
}
