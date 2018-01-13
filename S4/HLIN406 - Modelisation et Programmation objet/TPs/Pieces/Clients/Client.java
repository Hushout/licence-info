package Clients;

public class Client {

	private String nom;
	private String adresse;
	private String email;

	public Client(String nom, String adresse, String email){
		this.nom = nom;
		this.adresse = adresse;
		this.email = email;
	}	
	
	public String nom(){
		return nom;
	}

	public String adresse(){
		return adresse;
	}

	public String email(){
		return email;
	}
}
