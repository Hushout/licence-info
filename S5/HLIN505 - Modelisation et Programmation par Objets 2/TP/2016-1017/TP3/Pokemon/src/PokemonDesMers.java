public class PokemonDesMers extends Pokemon {
	protected int nbNageoires;
	public PokemonDesMers(String name , double poids , int nbNageoires) {
		super(name , poids);
		this.nbNageoires = nbNageoires;
	}
	public double vitesse() {
		return (poids / 25 * nbNageoires);
	}
	public String toString() {
		return super.toString() + " et j'ai " + nbNageoires + " nageoires";
	}
}
