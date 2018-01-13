public class CamionCiterne extends Camion {
	public CamionCiterne(String s , int c) {
		super(s , c);
		poidsAVide = 3;
		chargeMaximale = 10;
	}
	
	public int vitesseMax() {
		if(charge == 0) return 130;
		else if(charge <= 1) return 110;
		else if(charge <= 4) return 90;
		else return 80;
	}
	
	public String toString() {
		return super.toString() + "Citerne";
	}
}
