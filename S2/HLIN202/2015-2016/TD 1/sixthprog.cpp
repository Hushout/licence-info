#include <iostream>

using namespace std;

int main(){

  float a;

  cout<<"Entrez la temperature en fahrenheit: "<<endl;
  cin >> a;

  cout<<"la temperature en celcius est : "<< (float)((5.0/9.0)*(a - 32)) <<endl;

  return 0;
}
