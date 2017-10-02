<?php
include 'Mastermind.php';
session_start();
?>
<DOCTYPE html>
  <html>
  <head>
    <title>MASTERMIND</title>
  </head>
  <body>
    <!--ce formulaire permet de saisir une solution pour le jeu, et un pseudo de joueur au début-->
    <form action="jeu_mastermind.php" method="post" id="mastermind_form" name="mastermind">
      <script>

      //cette fonction est appelée au tout début pour produire un champ de texte où le joueur peut saisir son pseudo
      function addPlayerInput(){
        var form = document.getElementById("mastermind_form");
        var label = document.createElement("label");
        var input = document.createElement("input");
        input.type = "text";
        input.required = true;
        input.id = "playerInput";
        input.name = "player";
        label.htmlFor = "playerInput";
        label.innerHTML = "Player Name";
        form.appendChild(label);
        form.appendChild(input);
      }

      //le reste du script produit i champs pour rentrer la solution du mastermind
      //modifier la borne supérieure de i pour modifier la complexité du jeu
      var form = document.getElementById("mastermind_form");
      for(var i = 0 ; i < 2 ; i++) {
        var input = document.createElement("input");
        input.type = "number";
        input.name = "number[]";
        input.min = "0";
        input.max = "9";
        input.length = "1";
        input.required = true;
        form.appendChild(input);
      }
      </script>
      <input type="submit">
    </form>
    <?php
    global $mastermind;
    //si on a déjà un objet Mastermind (3ème passage sur la page)
    if(isset($_SESSION['mastermind'])) {
      $mastermind = unserialize(base64_decode(array_pop($_SESSION)));

      //si on a déjà un joueur (2ème passage sur la page)
    } else if(isset($_POST['player'])) {
      $mastermind = new Mastermind((string)$_POST['player']);

      //sinon (1er passage sur la page)
    } else {
      unset($_POST['number']);
      echo '<script>addPlayerInput();</script>';
    }

    //si on a déjà des nombres dans le $_POST
    if(isset($_POST['number'])) {

      //on affiche le pseudo du joueur
      echo 'Joueur : ' . $mastermind->player .'<br>';

      //on affiche l'historique des coups joués
      if(!empty($mastermind->history)) {
        echo 'Historique des coups joués : <br>' ;
        $mastermind->print_history();
      }

      //passe la dernière saisie de l'utilisateur dans $saisie
      $saisie = array();
      $saisie = array_merge($saisie , $_POST['number']);

      //on affiche la saisie de l'utilisateur
      echo 'Votre saisie : ';
      foreach($saisie as $key=>$value) {
        echo $value;
      }

      //on vérifie si la saisie est juste
      $result = $mastermind->tentative($saisie);
      $numbers = array();
      $numbers = array_merge($numbers , $result['number']);

      //et on affiche le résultat
      echo 'Resultat : ';
      foreach($numbers as $key=>$value) {
        echo $value;
      }
      echo '<br>' . $result['correct'] . '<br>';

      //on ajoute la dernière saisie à l'historique et on passe l'objet mastermind à $_SESSION
      $coup = array();
      $coup['saisie'] = $saisie;
      $coup['result'] = $result;
      $mastermind->add($coup);
      $_SESSION['mastermind'] = base64_encode(serialize($mastermind));

      //si l'utilisateur a gagné on détruit la session pour recommencer à zéro
      if($result['correct'] == 'Réussi!'){
        session_destroy();
      }
    }
    ?>
  </body>
  </html>
