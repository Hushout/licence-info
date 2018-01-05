<?php
class Mastermind{
  public $player = '';
  private $combination = array();
  public $history = array();

  //Constructeur de classe qui prend le nom du joueur en paramètre
  public function __construct($p) {
    $this->player = $p;
    for($i = 0 ; $i < 4 ; $i++) {
      $this->combination[$i] = rand(0 , 9);
    }
    $this->history = array();
  }

  //Prend un tableau de 4 entiers en paramètres pour vérifier si c'est la bonne combinaison
  public function tentative($t) {
    $retour = array();
    $correct = 'Réussi!';
    foreach ($t as $key=>$value) {
      if($t[$key] == $this->combination[$key]) {
        $retour['number'][] = ($t[$key]);
      } else {
        $retour['number'][] = 'x';
        $correct = 'Echec!';
      }
    }
    echo '<br>';
    $retour['correct'] = $correct;
    return $retour;
  }

  //ajoute la saisie $s à l'historique
  public function add($s){
    array_push($this->history , $s);
  }

  //affiche l'historique des coups joués et de leur résultat
  public function print_history(){
    foreach ($this->history as $key=>$value) {
      $t = array();
      $t = array_merge($t , $value['saisie']);
      foreach($t as $number){
        echo $number;
      }
      echo ' : ';
      $t = array();
      $t = array_merge($t , $value['result']['number']);
      foreach($t as $number){
        echo $number;
      }
      echo '<br>';
    }
  }
}
?>
