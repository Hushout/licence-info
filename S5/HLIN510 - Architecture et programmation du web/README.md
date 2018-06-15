# PHP

### GENERAL

**Chaines de charactères:**

"$var" analyse si une variable est dans la chaine, contrairement à '$var' qui est plus rapide par contre, un alternative est : ' ' . $var . ' '

**Afficher bien les tableaux :**
```php
for($i = 0 ; $i < 100 ; $i++){}
foreach($tableau as $element){}
foreach($map as $key => $element){}
echo '<pre>';
print_r($coordonnees);
echo '</pre>';
```
**utile avec les tableaux:**
```php
array_key_exists('cle', $array) => verify si la clef existe
in_array('val', $array) 		=> verify si la valeur existe
array_search('val', $array) 	=> recupere la clé d'une valeur sinon faux
```
**Envoie de lien url:**
```html
<a href = "index.php?nom=boby&amp;prenom=josé">Envoyer</a>
(ne pas depasser 256 caractères sinon bug donc faire attention a get)
```

**Formulaire:**
```html
<form method="post/get" action="cible.php"></form>
get 	=> données envoyées par url recuperer avec $_GET (< 256 caractères)
post 	=> données non envoyées par url recuperer avec $_POST
```
**Injection html/javascript:**
La commande suivante empeche le navigateur d'interpreter le code html
```php
htmlspecialchars($_POST['prenom']);
```
Celle-ci les retire totalement
```php
strip_tags($_POST['prenom']);
```
### VARIABLE GLOBALES

```
$_SERVER['REMOTE_ADDR'] => adresse ip de l'utilisateur
$_SESSION               => les varibles stocker temporairement sur le serveur
$_COOKIE                => les variables enregistrer sur l'ordi du visiteur
$_FILES                 => listes des fichier envoyé par formulaire
```

### SESSIONS ET COOKIES

```
PHPSESSID           => identifiant session
session_start()     => demarre la session (utiliser avant le code html)
session_destroy()   => ferme la session
```

```php
           //nom      valeur    date d'expiration
setcookie('pseudo', 'M@teo21', time() + 365*24*3600, null, null, false, true);
``` 
(utilliser avant le code html, le dernier true = securité pour faille xss)

### FICHIER

changer les droit du fichier a 777 au prealable;

```php
$fichier = fopen('fichier.txt', 'r+');
//modifier le fichier ici
$c = fgetc($fichier);
$s = fgets($fichier);
fseek($fichier, position);
fputs($fichier, 'ma phrase');
$fclose($fichier);
```
```
r 	=> lecture seule
r+ 	=> lecture ecriture
a 	=> ecriture seule + creer  fichier si non existant
a+ 	=> lecture ecriture + creer fichier si non existant
```
### BASE DE DONNEES

**Avec query, immediat mais moins securisé:**
```php
$bdd = new PDO('mysql:host=localhost;dbname=test;charset=utf8','root','', array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION)););
$reponse = $bdd->query('SELECT * FROM TABLE');
$donnes = $reponse->fetch();
$reponse->closeCursor(); //fin d'une requete

//array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION)); => affiche les erreurs
```

**Avec prepare, plus adapté pour les variables et plus securisé:**
```php
$req = $bdd->prepare('SELECT nom FROM jeux_video WHERE possesseur = ? AND prix <= ?');
$req->execute(array($_GET['possesseur'], $_GET['prix_max']));
```

**Modifier les bdd directement:**
```php
$bdd->exec('INSERT INTO jeux_video VALUES(\'Battlefield 1942\', \'Patrick\', \'PC\', 45, 50, \'2nde guerre mondiale\')');
```

**Modifier les bdd avec preparation:**
```php
$req = $bdd->prepare('INSERT INTO jeux_video VALUES(:nom, :possesseur, :console, :prix, :nbre_joueurs_max, :commentaires)');

$req->execute(array(

    'nom' => $nom,

    'possesseur' => $possesseur,

    'console' => $console,

    'prix' => $prix,

    'nbre_joueurs_max' => $nbre_joueurs_max,

    'commentaires' => $commentaires

    ));

$nb_modifs = $bdd->exec('UPDATE jeux_video SET possesseur = \'Florent\' WHERE possesseur = \'Michel\'');
```

### DATES FRANCAISES
```php
$comments = $db->prepare('SELECT id, author, comment, DATE_FORMAT(comment_date, \'%d/%m/%Y à %Hh%imin%ss\') AS comment_date_fr FROM comments WHERE post_id = ? ORDER BY comment_date DESC');
$comments->execute(array($postId));
```

### REDIRECTION
```php
header('Location: minichat.php');
```

# JAVASCRIPT

### EVENEMENTS

