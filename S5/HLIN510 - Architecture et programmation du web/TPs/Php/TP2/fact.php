<!doctype html>

<html lang="fr">
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="" />
    <title>Odorico Thibault - HLIN510</title>
  </head>

  <body>

    <header>
    </header>

    <section>
      <form method="get">
	<label for="val">Valeur d'entrée: </label>
	<input type="text" name="val" value="1" pattern="[0-9]+" title="Entiers uniquement"/>
	<input type="submit" value="Envoyer"/>
      </form>
      <p>
	<?php
	   function fact($x){
	   return $x == 1 ? 1 :  $x * fact($x - 1);
	   }
	   echo "Fact(" . $_GET['val'] . ") = " . fact($_GET['val']);
	   ?>
	</p>
    </section>

    <footer>
    </footer>
  </body>
</html>
