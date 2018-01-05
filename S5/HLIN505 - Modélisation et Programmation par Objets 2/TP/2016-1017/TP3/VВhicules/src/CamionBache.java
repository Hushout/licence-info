public class CamionBache extends Camion {
	public CamionBache(String s , int c) {
		super(s , c);
		poidsAVide = 4;
		chargeMaximale = 20;
	}
	
	public int vitesseMax() {
		if(charge == 0) return 130;
		else if(charge <= 3) return 110;
		else if(charge <= 7) return 90;
		else return 80;
	}
	
	public String toString() {
		return super.toString() + "Bâché";
	}
	
}
