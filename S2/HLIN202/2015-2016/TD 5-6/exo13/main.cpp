#include <iostream>

using namespace std;



int main()
{
int a;
float b;

cout << "Entrez un entier: ";
cin >> a;
b = *((float*)(&a));
cout << "float: " << b << endl;




    return 0;
}
