<DOCTYPE html>
  <html>
  <head><title>Commandes</title></head>
  <body>
    <?php
    $commande = array();
    $lcommandes = array();

    foreach ($_POST as $key=>$value) {

      if($key == 'historique') {
        $historique = unserialize(base64_decode($value));

        foreach ($historique as $commande) {
          array_push($lcommandes , $commande);
        }

      } else {
        $commande[$key] = $value;
      }
    }
    array_push($lcommandes , $commande);

    foreach($lcommandes as $commandeCourante){
      print_r($commandeCourante);
      echo '<br>';
    }
    ?>
    <form action="champscachés.php" method="post" name="formulaire_commande">
      <?php
      foreach ($_POST as $value) {
        echo '<input type="hidden" name="historique" value="' . base64_encode(serialize($lcommandes)) . '">';
      }
      ?>
      Quantité de disques durs : <input type="number" name="quantité" /><br>
      <!--Selection du type de DD-->
      <select name="type">
        <option value="">Select</option>
        <option value="seagate">Disque Dur Seagate 500Go</option>
        <option value="western">Disque Dur Western 750Go</option>
        <option value="externe">Disque Dur Externe 500Go</option>
      </select>
      <!--Selection des claviers et souris-->
      <div id="selection_claviers_souris">
        clavier logitech (10€)<input type="checkbox" name="claviers_souris[]" value="clavier_logitech" />
        souris logitech (12€)<input type="checkbox" name="claviers_souris[]" value="souris_logitech" />
        clavier souris sans fil (35€)<input type="checkbox" name="claviers_souris[]" value="clavier_souris" />
      </div>
      <!--Selection d'accessoires-->
      <div id="selection_accessoires">
        clavier logitech (10€)<input type="radio" name="accessoires" value="enceinte" />
        souris logitech (12€)<input type="radio" name="accessoires" value="tapis_souris" />
      </div>
      <!--Mail, nom du panier et bouton de validation-->
      Adresse email : <input type="email" name="email" size="40" maxlength="40" required/><br>
      Nom : <input style="text-transform: uppercase" type="text" name="name" size="20" maxlength="20" id="text" onblur="caps(this.id)" required/><br>
      <input type="submit"/>
    </form>
  </body>
  </html>
