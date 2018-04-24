#include <iostream>

template <typename T>
class MyVector{
 private:
  T *   _data;
  size_t     _n;
  size_t _alloc;

  void extend();
 public:
  MyVector();
  MyVector(size_t);
  ~MyVector();
  
  size_t size()const;
  T& at(size_t);
  const T& at(size_t)const;
  void push_back(T);
  
  void erase(int);          // remove the element at the given position
  int  find(const T&) const; // return the position of the element or -1
  void print();
};

/*
void write(std::ostream&, const MyVector<T>);
*/

#include "my-vector.tcc"
