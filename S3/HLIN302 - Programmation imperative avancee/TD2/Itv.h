#include <iostream>

class Itv {
 private:
  // Attributs
  double bi, bs;

 public:
  // Constructeurs
  Itv();
  Itv(double bi, double bs);

  // Accesseurs en lecture
  double getBorneInf() const;
  double getBorneSup() const;

  // Accesseurs en écriture
  void setBorneInf(double v);
  void setBorneSup(double v);

  // Autres Méthodes
  void Afficher() const;
  double Longueur() const;
  bool Appartient(double v) const;
};
