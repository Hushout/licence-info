#include <iostream>
#include <cstdlib>
#include <ctime>

//Odorico Thibault L2 groupe B

using namespace std;

void f1(int n){
  int* T = new int[n];
  for(int i = 0 ; i < n ; i++){
    T[i] = i;
  }
  delete [] T;
}

void f3(int n){
  for(int j = 0 ; j < n ; j++){
    for(int i = 0 ; i < n ; i++){
      f1(i);
    }
  }
}

void g2(int n){
  if(n > 1){
    g2(n - 1);
    g2(n - 1);
  }
}

void g3(int n){
  if(n > 1){
    g3(n - 1);
    g3(n - 1);
    g3(n - 1);
  }
}

//Ex2:
//difference entre f1(n) et f3(n) ? a partir de n = 1000 on sent une difference
//difference entre f3(n) et g2(n) ? a partir de n = 30 on sent une difference
//difference entre g2(n) et g3(n) ? a partir de n = 20 on sent une difference

//Ex3:
//difference entre f1(n) et f3(n) executer succesivement et f3(n) seul ? on ne voit pas de difference
//difference entre f3(n) et g2(n) executer succesivement et g2(n) seul ? on ne voit pas de difference
//difference entre g2(n) et g3(n) executer succesivement et g3(n) seul ? on ne voit pas de difference


int main(int argc, char** argv){
  if(argc == 2){
    
    clock_t time;
    time = clock();
    f1(atoi(argv[1]));
    time = clock() - time;
    cout << "f1 : temps exec = " << ((float)time)/CLOCKS_PER_SEC << "s" << endl;

    time = clock();
    f3(atoi(argv[1]));
    time = clock() - time;
    cout << "f3 : temps exec = " << ((float)time)/CLOCKS_PER_SEC << "s" << endl;

    time = clock();
    g2(atoi(argv[1]));
    time = clock() - time;
    cout << "g2 : temps exec = " << ((float)time)/CLOCKS_PER_SEC << "s" << endl;
    
    time = clock();
    g3(atoi(argv[1]));
    time = clock() - time;
    cout << "g3 : temps exec = " << ((float)time)/CLOCKS_PER_SEC << "s" << endl;
  }
  else{
    cout << "ERREUR: Mauvais argument : " << argv[0] << " <entier>" << endl;
  }
  
}

// g++ Q1.cpp -o R1


//A faire
//tri n²  (bulle)
//tri n log n (fusion)
