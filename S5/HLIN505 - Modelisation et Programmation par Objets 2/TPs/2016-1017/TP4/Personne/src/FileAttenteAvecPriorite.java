
public class FileAttenteAvecPriorite<A extends ElementAvecPriorite> extends FileAttente<A> {
	
	public A sort() {
		int index = 0;
		A a = null;
		
			for(int i = 0 ; i < contenu.size() ; i++) {
				
				if(contenu.get(i).priorite() <= contenu.get(index).priorite()) {
					index = i;
				}
			}
		a = contenu.get(index);
		contenu.remove(index);
		return a;
	}
}
