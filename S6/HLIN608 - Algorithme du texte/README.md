# GRAPHE DE BRUIJN

# GRAPHE K-MERS

Le terme k-mers ce réfère à toutes les sous-chaines possibles de taille k qu'une chaine contient.

Le nombre de k-mers possible dans une chaine de longueur L est **L − k + 1**.

# CHEVAUCHEMENTS ET BORDS

# ALIGNEMENTS DE SEQUENCES

# OPERATEUR BITS A BITS

Permet de faire des operations bits a bits sur des entiers non signés en c et c++.

## NOT <=> ~ (inverse les bits)

```c
unsigned a = 1;  	 // a == 0000 0000 0000 0001 (sur 16 bits)	
unsigned b = ~a; 	 // b == 1111 1111 1111 1110 (sur 16 bits)	
```

## AND <=> & (combine les bits avec un ET, permet de creer des masks)

```c
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a & b;  // c == 0000 0000 1111 0000 soit 0x00F0
```

## OR <=> | (combine les bits avec un OU)

```c 
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a | b;  // c == 1111 0000 1111 1111 soit 0xF0FF
```

## XOR <=> ^ (combine les bits avec un OU exclusif)

```c
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 0x00FF; // b == 0000 0000 1111 1111
unsigned c = a ^ b;  // c == 1111 0000 0000 1111 soit 0xF00F
```
## SHR <=> >> (Décalage à droite des bits)

```c
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 2; 	 // nombre de decalage vers la droite
unsigned c = a >> b; // c == 0011 1100 0011 1100 soit 0x3C3C 
```
## SHL <=> << (Décalage à gauche des bits)

```c
unsigned a = 0xF0F0; // a == 1111 0000 1111 0000
unsigned b = 2; 	 // nombre de decalage vers la gauche
unsigned c = a << b; // c == 1100 0011 1100 0000 soit 0xC3C0
```