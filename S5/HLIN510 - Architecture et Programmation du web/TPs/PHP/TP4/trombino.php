<!doctype html> <!-- fichier trombino.php -->
<html lang="fr">
<head>
  <meta charset="utf-8" /> 
  <title>trombinoscope</title>
</head>

<body>
<center>
  <h1>Trombinoscope</h1>
</center>

<?php
ini_set('display_errors', 1); error_reporting(E_ALL);
include("secret.php");
try {
  $dbh = new PDO('mysql:host=venus;dbname=mmeynard;charset=UTF8', $login, $passwd);
} catch (PDOException $e) {
  print "Impossible d'ouvrir la base de données !: " . $e->getMessage() . "<br/>";
  die();
}
   
// formulaire de sélection des options désirées et de l'ordre d'affichage
echo "<form name='fopt' method='POST'>\n"; 
echo '<table><tbody><tr align="center" valign="top">',"\n";

$req="SELECT code,nom FROM options;";
$res = $dbh->query($req) or die("Requête $req impossible");

// liste des options
echo "<td><b>Sélectionnez une ou plusieurs options, </b><br>\n";
echo '<select name="listopt[]" size="',$res->rowCount(),'" multiple>', "\n";
foreach ($res as $ligne ){ // tq il reste des options
  echo "<option value='{$ligne['code']}' ",
    (isset($_POST['listopt']) && in_array($ligne['code'],$_POST['listopt'])?
     "selected":""), ">{$ligne['nom']}</option>\n";
}
echo "</select></td>\n";

// ordre d'affichage
echo "<td><b>puis choisissez l'ordre d'affichage, </b><br>\n";
$lordre=array("nom"=>"par nom et prénom", "option"=>"par option", 
	      "groupe"=>"par groupe", "statut"=>"par statut (FI/FP)");
echo '<select name="ordre">', "\n";
foreach($lordre as $o=>$ch){
  echo "<option ",(!empty($_POST['ordre']) && !strcmp($_POST['ordre'],$o)?"selected":""),
    " value='$o'>$ch\n";
}
echo "</select></td>\n", '<td><b>enfin validez !</b><br>',"\n";
echo '<input type="SUBMIT" name="valider" value="valider">',"\n";
echo "</td></tr></tbody></table>\n</form>\n\n";

// tableau des infos d'étudiants : requête paramétrée par le form
echo '<table border="1"> <tbody>',"\n"; // début du tableau HTML

$req = "SELECT e.nom,prenom,statut,groupe,e.email,o.nom as optnom,e.numStageA ";
$req.= "FROM etudiant e LEFT JOIN options o ON e.opt=o.code ";
// Si $listopt[] est vide (debut ou tout deselectionne : on select tous)
if (!empty($_POST['listopt']) && $nbopt=count($_POST['listopt'])){  // au moins 1 option selectionnée
  $ensemble="('{$_POST['listopt'][0]}'" ; // 1ere option
  for ($i=1;$i<$nbopt;$i++){
    $ensemble.=",'{$_POST['listopt'][$i]}'"; // ajouter les autres options
  }
  $req.= "WHERE e.opt IN $ensemble) ";
}
if (!empty($_POST['ordre'])){
 switch ($_POST['ordre']){	 
 case "option" : $req.= "ORDER BY optnom, nom, prenom;";break;
 case "groupe" : $req.= "ORDER BY groupe, nom, prenom;";break;
 case "statut" : $req.= "ORDER BY statut, nom, prenom;";break;
 default : $req.= "ORDER BY nom, prenom;";break;
 }
}else{ $req.= "ORDER BY nom, prenom;";
}
//echo $req;
$res = $dbh->query($req) or die("Requête $req impossible");

// Début de l'affichage
$nbcol=8; // nombre de colonnes (étudiants) par ligne du tableau HTML
$numcol=0; //numéro de la colonne courante
foreach ($res as $ligne){ // tq il reste des étud
  if ($numcol==0){
    echo '<tr align="center" valign="top">',"\n";
  }
# ETUDIANT
#$c='<td><img width=50 height=80 src="' . $ligne["email"] . '.jpg"><br>';
  $c='<td>'.$ligne["nom"].' '.$ligne["prenom"].'<br>';
  $c=$c.'groupe '.$ligne["groupe"].' '.$ligne["statut"];
  $c=$c.'<br><a href="mailto:'.$ligne["email"].'@info-ufr.univ-montp2.fr">';
  $c=$c.$ligne["email"].'</a>';
  $c.=($ligne["optnom"] ? '<br>option '.$ligne["optnom"] : '');
  $c.=($ligne["numStageA"] ? '<br>stage A. '.$ligne["numStageA"] : '');
  $c.='</td>' ;
  echo $c,"\n";
  $numcol++; // colonne suivante
  if ($numcol==$nbcol){
    echo "</tr>\n";   // fin de ligne
    $numcol=0;      // réinit
  }
}
echo "</tbody> </table>\n\n" ;
$dbh=null;

?>
<br>

<h1><a href=".">Retour</a></h1>

</body>
</html>
