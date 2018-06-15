# OCAML:

### Compilation:

ocamlc fichier.ml -o sortie => compiler un fichier ml

use "fichier.ml" => inclus le fichier à l'interpreteur

Ctrl-D => termine l'interpreteur ocaml (exit 0;; egalement)

rlwrap ocaml => permet d'enregistrer les dernières commandes taper dans ocaml

### Basics:

| Type | Opérations |
|------|------------|
| int | +, -, *, /, mod, abs |
| float | +., -., *., /., **, sqrt, exp, log, cos, sin, tan |
| bool | not, &&, ||, =, <>, <, >, <=, >=, ==, != |
| char | int_of_char, char_of_int |
| string | ^ |
| list | @ |

```ocaml
let succ = (fun x -> x + 1);;

for i = 1 to 10 do
	(*...*)
done;;

while condition do
	(*...*)
done;;
```
### Recursif:

```ocaml

let rec size l = 
	if l = [] then 0
	else 1 + size(List.tl l);;

Avec les pattern match:

let rec size = function
	| [] -> 0
	| e :: tl -> 1 + (size tl);;
```

### Objets:

```ocaml
(unit == void)

class ['a] file = 
object (self)
	val mutable contenu = []
	method isEmpty = (List.length contenu) = 0
	method push (element : 'a) = contenu <- (element :: contenu)
	method pop = let res = List.hd(contenu) in contenu <- List.tl(contenu); res
	method top = List.hd(contenu)
end;;


let p = new file;;

p#push "coucou";;
p#push "hello";;
```

### Heritage:

```ocaml
class virtual container name =
    object (self)
      inherit widget name
      val mutable widgets = ( [] : widget list )
      method add w =
        widgets <- w :: widgets
      method get_widgets =
        widgets
      method repaint =
        List.iter (fun w -> w#repaint) widgets
    end;;
```

# SmallTalk:

### Heritage:

```smalltalk
Object subclass: #MonObjetMere
 	instanceVariableNames: 'varMere1 varMere2'
 	classVariableNames: ''
 	category: 'EXEMPLE'

MonObjetMere subclass: #MonObjetFils
 	instanceVariableNames: 'varFils1 varFils2'
 	classVariableNames: ''
 	category: 'EXEMPLE'
```

### Genericité:

```smalltalk
push: element
	(element isKindOf: typeElements)
	ifTrue: [ super push: element ]
	ifFalse: [ self error: ’Impossible d’’empiler ’ , element printString ,
	’ dans une pile de ’ , typeElements printString]
```

### Utiles:

C'est la methode qui est executer quand on utilise printIt.

```smalltalk
printOn: aStream
	aStream nextPutAll: ’une Pile, de taille: ’.
	capacite printOn: aStream.
	aStream nextPutAll: ’ contenant: ’.
	index printOn: aStream.
	aStream nextPutAll: ’ objets : (’.
	contenu do: [ :each | each printOn: aStream. aStream space ].
	aStream nextPut: $).
```

Autres fonctions utiles:

Execute un fonction sur toutes les variables du tableau contenu

```smalltalk
contenu do: [ :each | each function ].
```

Execute 20 fois la commande do

```smalltalk
1 to: 20 do: [...]
```