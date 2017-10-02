<?php
try {
  $dbh = new PDO('mysql:host=localhost;dbname=tp4' , $username="root" , $password="Mcs1@p.");
  foreach($dbh->query('SELECT * FROM etudiant') as $row) {
    print ($row['nom']) . "<br>";
  }
  $dbh = null;

} catch (PDOException $e) {
  print "Erreur : " . $e->getMessage() . "<br>";
  die();
}
?>
