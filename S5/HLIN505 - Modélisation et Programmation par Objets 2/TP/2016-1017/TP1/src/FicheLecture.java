import java.util.*;
import java.math.*;

public class FicheLecture{
	private NiveauPrimaire niveau;
	private LivreEnfant livre;
	private Vector<Question> questions;
	
	public NiveauPrimaire getNiveau(){
		return this.niveau;
	}
	public FicheLecture(LivreEnfant livre, NiveauPrimaire niveau){
		this.livre = livre;
		this.niveau = niveau;
		questions = new Vector<Question>();
	}
	
	public void ajoutQuestion(Question q){
		if(q.getLivre() == livre && !questions.contains(q)){
			questions.add(q);
		}
		else{
			System.out.println("Erreur");
		}
	}
	
	public int tempsTravail(){
		double tpsTravail = 0;
		tpsTravail += livre.getTpsLecture();
		for(Question q : questions){
			tpsTravail += q.getTpsReponse();
		}
		tpsTravail = Math.ceil(tpsTravail + tpsTravail / 10);
		return (int)tpsTravail;
	}
	
	public boolean estBienFormee(){
		if(this.tempsTravail() > 45){
			return false;
		}
		for(Question q : questions){
			if((q.getNiveauMin().getValue() > this.getNiveau().getValue()) 
				|| (q.getNiveauMax().getValue() < this.getNiveau().getValue())){
				return false;
			}
		}
		return true;
	}
	
	public static void main(String [] args){
		FicheLecture fiche = new FicheLecture(CP, new LivreEnfant(10, "Lulu Vroumette", CP, CE1));
	}
}