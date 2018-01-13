public class PetitBus extends Vehicule{
	public PetitBus(String s) {
		super(s);
	}
	public int vitesseMax() {
		return 150;
	}
	
	public String toString() {
		return super.toString() + "et de type Petit Bus";
	}
}
