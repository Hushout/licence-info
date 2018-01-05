public abstract class Vehicule {
	protected String immatriculation;
	protected int poidsAVide;
	
	public abstract int vitesseMax();
	
	public String toString() {
		return "Véhicule immatriculé " + immatriculation + " pesant " + poidsAVide + " tonnes à vide, de vitesse max " + vitesseMax();
	}
	
	public Vehicule(String s) {
		immatriculation = s;	
	}
}
