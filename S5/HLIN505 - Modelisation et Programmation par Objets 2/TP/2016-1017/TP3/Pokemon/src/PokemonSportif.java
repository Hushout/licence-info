public class PokemonSportif extends PokemonPhysique {
	private int frequenceCardiaque;
	public PokemonSportif(String name , double poids , int nombreDePattes , double taille , int frequenceCardiaque) {
		super(name , poids , nombreDePattes , taille);
		this.frequenceCardiaque = frequenceCardiaque;
	}
	public String toString() {
		return super.toString() + " et ma fréquence cardiaque est de " + frequenceCardiaque + " pulsations par minutes";
	}
}
