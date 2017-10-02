<html>
<head>
</head>
<body>
  <?php
  $login = $POST['login'];
  $pass = $POST['password'];
  $pass_confirm = $POST['password_confirm'];

  if($password != $password_confirm) {
    print("The passwords don't match\n");
  } else {
    try {
      $dbh = new PDO('mysql:host=localhost;dbname=annale2015' , $username="root" , $password="Mcs1@p.");
      $query = $dbh->query("SELECT * FROM Etudiant
      WHERE login = '$login'
      AND PASSWORD ='$pass'");
      $login = $query['login'];
      $pass = $query['PASSWORD'];
      print("Welcome '$login'");
    } catch(PDOException $e) {
      print "Erreur : " . $e->getMessage() . "<br>";
      die();
    }
  }
  ?>
</body>
</html>
