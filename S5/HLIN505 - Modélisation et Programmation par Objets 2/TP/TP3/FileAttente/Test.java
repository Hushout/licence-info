import java.util.*;

public class Test {

    public static void main(String[] args){

	Personne p1 = new Personne(10, "Boby");
	Personne p2 = new Personne(20, "Arnold");
	Personne p3 = new Personne(43, "Rodolf");
	Personne p4 = new Personne(25, "Jean-luc");

	@Todo(
	      typeTache = "faire trucs",
	      auteur = "bibi",
	      version = "1.000000003",
	      dureeTache = "Infinityyyyyy"
	      )
	
	ArrayList<Personne> list = new ArrayList<Personne>();
	list.add(p1);
	list.add(p2);
	list.add(p3);
	list.add(p4);
	
	Collections.sort(list);
	printArray(list);
	System.out.println("\nLe max est:");
	System.out.println(Collections.max(list, new ComparatorAgePersonne()));
	//printArray(list);
    }


    public static<E> void printArray(ArrayList<E> a){
	for(E objet : a){
	    System.out.println(objet);
	}
    }

    public @interface Todo {

	String auteur() default "Tichien";
	String typeTache() default "optimisation";
	String version() default "1.0";
	String dureeTache() default "1 heure";
	//rajouter des trucs ! c'est important les trucs.
    }
}
