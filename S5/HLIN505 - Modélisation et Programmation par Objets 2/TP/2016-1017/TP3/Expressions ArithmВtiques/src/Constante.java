public class Constante extends Expression {
	protected double valeur;
	public Constante(double d) {
		valeur = d;
	}
	public double eval() {
		return valeur;
	}
}
