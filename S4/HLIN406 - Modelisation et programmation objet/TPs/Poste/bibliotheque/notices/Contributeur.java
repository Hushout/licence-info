package bibliotheque.notices;

import java.util.ArrayList;

import bibliotheque.Personne;

public class Contributeur extends Personne{


	private ArrayList<Contribution> contributions;

	
	
	public Contributeur(String nom, String prenom) {
		super(nom, prenom);
		contributions=new ArrayList<Contribution>();
	}

	void ajoutContribution(Contribution contrib) {
		if (this==contrib.getContributeur()){
			contributions.add(contrib);
		}

	}

	public ArrayList<NoticeBibliographique> getNotices(){
		ArrayList<NoticeBibliographique> resultat=new ArrayList<NoticeBibliographique>();
		for (Contribution c: contributions){
			resultat.add(c.getNotice());
		}
		return resultat;
	}

}
