public class A {
	private String nom;
	
	public A(String n) {
		nom = n;
	}
	
	public String laClasse() {
		return "A";
	}
	
	public String toString() {
		return "Mon nom est " + nom + ", je suis un " + laClasse();
	}
}
