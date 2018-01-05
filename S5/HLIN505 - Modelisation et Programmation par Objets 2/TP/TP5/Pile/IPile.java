public interface IPile<A>{
	
	boolean estVide();
	void empile(A a);
    A depile(); // retourne l'element en sommet de pile
    int nbElements();
    A sommet(); // retourne le sommet de pile mais ne le depile pas
}
