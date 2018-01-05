public class TestFileAttente {
    public static void main(String[] args){

	Personne jeune = new Personne("boby", 8);
	Personne vieux = new Personne("henriette", 67);
	Personne autre = new Personne("jacque", 25);

	FileAttente<Personne> F = new FileAttente<>();
	F.entre(autre);
	F.entre(jeune);
	F.entre(vieux);

	System.out.println("File: "+F);
	Personne p = F.sort();
	System.out.println("sortie: " + p + " priorite: " + p.priorite());
	p = F.sort();
	System.out.println("sortie: " + p + " priorite: " + p.priorite());
	p = F.sort();
	System.out.println("sortie: " + p + " priorite: " + p.priorite());
    }
}
