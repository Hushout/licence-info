//////////// Tableau Int Extensible //////////////////

template <typename T>
void MyVector<T>::extend() {
  if (_n<_alloc) return;
  _alloc=2*_n;
  T* tmp=new T[_alloc];
  for(size_t i=0;i<_n;i++){tmp[i]=_data[i];}
  delete[] _data;
  _data=tmp;
}

template <typename T>
MyVector<T>::MyVector() : _data(new T[1]), _n(0), _alloc(1) {}

template <typename T>
MyVector<T>::MyVector(size_t n) : _data(new T[n]), _n(n), _alloc(n) {}

template <typename T>
MyVector<T>::~MyVector(){delete[] _data;}


template <typename T>
size_t MyVector<T>::size()const {return _n;}

template <typename T>
T& MyVector<T>::at(size_t i) {return _data[i];}

template <typename T>
const T& MyVector<T>::at(size_t i)const {return _data[i];}

template <typename T>
void MyVector<T>::push_back(T x) {
  extend();
  _data[_n]=x;
  _n++;
}

template <typename T>
void MyVector<T>::erase(int idx){
  if (idx>=0 && idx<(int)_n){
    for(size_t i=idx;i<_n-1;i++)
      _data[i]=_data[i+1];
    _n--;
  }  
}


template <typename T>
int MyVector<T>::find(const T& C) const{
  for (size_t i=0;i<_n;i++)    
    if (C == _data[i]) return i;		
  return -1;
}

template <typename T>
void MyVector<T>::print(){
  for (size_t i=0;i<_n;i++)
    std::cout << _data[i] << std::endl;
}

/*
void write(std::ostream& os, const MyVector&){
  for (size_t i=0;i<T.size();i++)
    os<<T.at(i)<<" ";
  os<<std::endl;
}
*/
