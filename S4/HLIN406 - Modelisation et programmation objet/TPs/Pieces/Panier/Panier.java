package Panier;

import java.util.*;
import Pieces.*;

public class Panier{

	private List<Achat> achats;

	public Panier(){
		achats = new ArrayList<Achat>();
	}
	
	public void ajouter(Piece P){
		
		boolean dejaPresent = false;
		
		for(int i = 0 ; i < achats.size() ; i++){
			
			if(achats.get(i).piece().reference() == P.reference()){
				dejaPresent = true;
				achats.get(i).incrementer();
			}
		}
		
		if(!dejaPresent){
			achats.add(new Achat(P, 1));
		}
	}
	
	public void supprimer(Piece P){
		
		boolean dejaPresent = false;
		
		for(int i = 0 ; i < achats.size() ; i++){
			
			if(achats.get(i).piece().reference() == P.reference()){
				achats.get(i).decrementer();
				if(achats.get(i).quantitee() == 0){
					achats.remove(i);
					i--;
				}
			}
		}
	}
	
	public void affiche(){
		
		for(int i = 0 ; i < achats.size() ; i++){
			System.out.println(achats.get(i).piece() + " quantite: " + achats.get(i).quantitee());
		}
	}
	
	public void triPrix(){
		Collections.sort(achats, Collections.reverseOrder(Achat.Comparators.PRIX));
	}
	
	public void triAlpha(){
		Collections.sort(achats, Achat.Comparators.NOM);
	}
}