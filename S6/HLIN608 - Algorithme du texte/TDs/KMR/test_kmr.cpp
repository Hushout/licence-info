#include "kmr.h"
#include <iostream>
#include <fstream>
#include <string>
#include <libgen.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
  string motif;
  cout << "Ce programme (" << basename(argv[0]) << ") "
       << "est la version qui utilise les classes :" << endl;
#ifdef __USING_VECTORS__
  cout << "- vector<size_t> pour le vecteur v_a";
#else
  cout << "- map<size_t, size_t> pour le vecteur v_a";
#endif
  cout << endl;

#ifdef __USING_STACKS__
  cout << "- stack<size_t> pour les piles P_i et Q_i";
#else
  cout << "- list<size_t> pour les piles P_i et Q_i";
#endif
  cout << endl;

  switch (argc) {
  case 1:
    cerr << "usage : " << basename(argv[0]) << "<motif>" << endl;
    cerr << "usage alternatif : " << basename(argv[0]) << "<fichier> <nb_octets> (-1 pour tout le fichier)" << endl;
    return 1;
    break;
  case 2:
    motif += argv[1];
    break;
  default: {
    ifstream is(argv[1]);
    if (is) {
      int n = atoi(argv[2]);
      is.seekg(0, ios::end);
      if ((n == -1) || (is.tellg() < n)) {
	n = is.tellg();
      }
      char *ch = new char[n];
      is.seekg(0, ios::beg);
      is.read(ch, n);
      is.close();
      motif += ch;
      delete [] ch;
    } else {
      cerr << "Impossible d'ouvrir le fichier '" << argv[1] << "'" << endl;
      return 1;
    }
    break;
  }
  }
  KMR kmr(motif);
  cout << kmr << endl;
  cout << "That's All, Folks!!!" << endl;
  return 0;
}
