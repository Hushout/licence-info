package bibliotheque.abonnes;

import java.util.ArrayList;

import bibliotheque.Personne;
import bibliotheque.exemplaires.Exemplaire;

public class Abonne extends Personne{
	private static int nbAbonnes=0;

	private ArrayList<Exemplaire> exemplairesEmpruntes;
	private int numeroAbonne;

	public Abonne(String nom, String prenom){
		super(nom, prenom);
		this.numeroAbonne=nbAbonnes;
		exemplairesEmpruntes=new ArrayList<Exemplaire>();
		nbAbonnes++;
	}

	public void emprunter(Exemplaire e){
		if (exemplairesEmpruntes.size()<5 && e.emprunter(this)){
			exemplairesEmpruntes.add(e);
		}
	}

	public void rendre(Exemplaire ex){
		if (ex.getEmprunteur()==this){
		ex.rendre();
		exemplairesEmpruntes.remove(ex);
		} else {
			ex.getEmprunteur().rendre(ex);
		}
	}

	@Override
	public String toString() {
		return "Abonne [nom=" + getNom() + ", numeroAbonne=" + numeroAbonne
				+ ", exemplairesEmpruntes=" + exemplairesEmpruntes + "]";
	}


	public int getNumeroAbonne() {
		return numeroAbonne;
	}

}
