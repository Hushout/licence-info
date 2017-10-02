#include <iostream>

using namespace std;

int main(){

  int a, b;

  cout<<"Entrez a:"<<endl;
  cin >> a;
  cout<<"Entrez b:"<<endl;
  cin >> b;

  cout<<"L'adresse de a est: "<< &a  <<endl;
  cout<<"L'adresse de b est: "<< &b  <<endl;

  return 0;
}
