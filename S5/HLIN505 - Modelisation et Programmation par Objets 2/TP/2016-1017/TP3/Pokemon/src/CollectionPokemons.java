import java.util.*;

public class CollectionPokemons {
	private ArrayList<Pokemon> collection = new ArrayList<Pokemon>();
	public CollectionPokemons() {}
	public void insertPokemon(Pokemon p) {
		collection.add(p);
	}
	public double vitesseMoyenne() {
		double moy = 0;
		for(int i = 0 ; i < collection.size() ; i++){
			moy += collection.get(i).vitesse();
		}
		return moy / collection.size();
	}
	public double vitesseMoyenneSportifs() {
		double moy = 0;
		int count = 0;
		
		for(int i = 0 ; i < collection.size() ; i++){
			if(collection.get(i) instanceof PokemonSportif){
				moy += collection.get(i).vitesse();
				count++;
			}
		}
		return moy / count;
	}
	public void displayCollection() {
		for(int i = 0 ; i < collection.size() ; i++){
			System.out.println(collection.get(i).toString());
		}
	}
}
