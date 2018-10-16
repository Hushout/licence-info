# 1 Compréhension du cours

#### Question 1: En c, que signifient les mots suivants: NULL, "", ? Exprimez leur valeur en Hexadécimal. (2 pts)

- NULL: macro representant un pointeur non initialisé et défini par ((void*)0) dans stddef.h.
- "": chaine de caractère vide. Contient uniquement le caractère de fin '\0' ayant pour valeur hexadecimal...

#### Question 2: Comment comparer deux chaines de caractères en C ? Donnez 3 exemples significatifs. (2 pts)

On utilise la fonction int strcmp(const char* s1, const char* s2) qui fait un comparaison lexicographique.

si s1 < s2 (ex: strcmp("ab", "ba")), le resultat est < 0.
si s1 = s2 (ex: strcmp("ab", "ab")), le résultat est 0.
si s1 > s2 (ex: strcmp("ba", "ab")), le résultat est > 0.

#### Question 3: Quel est l'appel système permettant d'accéder à un i-noeud (inode) ? Décrivez succintement 4 champs d'une entrée de cette table. (2 pts)

Il s'agit de la fonction stat()
numero: indentifiant dans la table.
propriétaire: utilisateur (uid) et groupe proprietaire (gid).
...
...

#### Question 4: Un signal envoyé à un processus contient-il l'identification du processus émetteur ? Comment s'envoyer un signal après une temporisation de 5 secondes ? (2 pts)

On ne connait pas le processus émetteur.
Pour s'envoyer un signal après temporisation de 5 secondes il faut utiliser l'appel système alarm(5). Cela enverra un SIGALARM après 5 secondes.

=======================================

On souhaite écrire un programme C affichant la liste triée en ordre des mots et de leur nombre d'occurences d'un tel fichier dont le nom est passé en paramètre à la ligne de commande.

```
$ tricpt exemple.txt
ami (1), en (2), leo (2), nom (1), etc...
```

Afin de décomposer le travail, on souhaite ecrire une fonction lire_mot dont la spécification suit:

```c
/** @function lire_mot 
 * lecture séquentielle du fichier (déjà ouvert), en ignorant ce qui n'est pas une letre minuscule, et retourne dans le buffer une copie du premier mot trouvé sous une forme d'une chaine c.
 * @param f fichier déjà ouvert en leture.
 * @param buf un tampon de caractètres (déjà alloué) qui contiendra le mot lu au retour.
 * @return 0 si EOF, 1 si trouvé un mot (qui sera stocké dans buf).
 */
```

#### Question 5: Ecrire l'algorithme de la fonction lire_mot. (3 pts)

```
Algorithme: lire_mot(f, buf)
Debut
	i <- 0

	tant que c <- lire_caractère(f) et est_lettre_minuscule(c) faire
		buf[i] <- c
		i++;
	fin tant que

	buf[i] <- '\0' 

	si c = EOF alors retourner 0;
	sinon retourner 1;
fin
```

#### Question 6: Ecrire la fonction C lire_mot correspondant à cet algorithme En utilisant que des appels systèmes. (1 pt)

```c
int lire_mot(int f, char buf[1024]){
	
	char c;
	int i = 0;

	while(read(f, &c, 1) && (c <= 'z' && c >= 'a')){
		buf[i++] = c;
	}

	buf[i] = '\0';

	if(i == 0){ return 0; }

	return 1;
}
```

=======================================

Selon le modèle du crible d'Eratosthène parallèle, on souhaite paralléliser le programme tricpt en utilisant des processus lourds et des tubes anonymes. Chaque processus crée  exécutera la fonction tricptpar qui: récupèrera dans son tube d'entrée une séquence de caracètres contenant  la liste des mots. Sélectionnera et affichera le plus petit ainsi que son nombre d'occurence qu'il aura compté tout en transmettant les autres via un tube de sortie à un processus enfant qu'il aura crée. La fonction principale (main) n'aura qu'à créer le premier tube et le premire fils, puis recopiera le fichier dans le tube.

