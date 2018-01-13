<?php

function getEtudiant($login, $password){
	$db = DBConnect();

	$sql = 'SELECT * FROM etudiant 
			WHERE login = :login AND password = :password';

	$req = $db->prepare($sql);
	$res = $req->execute(array(
		'login' => $login;
		'password' => $password;
	));

	return $res;
}

function getNotes($etudiant){
	$db = DBConnect();

	$sql = 'SELECT nom, note FROM etudiant, note, ue
			WHERE etudiant.numetu = note.numetu AND ue.code = note.code
			AND etudiant.numetu = :numetu';

	$req = $db->prepare($sql);
	$res = $req->execute(array(
		'numetu' => $etudiant['numetu'];
	));

	return $res;
}

function printNotes($notes){
	echo '<ul>';
	foreach ($notes as $note) {
		echo '<li>'.$note['nom'].' '.$note['note'].'</li>';
	}
	echo '</ul>';
}

function DBConnect(){
	$user="login"; $pass="pass";

	try{
		$db = new PDO('mysql:host=venus;dbname=apogee;charset=UTF8', 
			$user, $pass);
	} catch(PDOException $e){
		echo $e->getMessage();
		die("Connexion impossible !");
	}

	return $db;
}