<!doctype html>
<html lang="fr">
<head>
<meta charset="utf-8" /> 
<title>Accueil des Stages d'Analyse</title>
</head>

<body>
<center>
  <h1>Stages d'Analyse</h1>
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

  $req="SELECT S.numStageA, sujet, entreprise, lieu, respEnt, respPeda,nom, prenom, email ";
  $req.="FROM stageA S LEFT JOIN etudiant E ON S.numStageA=E.numStageA ";
  $req.="ORDER BY S.numStageA, nom, prenom";

  $res = $dbh->query($req);
  if (!$res) die("Impossible d'exécuter la requête !");
  // Début de l'affichage : 1 tableau par stage !
  $numStage=-1;			   // numéro de stage courant
  foreach ($res as $ligne){        // tq il reste des Stage-étud
    if ($numStage!=$ligne["numStageA"]){ // nouveau Stage
      if ($numStage!=-1){	// il faut fermer la table du stage prec
	echo "\n",'</td></tr></tbody></table></tr></tbody></table>',"\n<br>"; 
	// fermeture 2 tab
      }
      $numStage=$ligne["numStageA"]; // chgt numero courant
      echo "\n",'<table border="1"> <tbody>',"\n"; // début du tableau HTML
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<th>Numéro</th><th>",$ligne['numStageA'],"</th></tr>\n";
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<td>Sujet</td><td>",$ligne['sujet'],"</td></tr>\n";
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<td>Entreprise</td><td>",$ligne['entreprise'],"</td></tr>\n";
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<td>Responsable</td><td>",$ligne['respEnt'],"</td></tr>\n";
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<td>Tuteur péda.</td><td>",$ligne['respPeda'],"</td></tr>\n";
      echo '<tr align="left" valign="top">'; // nouvelle ligne
      echo "<td>Etudiants</td>\n";
      echo ' <td><table border="0"><tbody><tr align="left" valign="top">',"\n";
      if ($ligne["email"]){	// si au moins 1 étudiant : $c=case
	$c='  <td>';
	$c.='<br>'.$ligne["nom"].' '.$ligne["prenom"].'<br><a href="mailto:';
	$c.=$ligne["email"].'@info-ufr.univ-montp2.fr">'.$ligne["email"];
	$c.='</a><br></td>';
	echo $c;		// affichage de l'étudiant num 1 (case)
      }
      else {			// pas d'etudiant inscrit dans ce stage !
	echo '  <td>Aucun stagiaire</td>'; // case vide
      }
    }
    else {			// stage déja vu alors 1 etudiant
      $c=' <td>';
      $c.='<br>'.$ligne["nom"].' '.$ligne["prenom"].'<br><a href="mailto:';
      $c.=$ligne["email"].'@info-ufr.univ-montp2.fr">'.$ligne["email"];
      $c.='</a><br></td>';
      echo $c;		// affichage de l'étudiant suivant
    }
  } // fin du foreach
				// dernier stage
  echo "\n",'</td></tr></tbody></table></tr></tbody></table>',"\n<br>";
  $dbh = null;   // fermeture connexion

?>
<br>
<h1><a href="index.php">Retour</a></h1>
</body>
</html>
