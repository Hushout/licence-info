public class Tableau<A extends Comparable<A>> {

    private A T[];

    public Tableau(A T[]){
	this.T = T;
    }

    public void triBulle(){

	boolean trie = false;

	while(!trie){
    
	    trie = true;
    
	    for(int i = 0 ; i < T.length-1  ; i++){
		if(T[i+1].compareTo(T[i]) > 0){
		    A aux = T[i];
		    T[i] = T[i+1];
		    T[i+1] = aux;
		    trie = false;
		}
	    }
	}
    }

    public String toString(){
	String s = new String();
	for(A a : T){
	    s += a.toString() + " ";
	}
	return s;
    }
}
