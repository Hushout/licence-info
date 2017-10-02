
public class Question {
 private FormeQuestion forme;
 private LivreEnfant livre;
 private int tpsReponse;
 private String texte;
 private NiveauPrimaire niveauMin,
 		 				niveauMax;
 
 public Question(int temps, String texte, FormeQuestion forme, NiveauPrimaire min, NiveauPrimaire max, LivreEnfant livre){
	 this.tpsReponse = temps;
	 this.livre = livre;
	 this.texte = texte;
	 this.niveauMax = max;
	 this.niveauMin = min;
	 this.forme = forme;
 }

 public LivreEnfant getLivre(){
	 return livre;
 }
 
 public int getTpsReponse(){
	 return tpsReponse;
 }
 
 public String getTexte(){
	 return texte;
 }
 
 public NiveauPrimaire getNiveauMin(){
	 return niveauMin;
 }
 
 public NiveauPrimaire getNiveauMax(){
	 return niveauMax;
 }
}
