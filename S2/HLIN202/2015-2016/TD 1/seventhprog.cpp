#include <iostream>

using namespace std;

int main(){

  float a;

  cout<<"Entrez la temperature en celcius: "<<endl;
  cin >> a;

  cout<<"la temperature en celcius est fahrenheit: "<< (float)(a*(9.0/5.0)+32) <<endl;

  return 0;
}
