package Poste;

import java.util.Date;

public class ColisExpress extends Colis {
	private Date dateEnvoi;
	private final int numeroSuivi;
	private boolean emballage;
	private static int numeroCourant=0;
	private static double tarifEmballage=3;
	private static double tarifBase=30;
	
	public ColisExpress() {
		this.numeroSuivi=ColisExpress.numeroCourant;
		ColisExpress.numeroCourant++;
	}
	// le numero de suivi n'est pas passé au constructeur car il est 
	// donne dans le constructeur
	public ColisExpress(String origine, String destination, String codePostal,
			double poids, double volume, TauxRecom tauxRec, String declContenu,
			double valeurDecl, Date dateEnvoi, boolean emballage) {
		super(origine, destination, codePostal, poids, volume, tauxRec,
				declContenu, valeurDecl);
		this.dateEnvoi = dateEnvoi;
		this.emballage = emballage;
		this.numeroSuivi=ColisExpress.numeroCourant;
		ColisExpress.numeroCourant++;
	}
	public Date getDateEnvoi() {
		return dateEnvoi;
	}
	public void setDateEnvoi(Date dateEnvoi) {
		this.dateEnvoi = dateEnvoi;
	}
	public int getNumeroSuivi() {
		return numeroSuivi;
	}
	// pas de setNumeroSuivi
	public boolean isEmballage() {
		return emballage;
	}
	public void setEmballage(boolean emballage) {
		this.emballage = emballage;
	}
	public static int getNumeroCourant() {
		return numeroCourant;
	}
	public static void setNumeroCourant(int numeroCourant) {
		ColisExpress.numeroCourant = numeroCourant;
	}
	public static double getTarifEmballage() {
		return tarifEmballage;
	}
	public static void setTarifEmballage(double tarifEmballage) {
		ColisExpress.tarifEmballage = tarifEmballage;
	}
	@Override
	public double getTarifBase() {
		return ColisExpress.tarifBase;
	}
	@Override
	public double tarifAff() {
		double t = this.getTarifBase();
		if (this.emballage) t+= ColisExpress.tarifEmballage;
		return t;
	}
	@Override
	public String getTypeObjet() {
		return "ColisExpress";
	}
	@Override
	public String toString() {
		return super.toString() +"/"+
				this.getPoids()+"/"+
				this.numeroSuivi;
	}
	@Override
	public void setPoids(double poids) {
		if (poids <= 30)
			super.setPoids(poids);
		else {
			System.out.println("Le poids doit rester inferieur a 30");
			super.setPoids(30);	// on choisit de mettre la valeur maximale		
			// on peut choisir de ne pas changer la valeur
		}
	}
}