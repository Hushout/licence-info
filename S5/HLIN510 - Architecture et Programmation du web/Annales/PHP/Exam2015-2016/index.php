<?php 

session_start(); 

require 'function.php';

$notes = '';

if(isset($_SESSION['login']) && isset($_SESSION['pass']) && isset($_SESSION['pass2'])){
	
	if($_SESSION['pass'] == $_SESSION['pass2']){

		$etudiant = getEtudiant($_SESSION['login'], $_SESSION['pass']);

		if($etudiant){

			$notes = getNotes($etudiant);
		}
	}
}

?>

<html>
<head>
	<meta charset="utf-8">
	<title>Exam</title>
</head>
<body>
	<?php if(!$notes): ?>
		<?php include 'form.php'; ?>
	<?php else: ?>
		<?php printNotes($notes); ?>
	<?php endif; ?>
</body>
</html>