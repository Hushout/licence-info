#include <iostream>

using namespace std;

int main()
{
    int T[32];

    for(int i = 0 ; i < 32 ; i++)
    {
        T[i] = i;
    }

    cout << "T[5] = " << T[5] << endl;

    return 0;
}
