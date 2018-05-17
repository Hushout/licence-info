# GRAPHE DE BRUIJN:

Le graphe B ( 2 , 3 ) {\displaystyle B(2,3)} B(2,3) ci-contre est construit sur un alphabet binaire A = { 0 , 1 } {\displaystyle A=\{0,1\}} A=\{0,1\} pour des mots de longueur n = 3 {\displaystyle n=3} n=3. Les 2 3 = 8 {\displaystyle 2^{3}=8} 2^{3}=8 mots de longueur 3 sur l'alphabet binaire sont :

    000 ,   001 ,   010 ,   011 ,   111 ,   110 ,   101 ,   100 {\displaystyle 000,\ 001,\ 010,\ 011,\ 111,\ 110,\ 101,\ 100} 000,\ 001,\ 010,\ 011,\ 111,\ 110,\ 101,\ 100.

Il existe par exemple un arc allant du sommet 000 {\displaystyle 000} 000 au sommet 001 {\displaystyle 001} 001 car le suffixe de longueur 2 de 000 {\displaystyle 000} 000 est égal au préfixe de longueur 2 de 001 {\displaystyle 001} 001. De même, il existe un arc allant du sommet 100 {\displaystyle 100} 100 au sommet 000 {\displaystyle 000} 000 car le suffixe de longueur 2 de 100 {\displaystyle 100} 100 est égal au préfixe de longueur 2 de 000 {\displaystyle 000} 000.

Le graphe B ( n , 1 ) {\displaystyle B(n,1)} B(n,1) est formé de n {\displaystyle n} n sommets, un pour chaque lettre. De chaque sommet partent n {\displaystyle n} n arcs, il y a donc n 2 {\displaystyle n^{2}} n^{2} arcs.

# GRAPHE K-MERS:

Le terme k-mers ce réfère à toutes les sous-chaines possibles de taille k qu'une chaine contient.

Le nombre de k-mers possible dans une chaine de longueur L est **L − k + 1**.



# CHEVAUCHEMENTS ET BORDS:

# ALIGNEMENTS DE SEQUENCES:

# OPERATEUR BITS A BITS:

Permet de faire des operations bits a bits sur des entiers non signés en c et c++.

## NOT <=> ~ (inverse les bits)

``` 
unsigned a = 1;  	 // a == 0000 0000 0000 0001 (sur 16 bits)	
unsigned b = ~a; 	 // b == 1111 1111 1111 1110 (sur 16 bits)	
```

## AND <=> & (combine les bits avec un ET, permet de creer des masks)

``` 
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a & b;  // c == 0000 0000 1111 0000 soit 0x00F0
```

## OR <=> | (combine les bits avec un OU)

``` 
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a | b;  // c == 1111 0000 1111 1111 soit 0xF0FF
```

## XOR <=> ^ (combine les bits avec un OU exclusif)

```
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a ^ b;  // c == 1111 0000 0000 1111 soit 0xF00F
```
## SHR <=> >> (Décalage à droite des bits)

```
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 2; 	 // nombre de decalage vers la droite
unsigned c = a >> b; // c == 0011 1100 0011 1100 soit 0x3C3C 
```
## SHL <=> << (Décalage à gauche des bits)

```
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 2; 	 // nombre de decalage vers la gauche
unsigned c = a << b; // c == 1100 0011 1100 0000 soit 0xC3C0
```