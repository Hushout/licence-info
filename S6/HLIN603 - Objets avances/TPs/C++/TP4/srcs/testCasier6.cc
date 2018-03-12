#include <iostream>
#include "Casier6.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Casier6<Oeuf>* C = new Casier6<Oeuf>();
	Oeuf* O = new Oeuf();

	C->range(O, 4);

	return 0;
}