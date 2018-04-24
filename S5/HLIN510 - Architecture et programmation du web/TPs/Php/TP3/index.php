<!doctype html>

<html lang="fr">
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="" />
    <title>Odorico Thibault - HLIN510</title>
  </head>

  <body>

    <header>
      <h1>Mastermind<h1>
    </header>


    <section>
      <?php
      include 'Mastermind.php';

	 session_start();

	 if(!empty($_GET) && isset($_GET['nouveau']))
	 {
	 	session_unset();
	 }

	 if(!isset($_SESSION['mm']))
	 {
	 	$_SESSION['mm'] = new Mastermind;
	 }

	if(!empty($_GET) && isset($_GET['code']) && isset($_GET['envoyer'])){
		$placement_array = $_SESSION['mm']->tryCode($_GET['code']);
		$_SESSION['action_array'][] = $placement_array;
		$_SESSION['win'] = $placement_array[1] == 4;
	}


      ?>
      <form method="get">
	<?php
	if(!empty($_GET) && isset($_GET['code']))
	echo "<input type='text' name='code' autofocus='autofocus' value='{$_GET['code']}' pattern='[0-9]{4}' required title='4 nombres'/>";
	else
	echo "<input type='text' name='code' autofocus='autofocus' pattern='[0-9]{4}' required title='4 nombres'/>";
	?>
	<input type="submit" name="envoyer" value="Envoyer"/>
	<input type="submit" name="nouveau" value="Nouveau"/>
      </form>
      <?php
	if(isset($_SESSION['action_array'])){

		echo "<table border='1'>";
		echo "<tr><th>Code</th><th>Bien placées</th><th>Bon numeros</th></tr>";

		foreach($_SESSION['action_array'] as $try){
			echo "<tr><th>".$try[0]."</th><th>".$try[1]."</th><th>".$try[2]."</th></tr>";
		}

		echo "</table>";

		if($_SESSION['win']){
			echo "<p>Gagnées</p>";
		}
	}
	$_SESSION['mm']->printCode();
	?>
    </section>

    <footer>
    </footer>
  </body>
</html>
