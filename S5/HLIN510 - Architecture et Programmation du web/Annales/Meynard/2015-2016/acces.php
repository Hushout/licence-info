<?php
session_start()

include 'bdd.php';

if(isset($_SESSION['login']) && isset($_SESSION['password']) && isset($_SESSION['confirm'])){
	if($_SESSION['password'] == $_SESSION['confirm']){

		$etudiant = getEtudiant($_SESSION['login'], $_SESSION['password']);

		if($etudiant){
			$notes = getNotes($etudiant);
			require 'notes.php';
		}
	}
}

require 'index.php';