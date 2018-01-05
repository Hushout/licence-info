#include "Itv.h"

using namespace std;

Itv::Itv():bi(0), bs(0) { }
Itv::Itv(double bi, double bs):bi(bi), bs(bs) {
  if (bi > bs) {
    cerr << "Avertissement: les valeurs fournies (bi=" << bi << ", bs = " << bs
	 << ") pour la création de l'intervalle ont été inversées." << endl;
    this->bi = bs;
    this->bs = bi;
  }
}

double  Itv::getBorneInf() const { return bi; }
double  Itv::getBorneSup() const { return bs; }

void  Itv::setBorneInf(double v) {
  if (v > bs) {
    cerr << "Avertissement: la valeur de la borne supérieure (bs = " << bs
	 << ") a été mise à jour automatiquement suite à la mise à jour de la "
	 << "borne inférieure (bi passant de " << bi << " a " << v << ")."
	 << endl;
    bs = v;
  }
  bi = v;
}
void  Itv::setBorneSup(double v) {
  if (bi > v) {
    cerr << "Avertissement: la valeur de la borne inférieure (bi = " << bi
	 << ") a été mise à jour automatiquement suite à la mise à jour de la "
	 << "borne supérieure (bs passant de " << bs << " a " << v << ")."
	 << endl;
    bi = v;
  }
  bs = v;
}

void  Itv::Afficher() const { cout << "[" << bi << ", " << bs << "]"; }

double  Itv::Longueur() const { return bs - bi; }

bool  Itv::Appartient(double v) const { return (v >= bi) && (v <= bs); }
 
