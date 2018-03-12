#ifndef DICO_H
#define DICO_H

#include <map>

template <typename K, typename V>
class Dico
{
private:
	std::map<K,V> data;

public:
	Dico();
	virtual ~Dico();

	virtual V get(K key);
	virtual void put(K key, V value);

	virtual bool empty();
	virtual bool size();
	virtual bool exist(K key);

	virtual void print();
};

#include "dico.cc"

#endif 