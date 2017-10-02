package bibliotheque.notices;

import java.util.ArrayList;

import bibliotheque.exemplaires.Exemplaire;
import bibliotheque.exemplaires.Exemplaires;


public class NoticeBibliographique {

	private String titre;
	private String soustitre;
	private String isbn;
	private PublicCible cible;
	
	private Exemplaires exemplaires;	
	private ArrayList<Contribution> contributions;
	
 

	public NoticeBibliographique(String titre, String soustitre, String isbn, PublicCible cible) {
		contributions=new ArrayList<Contribution>();
		exemplaires=new Exemplaires(this);
		this.titre = titre;
		this.soustitre = soustitre;
		this.isbn = isbn;
		this.cible=cible;
	}


	public String getTitre() {
		return titre;
	}


	public String getSoustitre() {
		return soustitre;
	}


	public String getIsbn() {
		return isbn;
	}
	
	public ArrayList<Contributeur> getContributeurs(){
		ArrayList<Contributeur> resultat=new ArrayList<Contributeur>();
		for (Contribution c: contributions){
			resultat.add(c.getContributeur());
		}
		return resultat;
	}

	public void ajoutContribution(Contributeur c, ArrayList<NatureContribution> roles){
		Contribution contrib=new Contribution (roles, this, c);
		ajoutContrib(contrib);
	}

	public void ajoutContribution(Contributeur c, NatureContribution role){
		Contribution contrib=new Contribution (role, this, c);
		ajoutContrib(contrib);
	}

	private void ajoutContrib(Contribution contrib){
		contributions.add(contrib);
		contrib.getContributeur().ajoutContribution(contrib);
	}
	
	public Exemplaire addExemplaire(){
		return exemplaires.addExemplaire();
	}
	
	public boolean estDisponible(){
		return exemplaires.existeExemplaireDisponible();
	}
		
	public ArrayList<Exemplaire> exemplairesDisponibles(){
		return exemplaires.exemplairesDisponibles();
	}

	
	
	@Override
	public String toString() {
		String resultat= "NoticeBibliographique [titre=" + titre + ", contributions=";
		for (Contribution c:contributions){
			resultat+=c.getContributeur().getNom()+" "+c.getNature();
		}
		resultat+=		"]";
		return resultat;
	}


	public PublicCible getCible() {
		return cible;
	}
	
	public boolean aPourContributeur(String nom){
		for (Contributeur c: getContributeurs())
			if (c.getNom().equals(nom))
				return true;
		return false;
	}
}
