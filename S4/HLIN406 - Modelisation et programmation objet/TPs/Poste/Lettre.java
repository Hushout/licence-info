package Poste;

public class Lettre extends ObjetPostal {
	private boolean urgente;
	private static double tarifBase=0.5;
	
	public Lettre() {
	}

	public Lettre(String origine, String destination, String codePostal,
			double poids, double volume, TauxRecom tauxRec, boolean urgente) {
		super(origine, destination, codePostal, poids, volume, tauxRec);
		this.urgente = urgente;
	}

	@Override
	public double getTarifBase() {
		return Lettre.tarifBase;
	}
	
	@Override
	public double tarifAff() {
		double t = super.tarifAff();
		if (urgente) t+= 0.3;
		return t;
	}

	@Override
	public double tarifRemb() {
		switch (this.getTauxRec()){
		case moyen:return 1.5;
		case fort:return 15;
		}
		return 0;
	}

	@Override
	public String getTypeObjet() {
		return "Lettre";
	}
	
	@Override
	public String toString() {
		String res=super.toString();
		if (urgente) res += "/urgente";
		else res += "/ordinaire";
		return res;
	}
	
	// remarque : on ne reecrit pas affiche car la version heritee
	// convient !
}
