#include <stdlib.h>
#include <stdio.h>

unsigned int sommeEntierConsecutifs(unsigned int n);
unsigned int sommeEntierConsecutifsIte(unsigned int n);
unsigned int sommeEntierConsecutifsRec(unsigned int n);

unsigned int sommeEntierConsecutifsGeneral(unsigned int a, unsigned int b);
unsigned int sommeEntierConsecutifsGeneralIte(unsigned int a, unsigned int b);
unsigned int sommeEntierConsecutifsGeneralRec(unsigned int a, unsigned int b);

unsigned int sommeEntierConsecutifs(unsigned int n){
	return sommeEntierConsecutifsGeneral(1, n);
}

unsigned int sommeEntierConsecutifsIte(unsigned int n){
	return sommeEntierConsecutifsGeneralIte(1, n);
}

unsigned int sommeEntierConsecutifsRec(unsigned int n){
	return sommeEntierConsecutifsGeneralRec(1, n);
}

unsigned int sommeEntierConsecutifsGeneral(unsigned int a, unsigned int b){
		/*si a et b pair	  decalement d'un bit			 decalement d'un bit*/
	return ((a&1) == (b&1)) ? ((a + b) >> 1) * (b - a + 1) : ((b - a + 1) >> 1) * (a + b);
}

unsigned int sommeEntierConsecutifsGeneralIte(unsigned int a, unsigned int b){
	
	unsigned int sum = 0;

	for(unsigned int i = a ; i <= b ; i++)
		sum+=i;

	return sum;
}

unsigned int sommeEntierConsecutifsGeneralRec(unsigned int a, unsigned int b){
	return b == a ? a : b + sommeEntierConsecutifsGeneralRec(a, b - 1);
}

int main(int argc, char const *argv[])
{
	if(argc == 2){
		printf("SommeEntierConsecutifs(%s) = %u\n", argv[1], sommeEntierConsecutifs(atoi(argv[1])));
		printf("SommeEntierConsecutifsIte(%s) = %u\n", argv[1], sommeEntierConsecutifsIte(atoi(argv[1])));
		printf("SommeEntierConsecutifsRec(%s) = %u\n", argv[1], sommeEntierConsecutifsRec(atoi(argv[1])));
	}
	else if(argc == 3){
		printf("sommeEntierConsecutifsGeneral(%s, %s) = %u\n", argv[1], argv[2], sommeEntierConsecutifsGeneral(atoi(argv[1]), atoi(argv[2])));
		printf("sommeEntierConsecutifsGeneralIte(%s, %s) = %u\n", argv[1], argv[2], sommeEntierConsecutifsGeneralIte(atoi(argv[1]), atoi(argv[2])));
		printf("sommeEntierConsecutifsGeneralRec(%s, %s) = %u\n", argv[1], argv[2], sommeEntierConsecutifsGeneralRec(atoi(argv[1]), atoi(argv[2])));
	}
	else{
		printf("usage: %s <entier> (optionnels <entier>)", argv[0]);
	}
	return 0;
}