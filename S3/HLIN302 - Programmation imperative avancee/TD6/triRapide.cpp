#include "triRapide.h"
#include "tableau-cellule.h"

void triRapide_aux(TableauCellule &T, size_t deb, size_t fin) {
  if (deb >= fin) return;
  size_t d = deb, f = fin-1, pivot;
  pivot = (deb + fin) / 2;
  while (d < f) {
    while ((d < pivot) && T.at(d).estAvantOuEquivalente(T.at(pivot))) {
      d++;
    }
    while ((pivot < f) && T.at(f).estApresOuEquivalente(T.at(pivot))) {
      f--;
    }
    echanger(T.at(d), T.at(f));
    if (pivot == d) {
      pivot = f++;
    } else {
      if (pivot == f) {
	pivot = d--;
      }
    }
    d++;
    f--;
  }
  triRapide_aux(T, deb, pivot);
  triRapide_aux(T, pivot + 1, fin);
}

void triRapide(TableauCellule &T) {
  triRapide_aux(T, 0, T.size());
}
