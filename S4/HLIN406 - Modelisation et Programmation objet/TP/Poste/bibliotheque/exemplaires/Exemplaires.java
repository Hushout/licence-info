package bibliotheque.exemplaires;

import java.util.ArrayList;

import bibliotheque.notices.NoticeBibliographique;

public class Exemplaires {
private ArrayList<Exemplaire> exemplairesReferences=new ArrayList<Exemplaire>();
private NoticeBibliographique notice;
	


	public Exemplaires(NoticeBibliographique notice) {
	this.notice = notice;
}

	public Exemplaire addExemplaire(){
		Exemplaire e=new Exemplaire(notice);
		exemplairesReferences.add(e);
		return e;
	}
	
	public boolean existeExemplaireDisponible(){
		boolean resultat=false;
		for (Exemplaire e:exemplairesReferences){
			if (e.estDisponible()){
				return true;
			}
		}
		return resultat;
	}
	
	public int nbExemplairesDisponibles(){
		return exemplairesDisponibles().size();
	}
	
	public ArrayList<Exemplaire> exemplairesDisponibles(){
		ArrayList<Exemplaire> result=new ArrayList<Exemplaire>();
		for (Exemplaire e:exemplairesReferences){
			if (e.estDisponible()){
				result.add(e);
			}
		}
		return result;
	}


}
