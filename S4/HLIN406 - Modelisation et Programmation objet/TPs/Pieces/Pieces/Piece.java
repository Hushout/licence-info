package Pieces;

public class Piece{

	private String nom;
	private String reference;
	private float prix;
	private float garantie;
	private float dureeFab;

	public Piece(String nom, String reference, float prix, float garantie, float dureeFab){
		this.nom = nom;
		this.reference = reference;
		this.prix = prix;
		this.garantie = garantie;
		this.dureeFab = dureeFab;
	}
	
	public float prix(){
		return prix;
	}
	
	public float dureeGarantie(){
		return garantie;
	}
	
	public float dureeFabrication(){
		return dureeFab;
	}
	
	public String reference(){
		return reference;
	}
	
	public String nom(){
		return nom;
	}
	
	public void affiche(){
		System.out.print(
		"nom : " + nom + 
		"\nreference : " + reference +
		"\nprix : " + prix + " euros" +
		"\ngarantie : " + garantie + " mois" +
		"\nduree de fabrication : " + dureeFab + " jour(s)\n");
	}
	
	protected void afficheComposants(int nbEspace){}
	
	public String toString(){
		return nom + " - " + reference;
	}
}