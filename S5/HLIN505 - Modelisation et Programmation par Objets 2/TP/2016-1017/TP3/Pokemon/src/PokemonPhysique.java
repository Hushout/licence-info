public abstract class PokemonPhysique extends Pokemon {
	protected int nombreDePattes;
	protected double taille;
	public PokemonPhysique(String name , double poids , int nombreDePattes , double taille){
		super(name , poids);
		this.nombreDePattes = nombreDePattes;
		this.taille = taille;
	}
	public double vitesse() {
		return nombreDePattes * taille * 3;
	}
	public String toString() {
		return super.toString() + ", j'ai " + nombreDePattes + " pattes, ma taille est de " + taille + " m";
	}
}
