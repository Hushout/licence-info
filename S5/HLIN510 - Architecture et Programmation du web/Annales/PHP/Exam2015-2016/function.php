<?php

function dbConnect($login, $pass){

	try{
		$db = new PDO('mysql:host=venus;dbname=apogee;charset=UTF8', $user, $pass);
	} catch(PDOException $e){
		echo $e->getMessage();
		die("Connexion impossible !");
	}

	return $db;
}

function getEtudiant($login, $password){
	$db = dbConnect('root', '');

	$sql = 'SELECT * FROM etudiant 
			WHERE login = :login AND password = :password';

	$req = $db->prepare($sql);

	$res = $req->execute(array(
		'login' => $login,
		'password' => $password
	));

	return $res;
}

function getNotes($etudiant){
	$db = dbConnect('root', '');

	$sql = 'SELECT ue.nom, note.note FROM etudiant, note, ue
			WHERE etudiant.numetu = :numetu AND etudiant.numetu = note.numetu AND note.code = ue.code';

	$req = $db->prepare($sql);

	$res = $req->execute(array('numetu' => $etudiant['numetu']));

	return $res;
}

function printNotes($notes){
	echo '<ul>';
	foreach ($notes as $note) {
		echo '<li>' . $note['nom'] . ' ' . $note['note'] . '</li>';
	}
	echo '</ul>';
}

