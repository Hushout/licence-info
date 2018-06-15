# LES TYPES EN C

```
char:
-128 / +127
'0' = 48, 'A' = 65, 'a' = 97 (toupper = c - 32, tollower = c + 32)

int:
complement à 2
-32 768 / +32 767

float:
1 bit sur poid fort
```
# COMMANDES UTILES

```
pwd             => print work directory
touch "ficher"  => creer un nouveau fichier
```

# FONCTION C UTILES

**Fichier:**
```c
fopen(const char* chemin, const char* mode); => ouvre un fichire 
```
Mode:
```
r 	=> lecture seule
w 	=> ecriture seule
a 	=> ajout a la fin
rb+	=> ecriture lecture dans un fichier existant en binaire)
```
**Processus:**

```
fork() => -1 si erreur 
       => 0 si dans process fils
       => pid fils si dans pere
```

- alloue block controle dans table process
- copie processe present dans fils sauf pid et ppid
- alloue pid au fils
- associe segment données pile au fils
- mise du processus en execution

```
getpid()            => renvoie pid processus appelant
getppid()           => renvoie pid parent
exit(int status)    => termine le programme
assert(bool)        => avorter le programme
atexit(*function)   => execute fonction a la fin
on_exit(*function)  => same
```

**Differences thread et fork:**

- Les threads partagent une memoire virtuel, les fork non.
- Si le thread parant est tué alors tous les threads fils aussi, les fork non.

# COMPILATION

1. Prétraitement (preprocessing)
2. Analyse syntaxique (parsing)
3. Analyse sémantique
4. Géneration du code
5. Edition des liens

# PRINTF

```
p => adresse pointeur 
e => scientific notation (E uppercase)
o => unsigned octal
x => unsigned hexadecimal integer (X uppercase)
a => hexadecimal floating point (A uppercase)

(number)    => formatte la zone d'ecrite minimal
(space)     => si pas de signe alors un espace
-           => align le l'ecriture à gauche de la zone formaté
+           => affiche signe meme si positif
#           => affiche le 0x selon le format d'ecriture
0           => rempli la zone formatter avec des zeros
.(number)   => precision
*           => permet de mettre un paramètre un nombre 
```
**Exemple:**
```c
printf("%.*f", 3, 3.23);
```

# DROIT D'ACCES

| user | group | others |
|------|-------|--------|
| rwx  | rwx   | rwx    |

| symb | trad  | value |
|------|-------|-------|
| r    | read  | 4     |
| w    | write | 2     |
| x    | exec  | 1     |

4 + 2 + 1 => 7 (tous les droits)

# ENTREES SORTIES

```c
extern FILE* stdin; 	//(0)
extern FILE* stdout; 	//(1)
extern FILE* stderr; 	//(3)
```

Les descritpteur de ficher sont des entiers representant des fichier (0 = stdin)

# EXECUTION

```c
int execve(const char *filename, char *const argv[], char *const envp[]); 
```
execve est un appel système à la base des fonctions suivantes:

```
exec + l => argument sous forme de liste
exec + v => arg sous forme de tableau
exec + p => fichier a executer rechercher avec variable PATH
exec + e => nouvel environnement transmis au processus fils
```

# GESTION DES FICHIER

```c
struct stat
{
	dev_t st_dev; /* Périphérique */
	ino_t st_ino; /* Numéro i-noeud */
	umode_t st_mode; /* type de fichier et droits */
	nlink_t st_nlink; /* Nb liens matériels */
	uid_t st_uid; /* UID propriétaire */
	gid_t st_gid; /* GID propriétaire */
	dev_t st_rdev; /* Type périphérique */
	off_t st_size; /* Taille totale en octets */
	unsigned long st_blksize; /* Taille de bloc pour E/S */
	unsigned long st_blocks; /* Nombre de blocs alloués */
	time_t st_atime; /* Heure dernier accès */
	time_t st_mtime; /* Heure dernière modification */
	time_t st_ctime; /* Heure dernier changement état*/
};
```
```
Trouver le type du fichier          => st_mode & S_IFMT == (S_IFREG, S_IFDIR, S_IFLNK)
Trouver les droits sur le fichier   => st_mode & (S_IRUSR, S_IWGRP, S_IXOTH) 
```

```c
struct dirent
{
	long d_ino; /* inode number */
	off_t d_off; /* offset to this dirent */
	unsigned short d_reclen; /* length of this d_name */
	char d_name [NAME_MAX+1]; /* file name (null-terminated) */
}
```