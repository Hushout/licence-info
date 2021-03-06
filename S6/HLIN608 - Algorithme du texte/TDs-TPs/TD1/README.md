//////////// Question 1:

```c
unsigned int SommeEntiersConsecutif(unsigned int n){
	unsigned int sum = 0;

	for(unsigned int i = 1 ; i <= n ; i++){
		sum+= i;
	}

	return sum;
}
```

Mémoire: O(1)
Temps: O(n);

ou

```c
unsigned int SommeEntiersConsecutif(unsigned int n){
	return (n * (n + 1))/2;
}
```

Mémoire: O(1)
Temps: O(n);

ou

```c

unsigned int SommeEntiersConsecutif(unsigned int n){
	if(n == 0)
		return 0;
	else
		return n + SommeEntiersConsecutif(n - 1);
}
```

Mémoire: O(n) supporter en O(1) pour certains compilateur
Temps: O(n)

ou

```c

unsigned int SommeEntiersConsecutif(unsigned int n){
	return SommeEntiersConsecutifGeneral(0, n);
}
```

Mémoire: celle de SommeEntiersConsecutifGeneral(0, n)
Temps: celle de SommeEntiersConsecutifGeneral(0, n)

//////////// Question 2:

```c
unsingned int SommeEntiersConsecutifGeneral(unsigned int a, unsigned int b){
	unsigned int sum = 0;

	for(unsigned int i = a ; i <= b ; i++){
		sum+= i;
	}

	return sum;
}
```

Mémoire: O(1)
Temps: O(b-a)

ou

```c
unsingned int SommeEntiersConsecutifGeneral(unsigned int a, unsigned int b){
	return (a + b)*(b - a + 1)/2; // problème de depassement de la taille de unsigned int
	//return (a + b) / 2 * (b - a + 1) //meilleur solution mais problème de division avec (a + b) impair fonction pair efficace avec un mask:

	/*      si a et b pair
	return ((a&1) == (b&1)) ? (a + b)/2 * (b - a + 1) : (b - a + 1)/2 * (a + b);
	division pas très efficace or la division par 2 revien a decaler les bit de 1 ce qui est plus efficace

	reviens a dire:
			si a et b pair	  decalement d'un bit			 decalement d'un bit
	return ((a&1) == (b&1)) ? ((a + b) >> 1) * (b - a + 1) : ((b - a + 1) >> 1) * (a + b);

	*/
}
```

Mémoire: O(1)
Temps: O(1)

ou

```c
unsigned int SommeEntiersConsecutif(unsigned int a, unsigned int b){
	if(a == b)
		return b;
	else
		return a + SommeEntiersConsecutifGeneral(a + 1, b);
}
```

Mémoire: O(b-a)
Temps: O(b-a)

ou

```c
unsingned int SommeEntiersConsecutifGeneral(unsigned int a, unsigned int b){
	return (SommeEntiersConsecutif(b) - SommeEntiersConsecutif(a) + a);
}
```

Mémoire: 2 * complexité de SommeEntiersConsecutif
Temps: 2 * complexité de SommeEntiersConsecutif

//Algo naif important pour faire des test de comparation fiable



