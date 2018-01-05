package Clients;

public class Particulier extends Client{

	private String prenom;
	private Civilite civilite;
	private Sexe sexe;

	public Particulier(String nom, String Prenom, String adresse, String email, Civilite civilite, Sexe sexe){
		super(nom, adresse, email);
		this.prenom = prenom;
		this.civilite = civilite;
		this.sexe = sexe;
	}	
	
	public String prenom(){
		return prenom;
	}

	public Civilite civilite(){
		return civilite;
	}

	public Sexe sexe(){
		return sexe;
	}
}