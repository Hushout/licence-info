import java.util.*;

public class Pochette<E extends Document> {
	private String theme;
	private ArrayList<E> documents;

	public Pochette() {
		theme = "Default";
		documents = new ArrayList<>();
	}

	public Pochette(String t){
		theme = t;
		documents = new ArrayList<>();
	}

	public void add(E e) throws DocumentException {
		documents.add(e);
	}

	public void transferTo(Pochette<? super E> p) throws DocumentException {
		
		for(int i = 0 ; i < documents.size() ; i++){
			p.add(documents.get(i));
		}
	}

	public String getTheme() {
		return theme;
	}

	public int nbDocuments(){
		return documents.size();
	}

	public String toString() {
		return theme + " " + documents.size();
	}
}