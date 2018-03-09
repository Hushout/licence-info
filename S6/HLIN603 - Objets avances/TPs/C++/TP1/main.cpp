#include <iostream>
#include "Strophe.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Strophe st;

	st.saisie(cin);

	st.affiche(cout);

	return 0;
}