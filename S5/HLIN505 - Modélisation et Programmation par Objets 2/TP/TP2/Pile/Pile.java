import java.io.*;

public class Pile {
	class PileVideException extends Exception {}
	class PilePleineException extends Exception {}
	private static final int TAILLE_MAX = 0;
	private int t[];
	private int nb;

	public Pile(){
		t = new int [TAILLE_MAX];
		nb = 0;
	}

	public boolean estVide() { return nb == 0;}

	public void empiler(int i) throws PilePleineException {
		if(nb == TAILLE_MAX) throw new PilePleineException();
		t[nb] = i;
		nb++;
		System.out.println("sortie de empiler");
	}

	public int sommet() throws PileVideException {
		if(nb == 0) throw new PileVideException();
		System.out.println("sortie de sommet");
		return t[nb-1];
	}

	public void depiler() throws PileVideException {
		if(nb == 0) throw new PileVideException();
		nb--;
		System.out.println("sortie de depiler");
	}

	public void depilerTout() {
		try {
			while(true) {
				System.out.println(sommet());
				depiler();
			}
		}
		catch(PileVideException e)
		{System.out.println("le depilerTout est passe par la");}
		System.out.println("sortie du depilerTout");
	}

	public static void main(String[] args) {
		Pile p = new Pile();
		try{
			p.empiler(2);
			p.empiler(4);
			p.depilerTout();
			System.out.println(p.sommet());	    
		}
		catch(PileVideException e)
		{System.out.println("Le main pense que la pile est vide");}
		catch(PilePleineException e)
		{System.out.println("Le main pense que la pile est pleine");}
		catch(Exception e)
		{System.out.println("Le main est passe par la");}
		System.out.println("Sortie du main");
	}
}