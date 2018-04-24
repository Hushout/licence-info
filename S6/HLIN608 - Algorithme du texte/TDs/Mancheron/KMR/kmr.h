#ifndef __KMR_H__
#define __KMR_H__

#include <string>
#include <list>
#include <vector>
#include <map>

class KMR {
 private:
  friend std::ostream &operator<<(std::ostream &os, const KMR &kmr);
  const std::string &ref_seq;

  size_t a, b, e, n;
#ifdef __USING_VECTORS__
  std::vector<size_t> v_a;
#else
  std::map<size_t, size_t> v_a;
#endif

  void init();
  bool next_iter();

 public:
  KMR(const std::string &ref_seq = "");

  const std::string &getRefSeq() const;
  size_t getRepeatedMotifMaxLength() const;
  size_t getNbRepeatedMotif() const;
  std::list<size_t> getRepeatedMotifPositions(size_t motif) const;

};

std::ostream &operator<<(std::ostream &os, const KMR &kmr);

#endif
