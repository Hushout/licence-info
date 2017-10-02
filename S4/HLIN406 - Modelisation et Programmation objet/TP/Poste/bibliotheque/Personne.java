package bibliotheque;

public abstract class Personne {
 private String nom;
 private String prenom;
public String getNom() {
	return nom;
}
public String getPrenom() {
	return prenom;
}
public Personne(String nom, String prenom) {
	this.nom = nom;
	this.prenom = prenom;
}
 
}
