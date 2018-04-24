package Poste;

public class Colis extends ObjetPostal {
	private String declContenu;
	private double valeurDecl;
	private static double tarifBase=2;
	
	
	public Colis() {
	}
	public Colis(String origine, String destination, String codePostal,
			double poids, double volume, TauxRecom tauxRec, String declContenu,
			double valeurDecl) {
		super(origine, destination, codePostal, poids, volume, tauxRec);
		this.declContenu = declContenu;
		this.valeurDecl = valeurDecl;
	}

	public String getDeclContenu() {
		return declContenu;
	}
	public void setDeclContenu(String declContenu) {
		this.declContenu = declContenu;
	}
	public double getValeurDecl() {
		return valeurDecl;
	}
	public void setValeurDecl(double valeurDecl) {
		this.valeurDecl = valeurDecl;
	}
	public static void setTarifBase(double tarifBase) {
		Colis.tarifBase = tarifBase;
	}
	@Override
	public double getTarifBase() {
		return Colis.tarifBase;
	}
	
	@Override
	public double tarifAff() {
		double t = super.tarifAff();
		if (this.getVolume()>1.0/8.0) t+= 3;
		return t;
	}

	@Override
	public double tarifRemb() {
		switch (this.getTauxRec()){
		case moyen:return 10*this.valeurDecl/100.0;
		case fort:return 50*this.valeurDecl/100.0;
		}
		return 0;
	}

	@Override
	public String getTypeObjet() {
		return "Colis";
	}

	@Override
	public String toString() {
		return super.toString() +"/"+
				this.getVolume()+"/"+
				this.valeurDecl;
	}
	
	// remarque : on ne reecrit pas affiche car la version heritee
	// convient !
}
