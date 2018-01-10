<?php
try {
$dbh = new PDO('mysql:host=venus;dbname=todorico', "todorico", "12345678");

$reponse = $dbh->query('SELECT nom from etudiant');
while($donnees = $reponse->fetch()){
	echo $donnees;
}

$dbh = null;
// fermeture connexion
}catch (PDOException $e) {
	print "Erreur !: " . $e->getMessage() . "<br/>";
	die();
}
?>
