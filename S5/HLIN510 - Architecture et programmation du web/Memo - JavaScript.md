# EVENEMENTS

**Body:**
onLoad 		=> chargement de la page
onUnLoad	=> dechargement de la page

**Input/button:**
onClick 	=> clic souris

**Select:**
onChange 	=> modification objet

**General:**
onMouseOver => quand souris rentre
onMouseOut 	=> quand souris sort

**Form:**
onSubmit 	=> a l'envoe

**Fenetre:**
```javascript
alert("message !");
var boolean = confirm("message ?");
var reponse = prompt("message ?");
open('page.html', 'reponse', 'width=500,height=500');
```

# FONCTIONS

<script>
	function mafonction(arg){}
</script>

document.write("<h1>Titre</h1>"); => ecrit la page web dynamiquement
setTimeout('maFonction()', 3000); => en ms
setTimeout('maFonction()', 3000); => en ms

# CONVERSIONS

text to number 	=> parsInt("text"); parsInt('text', base number)
number to text 	=> int1 + '' + int2;
=== 			=> regarder l'egalité avec en plus l'égalité de type ! 

# TYPES

**typeof:**
'undefined'
'boolean'
'number'
'string'
'symbol'
'function'
'object'

# OBJETS

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

# DOM

**Objet window implicite:**
window.alert() == alert()

**Document, un element de window:**
document.getElementById()
document.getElementsByTagName()
document.getElementsByName()

var query 		= document.querySelector('#id .class balise');
var queryAll 	= document.querySelectorAll('##menu .item span');

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
document.getElementById('myId').className = 'blue';

**Recuperer html/text:**
var div 	= document.getElementById('myDiv');
var html 	= div.innerHTML;
var text 	= div.innerText; == textContent;

**Se deplacer dans le dom:**
var parent = div.parentNode;
nodeType
nodeName
firstChild
lastChild

nextSibling 	=> noeud suivant
previousSibling => noeud precedant

(pour html uniquement rajouter 'Element')

**Exemble:**
firstElementChild
nextElementSibling

**Creation d'elements:**
var newLink 	= document.createElement('a');
newLink.id    	= 'sdz_link';
newLink.href  	= 'http://www.siteduzero.com';
newLink.title 	= 'Découvrez le Site du Zéro !';
newLink.setAttribute('tabindex', '10');

**Ajout d'elements:**
eleement.appendChild(newLink);

**creation d'elements texts:**
var newLinkText = document.createTextNode("Le Site du Zéro");
newLink.appendChild(newLinkText);

replaceChild
removeChild 	=> return l'element supprimer
insertBefore() 	=> insert avant un element

# JQUERY

```javascript
$(function(){
	// entrer le code JQUERY ici
});

$() 		 		//=> $(document) identiques
$(*) 		 		//=> toutes les balises du document
$(selecteur) 		//=> selectionne un element de la page (.class, #id, h2)
$(selecteur).val() 	//=> lit la valeur de la selection (text)
$('balise[class="maclasse"]') 	//=> balise possedant un classe 'maclasse'
$('balise:even') 				//=> selection les balises d'index pair
$('balise:eq(i)') 				//=> selection la balise d'index i
$('balise:gt(i)') 				//=> selection les balises apres l'index i
$('balise:lt(i)') 				//=> selection les balises avant l'index i
$('balise').each(function(index){...}}]); //=> parcours les fils de l'element
```
# EVENEMENTS

```javascript
$(selecteur).click(function())
$(selecteur).scroll(function())
$(selecteur).mouseenter(function())
$(selecteur).mousedown(function())
$(selecteur).keypress(function())
```

# BIBLIOTHEQUE D3

```javascript
var canvas = d3.select('body').append('svg').attr('width', 100).attr('height', 100);

var circle = canvas.append("circle") 
		.attr("cx", 60).attr("cy",50)
		.attr("r", 20)
		.attr("fill", "red");

//.enter() => indique qu'on va creer des données
```