**Body:**
```
onLoad      => chargement de la page
onUnLoad    => dechargement de la page
```
**Input/button:**
```
onClick     => clic souris
```
**Select:**
```
onChange    => modification objet
```
**General:**
```
onMouseOver => quand souris rentre
onMouseOut  => quand souris sort
```
**Form:**
```
onSubmit    => à l'envoie
```

**Fenetre:**
```javascript
alert("message !");
var boolean = confirm("message ?");
var reponse = prompt("message ?");
open('page.html', 'reponse', 'width=500,height=500');
```

### FONCTIONS

```javascript
<script>
	function mafonction(arg){}
</script>

document.write("<h1>Titre</h1>"); //=> ecrit la page web dynamiquement
setTimeout('maFonction()', 3000); //=> en ms
setTimeout('maFonction()', 3000); //=> en ms
```

### CONVERSIONS

```
text to number 	=> parsInt("text"); parsInt('text', base number)
number to text 	=> int1 + '' + int2;
===             => regarder l'egalité avec en plus l'égalité de type ! 
```

### TYPES

**typeof:**
```
'undefined'
'boolean'
'number'
'string'
'symbol'
'function'
'object'
```
### OBJETS

```javascript
var myObject = {
	item1: 'truc',
	item2: 'muche'
};

myObject.item1; 	//=> 'truc'
myObject['item2'];	//=> 'muche'

for(var id in object){
	console.log(object[i]);
}

for(let p of object){
	console.log(p);
}
```

### DOM

**Objet window implicite:**
```javascript
window.alert() == alert()
```
**Document, un element de window:**
```javascript
document.getElementById()
document.getElementsByTagName()
document.getElementsByName()

var query = document.querySelector('#id .class balise');
var queryAll = document.querySelectorAll('##menu .item span');
```
**Set/get:**
```html
<a id="myLink" href="http://www.un_lien_quelconque.com">Un lien modifié dynamiquement</a>
```
```javascript
var link = document.getElementById('myLink');
var href = link.getAttribute('href'); // On récupère l'attribut « href »
link.setAttribute('href', 'http://www.siteduzero.com'); 
```

où

```javascript
var href = link.href;
link.href = 'http://www.siteduzero.com'; 
```

**Assign:**
```javascript
document.getElementById('myId').className = 'blue';
```

**Recuperer html/text:**
```javascript
var div 	= document.getElementById('myDiv');
var html 	= div.innerHTML;
var text 	= div.innerText; == textContent;
```
**Se deplacer dans le dom:**
```
var parent = div.parentNode;
nodeType
nodeName
firstChild
lastChild

nextSibling 	=> noeud suivant
previousSibling => noeud precedant
```
(pour html uniquement rajouter 'Element')

**Exemble:**
```
firstElementChild
nextElementSibling
```
**Creation d'elements:**
```javascript
var newLink 	= document.createElement('a');
newLink.id    	= 'sdz_link';
newLink.href  	= 'http://www.siteduzero.com';
newLink.title 	= 'Découvrez le Site du Zéro !';
newLink.setAttribute('tabindex', '10');
```
**Ajout d'elements:**
```javascript
element.appendChild(newLink);
```
**creation d'elements texts:**
```javascript
var newLinkText = document.createTextNode("Le Site du Zéro");
newLink.appendChild(newLinkText);
```

```
replaceChild
removeChild     => renvoie l'element supprimer
insertBefore() 	=> insert avant un element
```
### JQUERY

```javascript
$(function(){
	// entrer le code JQUERY ici
});

$()                 //=> $(document) identiques
$(*)                //=> toutes les balises du document
$(selecteur)        //=> selectionne un element de la page (.class, ##id, h2)
$(selecteur).val()  //=> lit la valeur de la selection (text)
$('balise[class="maclasse"]')   //=> balise possedant un classe 'maclasse'
$('balise:even')                //=> selection les balises d'index pair
$('balise:eq(i)')               //=> selection la balise d'index i
$('balise:gt(i)')               //=> selection les balises apres l'index i
$('balise:lt(i)')               //=> selection les balises avant l'index i
$('balise').each(function(index){...}}]); //=> parcours les fils de l'element
```
### EVENEMENTS

```javascript
$(selecteur).click(function())
$(selecteur).scroll(function())
$(selecteur).mouseenter(function())
$(selecteur).mousedown(function())
$(selecteur).keypress(function())
```

### BIBLIOTHEQUE D3

```javascript
var canvas = d3.select('body').append('svg').attr('width', 100).attr('height', 100);

var circle = canvas.append("circle") 
		.attr("cx", 60).attr("cy",50)
		.attr("r", 20)
		.attr("fill", "red");

//.enter() => indique qu'on va creer des données
```