#include "kmr.h"

#include <map>
#include <vector>
#include <stack>
#include <list>
#include <iostream>

//#define DEBUG
#ifdef DEBUG
#  define DEBUG_MSG(msg) \
  cerr << "DEBUG:" \
       << __FILE__ << ":" \
       << __LINE__ << ":" \
       << __FUNCTION__ << ":" \
       << msg << endl
#else
#  define DEBUG_MSG(msg) (void) 0
#endif

using namespace std;

bool KMR::next_iter() {
#ifdef __USING_STACKS__
  vector<stack<size_t> > P(e), Q(e);
#else
  vector<list<size_t> > P(e), Q(e);
#endif
  bool has_motif = false;
  
  cerr << "Nouvelle iteration avec "
       << "a = " << a
       << ", b = " << b
       << " et e = " << e
       << endl;
  // Empile les positions dans la pile correspondante au motif donné par v_a[i] s'il existe
#ifdef __USING_VECTORS__
  for (size_t p = 0; p < n; ++p) {
    if (v_a[p] != (size_t) -1) {
      size_t i = v_a[p];
#  ifdef __USING_STACKS__
      P[i].push(p);
#  else
      P[i].push_back(p);
#  endif
      DEBUG_MSG("On empile la position " << p << " sur la pile P[" << i << "]");
    }
  }
#else
  for (map<size_t, size_t>::const_iterator it = v_a.begin(); it != v_a.end(); ++it) {
    size_t i = it->second;
#  ifdef __USING_STACKS__
    P[i].push(it->first);
#  else
    P[i].push_back(it->first);
#  endif
    DEBUG_MSG("On empile la position " << *it << " sur la pile P[" << i << "]");
  }
#endif
  DEBUG_MSG("Fin de l'initialisation des piles P");
  // Dépile les piles P pour remplir les piles Q
  for (size_t i = 0; i < e; ++i) {
    while (!P[i].empty()) {
#ifdef __USING_STACKS__
      size_t p = P[i].top();
      P[i].pop();
#else
      size_t p = P[i].back();
      P[i].pop_back();
#endif
      DEBUG_MSG("On dépile la position " << p << " de la pile P[" << i << "]");
#ifdef __USING_VECTORS__
      if ((p + b < n) && (v_a[p + b] != (size_t) -1)) {
#else
      if ((p + b < n) && (v_a.find(p + b) != v_a.end())) {
#endif
#ifdef __USING_STACKS__
	Q[v_a[p + b]].push(p);
#else
	Q[v_a[p + b]].push_back(p);
#endif
	DEBUG_MSG("On empile la position " << p << " sur la pile Q[" << v_a[p + b] << "]");
      }
    }
    // Mettre un marqueur (-1) si il y a un motif répété dans chaque pile Q[i]
    DEBUG_MSG("Ajout des marqueurs sur les piles Q car on vient de vider la pile P[" << i << "]");
    for (size_t j = 0; j < e; ++j) {
      if (!Q[j].empty()) {
	DEBUG_MSG("La pile Q[" << j << "] n'est pas vide");
#ifdef __USING_STACKS__
	size_t x = Q[j].top();
	Q[j].pop();
#else
	size_t x = Q[j].back();
	Q[j].pop_back();
#endif
	if (x == (size_t) -1) {
	  DEBUG_MSG("La position au sommet est un marqueur");
#ifdef __USING_STACKS__
	  Q[j].push(x); // On remet x (=-1) au sommet de la pile
#else
	  Q[j].push_back(x); // On remet x (=-1) au sommetà la fin de la liste
#endif
	} else {
	  // La valeur x est une position, donc il y a peut-être un motif répété
	  DEBUG_MSG("La position au sommet est " << x);
	  if (!Q[j].empty()) { // Il y a une valeur sous x dans la pile Q[i]
#ifdef __USING_STACKS__
	    size_t y = Q[j].top();
#else
	    size_t y = Q[j].back();
#endif
	    DEBUG_MSG("Il y a une autre valeur sous le sommet : " << y);
	    if (y != (size_t) -1) { // Il y a au moins deux positions (x et y) dans la pile Q[i], donc un motif répété 
#ifdef __USING_STACKS__
	      Q[j].push(x); // On remet x au sommet de la pile (au dessus de y)
	      Q[j].push((size_t) -1); // On met un marqueur (-1) au sommet de la pile
#else
	      Q[j].push_back(x); // On remet x à la fin de la liste (après y)
	      Q[j].push_back((size_t) -1); // On met un marqueur (-1) à la fin de la liste
#endif
	      has_motif = true;
	      DEBUG_MSG("On vient de trouver au moins un motif répété car les positions "
			<< x << " et " << y << " étaient " << a << " équivalentes et les positions "
			<< (x + b) << " et " << (y + b) << " l'étaient également");
	    } // Sinon, x était toute seule. On ne la remet pas.
	  } // Sinon, x était toute seule. On ne la remet pas.
	}
      } // La pile Q[i] est vide. Inutile de mettre un marqueur (-1)
      DEBUG_MSG("Pile Q[" << j << "] à jour");
    }
  }
  DEBUG_MSG("Fin du remplissage des piles Q");

  if (has_motif) {
    DEBUG_MSG("Extraction des motifs répétés");
    // On réinitialise v_a avec (-1) pour chaque position
#ifdef __USING_VECTORS__
    fill(v_a.begin(), v_a.end(), (size_t) -1);
#else
    v_a.clear();
#endif
    // Extrait les motifs répétés des piles Q
    size_t e_tmp = (size_t) -1;
    for (size_t i = 0; i < e; ++i) {
      DEBUG_MSG("On dépile la pile Q[" << i << "]");
      while (!Q[i].empty()) {
#ifdef __USING_STACKS__
	size_t x = Q[i].top();
	Q[i].pop();
#else
	size_t x = Q[i].back();
	Q[i].pop_back();
#endif
	DEBUG_MSG("La pile Q[" << i << "] n'est pas vide");
	if (x == (size_t) -1) { // Nouveau motif
	  ++e_tmp;
	  DEBUG_MSG("Nouvelle classe de motifs " << e_tmp);
	} else {
	  v_a[x] = e_tmp;
	  DEBUG_MSG("Motif de la classe " << e_tmp << " à la position " << x);
	}
      }
    }
    e = ++e_tmp;
    a += b;
    n -= b;
    DEBUG_MSG("On restreint la taille de v_a à n = " << n);
  }
  return has_motif;
}

void KMR::init() {
  map<char, size_t> alphabet;
  n = ref_seq.length();
  a = b = 1;
#ifdef __USING_VECTORS__
  v_a.resize(n);
#endif

  for (size_t i = 0; i < n; ++i) {
    map<char, size_t>::const_iterator it = alphabet.find(ref_seq[i]);
    if (it == alphabet.end()) {
      v_a[i] = alphabet.size();
      DEBUG_MSG("Adding symbol '"
		<< ref_seq[i]
		<< "' with id "
		<< alphabet.size());
      alphabet.insert(pair<char, size_t>(ref_seq[i], alphabet.size()));
    } else {
      v_a[i] = it->second;
    }
  }
  e = (alphabet.size() < n ? alphabet.size() : 0);
}

KMR::KMR(const string &ref_seq): ref_seq(ref_seq) {
  init();
  if (e) {
    do {
      b = a;
    } while (next_iter());
    while (b > 1) {
      b >>= 1;
      next_iter();
    }
  } else {
    a = b = 0;
  }
  DEBUG_MSG("Fin de la recherche, k = " << a);
}

const string &KMR::getRefSeq() const {
  return ref_seq;
}

size_t KMR::getRepeatedMotifMaxLength() const {
  return e ? a : 0;
}

size_t KMR::getNbRepeatedMotif() const {
  return e;
}

list<size_t> KMR::getRepeatedMotifPositions(size_t motif) const {
  list<size_t> positions;
#ifdef __USING_VECTORS__
  for (size_t p = 0; p < n; ++p) {    
    if (v_a[p] == motif) {
      positions.push_back(p);
    }
  }
#else
  for (map<size_t, size_t>::const_iterator it = v_a.begin(); it != v_a.end(); ++it) {    
    if (it->second == motif) {
      positions.push_back(it->first);
    }
  }
#endif
  return positions;
}

ostream &operator<<(ostream &os, const KMR &kmr) {
  const string &ref = kmr.getRefSeq();
  if (!kmr.getNbRepeatedMotif()) {
    os << "Il n'y a pas de motif répété dans la séquence '"
       << ref
       << "'.";
  } else {
    os << "La taille maximale du(des) motif(s) répété(s) est " << kmr.getRepeatedMotifMaxLength() << endl
       << "Il y a " << kmr.getNbRepeatedMotif() << " motif(s) répété(s)" << endl;
    for (size_t m = 0; m < kmr.getNbRepeatedMotif(); ++m) {
      list<size_t> pos = kmr.getRepeatedMotifPositions(m);
      os << "Le motif " << (m + 1) << " correspondant à '";
      for (size_t i = 0; i < kmr.getRepeatedMotifMaxLength(); ++i) {
	os << ref[*(pos.begin()) + i];
      }
      os << "' apparaît aux positions : (";
      for (list<size_t>::const_iterator it = pos.begin(); it != pos.end(); ++it) {
	os << (it != pos.begin() ? ", " : "") << (*it + 1);
      }
      os << ")." << endl;
    }
  }
  os << endl;
  return os;
}
