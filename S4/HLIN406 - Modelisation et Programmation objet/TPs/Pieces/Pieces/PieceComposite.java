package Pieces;

import java.util.Vector;

public class PieceComposite extends Piece{
	
	private Vector<Piece> composants;
	
	public PieceComposite(String nom, String reference, float prix, float garantie, float dureeFab){
		super(nom, reference, prix, garantie, dureeFab);
		composants = new Vector<Piece>();
	}
	
	public void ajoute(Piece P){
		composants.add(P);
	}
	
	protected void afficheComposants(int nbEspace){
	
		for(int i = 0 ; i < composants.size() ; i++){
			
			for(int j = 0 ; j < nbEspace ; j++){
				System.out.print(" ");
			}
			
			System.out.println(composants.elementAt(i));
			
			if(composants.elementAt(i).reference().charAt(1) != '0'){
				nbEspace += 4;
			}
			
			composants.elementAt(i).afficheComposants(nbEspace);
		}
	}
	
}