package Clients;

public class Entreprise extends Client{

	private String siret;

	public Entreprise(String nom, String adresse, String email, String siret){
		super(nom, adresse, email);
		this.siret = siret;
	}	
	
	public String siret(){
		return siret;
	}
}