public abstract class Camion extends Vehicule{
	protected int charge;
	protected int chargeMaximale;
	
	public Camion(String s , int c){
		super(s);
		charge = c;
	}
	
	public String toString() {
		return super.toString() + ", de charge de " + charge + " tonnes, de charge maximale de " + chargeMaximale + " tonnes et de type Camion ";
	}
}
