import java.util.*;

public class FileAttente<A extends ElementAvecPriorite> {
	private ArrayList<A> contenu;

	public FileAttente(){
		contenu = new ArrayList<>();
	}

	public void entre(A a){
		contenu.add(a);
	}

	public A sort(){
		A a = null;
		if(!contenu.isEmpty()){
			int prioMax = Integer.MAX_VALUE;
			for(int i = 0 ; i < contenu.size() ; i++){
				if(contenu.get(i).priorite() < prioMax){
					prioMax = contenu.get(i).priorite();
					a = contenu.get(i);
				}
			}
			contenu.remove(a);
		}
		return a;
	}

	public boolean estVide(){
		return contenu.isEmpty();
	}

	public String toString(){
		return ""+contenu;
	}
}