#### Question 7: Dessiner un shéma décrivant les processus crées ainsi que les tubes et leur contenu en utilisant l'exemple de texte suivant: ed baba abc baba. (1 pt)

```	
   tube_1       tube_2       tube_3
P1 ========> P2 ========> P3 ========> P4 
          affiche       affiche     affiche
          abc (1)       baba (1)    cd (1)
```

#### Question 8: Ecrire l'algorithme de la fonction main(). (1 pt)

```
Algorithme main
Debut
	f <- ouverture fichier fourni dans argv
	pipe_out <- creer_tube()
	pid <- fork()

	si pid = 0 alors
		tricptpar(pipe_out)
		fermer(pipe_out)
	sinon si pid > 0 alors
		tant que c = lire_caractère(f) faire
			ecrire_dans(pipe_out, c)
		fin tant que
	fin si

	attendre()
	
	retourner 0
fin
```

#### Question 9: Ecrire l'algorithme de la fonction, tricptpar(int in[2]). (4 pts)

```
Algorithme tricptpar(pipe_in)
Debut
	fermer_ecriture(pipe_in)

	si !lire_mot(pipe_in, mot_lu) alors
		fin algorithme
	fin si

	creer_tube(pipe_out)

	pid <- fork()

	si pid = 0 alors
		tricptpar(pipe_out)
		fermer_lecture(pipe_out)
	sinon si pid > 0 alors
		plus_petit_mot <- mot_lu
		occ <- 1
		tant que lire_mot(pipe_in, mot_lu) faire
			si plus_petit_mot = mot_lu alors
				occ++
			sinon si plus_petit_mot < mot_lu alors 
				ecrire_dans(pipe_out, mot_lu)
			sinon
				ecrire_dans(pipe_out, plus_petit_mot)
				plus_petit_mot <- mot_lu
				occ <- 1
			fin si
		fin tant que
	fin si

	attendre()
fin
```

#### Question 10: Ecrire le programme C tricpt.c. (2 pts)

```c
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void tricptpar(int in[2]);
int lire_mot(int f, char buf[1024]);

int main(int argc, char* argv[]){

	if(argc < 2){
		fprintf(stderr, "Usage : %s [FICHIER]\n", argv[0]);
		return 1;
	}

	int f = open(argv[1]);

	if(f == -1){
		perror("");
		return 2;
	}

	int pipe_out[2];

	if(pipe(pipe_out) == -1){
		perror("");
		return 3;
	}

	int pid = fork();

	switch(pid){
		case 0: 
			tricptpar(pipe_out);
			close(out[0]);
			break;
		case -1:
			perror("");
			return 4;
			break;
		default:
			char buf[1024] = "";

			while(lire_mot(f, buf)){
				write(out[1], buf, sizeof(buf));
			}

			close(out[1]);
			wait(NULL);
	}
	return 0;
}

void tricptpar(int pipe_in[2]){
	
	close(pipe_in[1]);

	char mot_lu[1024];

	if(lire_mot(pipe_in, mot_lu)){ return; }

	int pipe_out[2];
	pipe(pipe_out);

	int pid = fork();

	if(pid == 0){
		tricptpar(pipe_out);
		close(pipe_out[0]);
	}
	else if(pid == -1){
		perror("");
		exit(4);
	}
	else{

		char plus_petit_mot[1024] = "";
		
		strcpy(plus_petit_mot, mot_lu);
		
		int occ = 1;
		
		while(lire_mot(pipe_in[0], mot_lu)){

			int cmp = strcmp(plus_petit_mot, mot_lu);

			if(cmp == 0){ occ++; }
			else if(cmp < 0){ write(pipe_out[1], mot_lu, sizeof(mot_lu)); }
			else{
				write(pipe_out[1], plus_petit_mot, sizeof(plus_petit_mot));
				strcpy(plus_petit_mot, mot_lu);
				occ = 1;
			}
		}

		close(pipe_out[1]);
		close(pipe_in[0]);

		printf("%s (%i)\n", plus_petit_mot, occ);
		fflush(stdout);

		wait(NULL);
	}
}
```