public abstract class Pokemon {
	protected String name;
	protected double poids;
	public Pokemon(String name , double poids) {
		this.name = name;
		this.poids = poids;
	}
	public abstract double vitesse();
	public String toString() {
		return "Je suis le Pokémon " + name + ", mon poids est de " + poids + "kg, ma vitesse est de " + vitesse() + "m/s ";
	}
}
