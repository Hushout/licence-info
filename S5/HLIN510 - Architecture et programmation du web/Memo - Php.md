# GENERAL

"$var" analyse si une variable est dans la chaine, contrairement à '$var' qui est plus rapide par contre, un alternative est : '' . $var . ''

**Afficher bien les tableaux :**
for($i = 0 ; $i < 100 ; $i++)
foreach($tableau as $element)
foreach($map as $key => $element)
echo '<pre>';
print_r($coordonnees);
echo '</pre>';

**utile avec les tableaux:**
array_key_exists('cle', $array) => verify si la clef existe
in_array('val', $array) 		=> verify si la valeur existe
array_search('val', $array) 	=> recupere la clé d'une valeur sinon faux

**Envoie de lien url:**
<a href = "index.php?nom=boby&amp;prenom=josé">Envoyer</a>
(ne pas depasser 256 caractères sinon bug donc faire attention a get)

**Formulaire:**
<form method="post/get" action="cible.php"></form>
get 	=> données envoyées par url recuperer avec $_GET (< 256 caractères)
post 	=> données non envoyées par url recuperer avec $_POST

**Injection html/javascript:**
la commande suivante empeche le navigateur d'interpreter le code html
```php
htmlspecialchars($_POST['prenom']);
```
celle-ci les retire totalement
```php
strip_tags($_POST['prenom']);
```
# VARIABLE GLOBALES

```
$_SERVER['REMOTE_ADDR'] => adresse ip de l'utilisateur
$_SESSION 				=> les varibles stocker temporairement sur le serveur
$_COOKIE 				=> les variables enregistrer sur l'ordi du visiteur
$_FILES 				=> listes des fichier envoyé par formulaire
```

# SESSIONS ET COOKIES

PHPSESSID 			=> identifiant session
session_start() 	=> demarre la session (utiliser avant le code html)
session_destroy() 	=> ferme la session

```php
		  //nom		valeur		date d'expiration
setcookie('pseudo', 'M@teo21', time() + 365*24*3600, null, null, false, true);
``` 
(utilliser avant le code html, le dernier true = securité pour faille xss)

# FICHIER

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

r 	=> lecture seule
r+ 	=> lecture ecriture
a 	=> ecriture seule + creer  fichier si non existant
a+ 	=> lecture ecriture + creer fichier si non existant

# BASE DE DONNEES

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

# DATES FRANCAISES
```php
$comments = $db->prepare('SELECT id, author, comment, DATE_FORMAT(comment_date, \'%d/%m/%Y à %Hh%imin%ss\') AS comment_date_fr FROM comments WHERE post_id = ? ORDER BY comment_date DESC');
$comments->execute(array($postId));
```

# REDIRECTION
```php
header('Location: minichat.php');
```


