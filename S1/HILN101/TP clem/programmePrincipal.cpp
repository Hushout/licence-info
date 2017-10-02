// Fichier dans lequel vous écrirez les expressions à évaluer
#include "definitionsFonctions.cpp"
#define EVAL(exp) cout << "Valeur de " << (#exp) <<" : "<< (exp) << endl


int main()
{
  srand(time(NULL));
  boolalpha(cout);

  cout << "\n=================================================================\n ";

  // Expressions à évaluer
  cout << "\n==== Prise en main =======\n";
  // commande pour évaluer l'expression 3+4
  EVAL( 3+4 );
  // A vous :
  EVAL(true||false);
  EVAL(3*2);
  EVAL(abs(5));
  // EVAL(2/(1-1));
  EVAL(8/2);
  EVAL(9/2);
  EVAL(8%4);
  EVAL(9%4);
  EVAL(8.5+1);
  EVAL(8.2/4.1);
  EVAL(8.2/2);
  EVAL((10.5+8+11.25)/3);
  EVAL(pow(3,2));
  EVAL(sqrt(25));
  EVAL(sqrt(pow(12.3,2)));
  EVAL(true);
  EVAL(2>3);
  EVAL(!(2>3));
  EVAL((2>3)&&true);
  EVAL((2>3)||true);
  // EVAL(((2/0)>1)||true);
  EVAL(true||(2/0)>1);
  EVAL(2>3?5:7);
  EVAL(sqrt(2)>1.4?5:7);
  EVAL(((11.4+8.5)/2)>10?1:2);
  EVAL(moyenne(2.3,8));
  // EVAL(moyenne(2.3,8,7.7));
  EVAL(moyenne(11.4,8.5)>10?1:2);
  EVAL(max3(3,9,2.5));
  EVAL(multiple(0,2));
  EVAL(multiple(2,0));
  EVAL(multiple(0,0));
  
  EVAL(triangleEqui(2,2,2));
  EVAL(triangle(2,5,6));

  EVAL(triangleRect(3,4,5));

  EVAL(triangleIso(2,2,5));
  EVAL(triangleIso(3,3,3));
  EVAL(triangleIso(1,3,3));

  EVAL(ouExcl(true,true));
  EVAL(ouExcl(false,true));

  EVAL(mul2ou3(4));
  EVAL(mul2ou3(6));

  EVAL(memeDizaine(50,40));
  EVAL(memeDizaine(38,33));
  EVAL(memeDizaine(33,38));
  
  EVAL(memeParite(28,50));
  EVAL(memeParite(29,50));

  EVAL(gainRoulette(100,675,500));
  EVAL(gainRoulette(100,675,672));
  EVAL(gainRoulette(100,675,675));

  EVAL(estPair(9));
  EVAL(estPair(10));
  EVAL(estPair(-2));

  EVAL(existeMul11(2,10));
  EVAL(existeMul11(22,22));
  EVAL(existeMul11(22,2));

  EVAL(maxMull11(3,43));
  EVAL(maxMull11(3,4));

  EVAL(nbMul11(3,43));
  EVAL(nbMul11(3,4));

  EVAL(somMul11(3,54));
  EVAL(somMul11(3,4));

  EVAL(nbChifDec(3249));

  EVAL(chifRang(3279,4));

  EVAL(somChif(3249));
  EVAL(somChif(2453));
  EVAL(somChif(1234));
 
  EVAL(racNum(1236));

  EVAL(invChif(1234));
  
  EVAL(estCarre(36));

  const list<int> exli={1,33,67,12,1,22};
  EVAL(exli);
  EVAL(tete(exli));
  EVAL(queue(exli));
  EVAL(tete(queue(exli)));
  //EVAL(tete(tete(exli)));
  EVAL(queue(queue(exli)));
  EVAL(cons(11,liVide<int>()));
  EVAL(cons(11,exli));
  //EVAL(cons(1.1,exli));
  EVAL(tete(exli)+tete(queue(exli)));
  EVAL(cons(tete(exli)+tete(queue(exli)),queue(queue(exli))));
  
  EVAL(cons(tete(exli),queue(queue(exli))));

  EVAL(liste({1,2,3}));
  
  EVAL(longLi(exli));
  
  EVAL(minLi(exli));
  EVAL(minLi(liste({5,6,2,8,1,9})));
  EVAL(oterLi(1,exli));
  EVAL(oterLi(67,exli));
  EVAL(oterLi(9,exli));

  EVAL(estTriee(exli));
  EVAL(estTriee(liste({2})));
  EVAL(estTriee(liste({5,1})));
  EVAL(estTriee(liste({3,3,12,13,16})));

  EVAL(triListe(exli));

  EVAL(lgPrefEg(liste({2,7,7,2})));
  EVAL(lgPrefEg(liste({2,2,2,7,2})));

  EVAL(supPrefEg(liste({2,7,7,2})));
  EVAL(supPrefEg(liste({2,2,7,2})));
  EVAL(supPrefEg(liste({2,2,2})));
  EVAL(supPrefEg(liste({2,2,2,7,3,7,7})));

  EVAL(supRepet(liste({2,7,7,7,2})));
  //EVAL(supRepet(liste({2,2,7,7,2})));
  //EVAL(supRepet(liste({2,7,7,7,2})));
  //EVAL(supRepet(liste({2,2})));
  //EVAL(supRepet(liste({2,7,3,7})));
  //EVAL(supRepet(liVide<int>()));

  //EVAL(codeLi(liste({7,7,7,7,8,8,7,7,7})));
  //EVAL(codeLi(liste({5,6,6,6,6,5})));

  cout << "\n=================================================================\n ";
  return 0;
}

