package bibliotheque.exemplaires;

import bibliotheque.abonnes.Abonne;
import bibliotheque.notices.NoticeBibliographique;

public class Exemplaire {
	private NoticeBibliographique notice;
	private Abonne emprunteur;
	private boolean enReparation;
	
	
	
	public Exemplaire(NoticeBibliographique notice) {
		enReparation=false;
		this.notice = notice;
	}

	
	
	public boolean estDisponible(){
		return emprunteur==null && !enReparation;
	}
	
	public boolean emprunter(Abonne a){
		boolean resultat=false;
		if (estDisponible()){
			emprunteur=a;
			resultat=true;
		}
		return resultat;
	}

	public NoticeBibliographique getNotice() {
		return notice;
	}

	public Abonne getEmprunteur() {
		return emprunteur;
	}

	public boolean isEnReparation() {
		return enReparation;
	}

public void rendre(){
	emprunteur=null;
}

	@Override
	public String toString() {
		if (emprunteur!=null){
		return "Exemplaire [livre=" + notice.getTitre() + ", emprunteur=" + emprunteur.getNom()
				+ ", enReparation=" + enReparation + "]";
		} else return "Exemplaire [livre=" + notice.getTitre() + ", emprunteur=null"
				+ ", enReparation=" + enReparation + "]";
	}
}
