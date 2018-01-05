public class PokemonCasanier extends PokemonPhysique {
	private int nbHeuresDevantLaTele;
	public PokemonCasanier(String name , double poids , int nombreDePattes , double taille , int nbHeuresDevantLaTele) {
		super(name , poids , nombreDePattes , taille);
		this.nbHeuresDevantLaTele = nbHeuresDevantLaTele;
	}
	public String toString() {
		return super.toString() + " et je passe " + nbHeuresDevantLaTele + " heures devant la tele par jour";
	}
}
