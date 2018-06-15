Compiler quelque fichiers avec leurs noms:

```bash
javac <fileName> <fileName> <fileName> ... <fileName>
```
Compiler tous les fichier du dossier:

```bash
javac *.java
```
Compiler tous les fichiers du dossier et des sous dossier recursivement:

```bash
find . -name "*.java" > sources.txt
javac @sources.txt
```