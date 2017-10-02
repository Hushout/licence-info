<?php
try {
  $dbh = new PDO('mysql:host=localhost;dbname=tp4' , $username="root" , $password="Mcs1@p.");

  //Tous les étudiants participant à un même stage d'analyse
  $sql = 'SELECT DISTINCT st.numStageA , st.sujet , st.respEnt , st.respPeda , e1.nom
  FROM stageA st , etudiant e1 , etudiant e2
  WHERE e1.numStageA = st.numStageA
  AND e2.numStageA = st.numStageA
  AND e1.nom != e2.nom
  AND e1.prenom != e2.prenom
  ORDER BY st.numStageA';

  foreach($dbh->query($sql) as $row) {
    print($row['numStageA']) . "\t";
    print($row['sujet']) . "\t";
    print($row['responsable']) . "\t";
    print($row['tuteur']) . "\t";
    print_r($row['nom']) . "\t";

    print "<br>";
  }

} catch (PDOException $e) {
  print "Erreur : " . $e->getMessage() . "<br>";
  die();
}
?>
