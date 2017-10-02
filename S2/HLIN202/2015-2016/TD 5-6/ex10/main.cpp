#include <iostream>

using namespace std;



void saisieDate(int* j, int* m, int* a)
{
    bool marche = true;
    char k, i;

    cout << "Entrez une date sous la forme jj/mm/aa: " << endl;
    cin >> *j >> k >> *m >> i >> *a;
    cout << endl;

    if( ((*j < 1 || *j > 31) || (*m < 1 || *m > 12)) || (k != '/' || i != '/') )
    {
        while(!marche)
        {
            cout << "ERREUR ! Entrez une date sous la forme jj/mm/aa: " << endl;
            cin >> *j >> k >> *m >> i >> *a;
            cout << endl;

            if( !(((*j < 1 || *j > 31) || (*m < 1 || *m > 12)) || (k != '/' || i != '/')) )
            {marche = true;}
        }
    }
}


int main()
{
    int j, m, a;
    saisieDate(&j, &m, &a);

    cout << j << '/' << m << '/' << a << endl;
    return 0;
}
