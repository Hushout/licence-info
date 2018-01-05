import java.util.*;

public class LivreEnfant {
 private int tpsLecture;
 private String titre;
 private NiveauPrimaire niveauMin,
						niveauMax;
 private Vector<FicheLecture> fiches;
 
 public NiveauPrimaire getNiveauMin(){
	 return niveauMin;
 }
 
 public NiveauPrimaire getNiveauMax(){
	 return niveauMax;
 }
 
 public int getTpsLecture(){
	 return tpsLecture;
 }
 
 public String getTitre(){
	 return titre;
 }
 
}
