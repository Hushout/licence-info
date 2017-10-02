#include <iostream>

using namespace std;

int cpt = 0;

int A(int m, int n)
{
    cpt++;
    return (m==0 ? n+1 : (n == 0 ? A(m-1, 1) : A(m-1, A(m, n-1)) ) );
}


int main()
{
    int m, n;
    cout << "entrer m et n : " ;
    cin >> m >> n;
    cout << "A(m, n) = " << A(m, n) << endl;
    cout << "nombre d'appels : " << cpt << endl;
	return 0;
}
