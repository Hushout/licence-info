
public class PokemonDeCroisiere extends PokemonDesMers {
	public PokemonDeCroisiere(String name , double poids , int nbNageoires) {
		super(name , poids , nbNageoires);
	}
	public double vitesse() {
		return (poids / 25 * nbNageoires) / 2;
	}
}
