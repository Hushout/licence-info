<?php				//error_reporting(E_ALL);//pour déboguer
ini_set('display_errors', 1); error_reporting(E_ALL);     
include "Mastermind.php";
session_start(); 
define('PREFIXE','master_');

if (isset($_POST['sauve']) && isset($_POST['nom']) && isset($_SESSION['jeu'])){
  // sauver la partie en cours dans un cookie 
  setcookie(PREFIXE.$_POST['nom'],serialize($_SESSION['jeu']),time()+86400) or 
    print 'Impossible de sauvegarder la partie en cours !';
  echo "Partie en cours sauvegardée sous le nom : {$_POST['nom']} !<br/>\n";
}else if(isset($_POST['restaure']) && isset($_POST['nom'])){
  // restaurer
  $n=PREFIXE.$_POST['nom'];
  if (isset($_COOKIE[$n])){
    // ATTENTION au stripslashes($_COOKIE[$n]) !!!
     $_SESSION['jeu']=unserialize(get_magic_quotes_gpc()?
		       stripslashes($_COOKIE[$n]):$_COOKIE[$n]);
    echo("Partie restaurée : {$_POST['nom']} !");
  } else {
    echo("Impossible de restaurer la partie {$_POST['nom']} !");
  }
}else if (isset($_POST['nouveau'])){
  $_SESSION=array();
}
?>
<!doctype html>
<html lang="fr">
<head>
<meta charset="utf-8" /> 
<title>Site de jeu : Mastermind avec cookie</title>
</head>
<body>
<h1 align="center">Mastermind avec cookie</h1>

<form action="<?php echo "{$_SERVER['PHP_SELF']}".(strlen(SID)?'?'.SID:''); ?>" method="post">
<table>
 <tr>
  <th align="left" valign="middle">Numéro</th>
  <th align="left" valign="middle">Proposition</th>
  <th align="left" valign="middle">Bien placé(s)</th>
  <th align="left" valign="middle">Mal placé(s)</th>
 </tr>
<?php
$i=1;
if(isset($_SESSION['jeu'])){	// restauration objet Mastermind
  $jeu=$_SESSION['jeu'];
  foreach($jeu->getEssais() as $code=>$res){
    echo "<tr><td>$i</td><td>".$code."</td><td>".$res['bon'].
      "</td><td>".$res['mal']."</td></tr>\n";
    $i++;
  }
}else {				// début de partie
  $jeu=new Mastermind();
  $_SESSION['jeu']=$jeu;
}
if (isset($_POST['prop'])){		// une proposition
  $r=$jeu->test($_POST['prop']); // résultat

  if ($r===false){		// proposition invalide
    echo "<tr><td>Incorrect</td><td>".$_POST['prop'].
      "</td><td></td><td></td></tr>\n";
  }else {			// valide !
    echo "<tr><td>$i</td><td>".$_POST['prop']."</td><td>".$r["bon"].
      "</td><td>".$r["mal"]."</td></tr>\n";
    $_SESSION['jeu']=$jeu;
    $i++;
  }
  if ($r===false || $r["bon"]!=4){   // tq pas gagné !
    echo "<tr><td>$i</td><td>";
    echo "<input type='text' name='prop' size='".$jeu->getTaille().
      "'</td><td></td><td></td></tr>\n";
    ?>
    </table>
   <input type="submit" value="OK">
<?php
  }else {			// GAGNE
?>
    <tr><td></td><td>GAGNE !</td><td></td></tr>
    </table>
<?php
  }
}else{
  echo "<tr><td>$i</td><td>";
  echo "<input type='text' name='prop' size='".$jeu->getTaille().
    "'</td><td></td><td></td></tr>\n";
?>
    </table>
    <input type="submit" value="OK">
<?php
}
?>
    <input type="submit" name="nouveau" value="Nouvelle Partie">
    Nom de sauvegarde : <input type="text" name="nom" size="10">
    <input type="submit" name="sauve" value="Sauver la partie en cours">
    <input type="submit" name="restaure" value="Restaurer une partie sauvegardée">
   </form>
  </body>
</html>
