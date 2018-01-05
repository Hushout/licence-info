import java.util.*;

public class FileAttente<A> {
	protected ArrayList<A> contenu;
	public FileAttente() {	
		contenu = new ArrayList<A>();
	}
	public void entre(A a) {
		contenu.add(a);
	}
	public A sort() {
		A a = null;
		if(!contenu.isEmpty()) {
			a = contenu.get(0);
			contenu.remove(0);
		}
		return a;
	}
	public boolean estVide() {
		return contenu.isEmpty();
	}
	public String toString() {
		return "" + contenu;
	}
}
