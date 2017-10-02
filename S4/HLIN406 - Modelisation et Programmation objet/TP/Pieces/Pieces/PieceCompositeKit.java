package Pieces;

public class PieceCompositeKit extends PieceComposite{
	
	private float dureeMontParticulier;
	
	public PieceCompositeKit(String nom, String reference, float prix, float garantie, float dureeFab, float dureeMontParticulier){
		super(nom, reference, prix, garantie, dureeFab);
		this.dureeMontParticulier = dureeMontParticulier;
	}
	
	public void affiche(){
		super.affiche();
		System.out.println("duree de montage particulier : " + dureeMontParticulier + " mn(s)" +
		"\ncomposants : ");
		afficheComposants(4);
	}
}