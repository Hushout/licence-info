import java.io.*;

public class Personne implements Comparable<Personne> {

    private int age;
    private String nom;
    
    Personne(int age, String nom){
	this.age = age;
	this.nom = nom;
    }

    public int getAge(){
	return age;
    }

    public String getNom(){
	return nom;
    }
    
    public int compareTo(Personne p){
	return this.nom.compareTo(p.nom);
    }

    public String toString(){
	return "Je m'appel " + nom + " et j'ai " + age + " ans";
    }
}
