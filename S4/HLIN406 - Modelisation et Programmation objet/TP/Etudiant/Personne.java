package Etudiant;

public class Personne{

    public int age;
    public int dateNaiss;
    public String nom;
    
    public Personne(int age, int dateNaiss, String nom){
	this.age = age;
	this.dateNaiss = dateNaiss;
	this.nom = nom;
    }
    
    public int getAge(){
	return age;
    }

    public int getDateNaiss(){
	return dateNaiss;
    }

    public String getNom(){
	return nom;
    }
}
