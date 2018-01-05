<DOCTYPE html>
  <html>
  <head>
    <title>Factorielle</title>
  </head>
  <body>
    <form action="factorielle.php" method="post" name="factorielle">
      <label for="champ">Entrez un nombre pour calculer sa factorielle</label>
      <input type="number" name="number" required></input>
      <input type="submit"></button>
    </form>
    <?php
    if(!(empty($_POST))){
      $nb = $_POST['number'];
      $factorielle = 1;
      for($i = 1 ; $i <= $nb ; $i++){
        $factorielle = $factorielle * $i;
      }
      echo "La factorielle de $nb est $factorielle\n";
    }
    ?>
  </body>
  <html>
