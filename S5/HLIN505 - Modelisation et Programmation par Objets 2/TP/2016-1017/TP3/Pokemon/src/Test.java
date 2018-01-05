public class Test {
	public static void main(String [] args){
		CollectionPokemons collec = new CollectionPokemons();
		Pokemon P = new PokemonDeCroisiere("Groudon" , 345.4 , 8);
		Pokemon P2 = new PokemonCasanier("Machope" , 62.0 , 4 , 1.76 , 18);
		Pokemon P3 = new PokemonSportif("Machopeur" , 90.0 , 6 , 2.05 , 135);
		
		collec.insertPokemon(P);
		collec.insertPokemon(P2);
		collec.insertPokemon(P3);
		
		collec.displayCollection();
		
		System.out.println(collec.vitesseMoyenneSportifs());
	}
}