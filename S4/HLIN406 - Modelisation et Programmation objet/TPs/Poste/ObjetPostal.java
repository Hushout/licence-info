package Poste;

public abstract class ObjetPostal {
	private String origine,
					destination,
					codePostal;
	private double poids,
					volume;
	private TauxRecom tauxRec;
	public ObjetPostal() {
	}
	public ObjetPostal(String origine, String destination, String codePostal,
			double poids, double volume, TauxRecom tauxRec) {
		// l'appel des accesseurs en ecriture permet de passer par
		// des points de controle s'il y en a (dans cette classe ou dans ses sous-classes)
		this.setOrigine(origine);
		this.setDestination(destination);
		this.setCodePostal(codePostal);
		this.setPoids(poids);
		this.setVolume(volume);
		this.setTauxRec(tauxRec);
	}
	public String getOrigine() {
		return origine;
	}
	public void setOrigine(String origine) {
		this.origine = origine;
	}
	public String getDestination() {
		return destination;
	}
	public void setDestination(String destination) {
		this.destination = destination;
	}
	public String getCodePostal() {
		return codePostal;
	}
	public void setCodePostal(String codePostal) {
		this.codePostal = codePostal;
	}
	public double getPoids() {
		return poids;
	}
	public void setPoids(double poids) {
		this.poids = poids;
	}
	public double getVolume() {
		return volume;
	}
	public void setVolume(double volume) {
		this.volume = volume;
	}
	public TauxRecom getTauxRec() {
		return tauxRec;
	}
	public void setTauxRec(TauxRecom tauxRec) {
		this.tauxRec = tauxRec;
	}
	
	abstract public double getTarifBase();
	
	public double tarifAff(){
		double t=this.getTarifBase();
		if (this.getTauxRec().equals(TauxRecom.moyen)) t+=0.5;
		else 
			if (this.getTauxRec().equals(TauxRecom.fort)) t+=1.5;
		return t;
	}
	
	abstract public double tarifRemb();	
	abstract public String getTypeObjet();
	
	public String toString(){
		return this.getTypeObjet()+"/"+this.getCodePostal()+"/"+
				this.getDestination()+"/"+this.getTauxRec();
	}
	
	public void affiche(){
		System.out.println(this);// ou this.toString
	}
}
