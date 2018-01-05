package Pieces;

public class PieceCompositeMontee extends PieceComposite{
	
	private float dureeMontAtelier;
	private float prixMontage;
	
	public PieceCompositeMontee(String nom, String reference, float prix, float garantie, float dureeFab, float dureeMontAtelier, float prixMontage){
		super(nom, reference, prix, garantie, dureeFab);
		this.dureeMontAtelier = dureeMontAtelier;
		this.prixMontage = prixMontage;
	}
	
	public void affiche(){
		super.affiche();
		System.out.println("duree de montage atelier : " + dureeMontAtelier + " jour(s)" +
		"\nprix du montage : " + prixMontage + " euros" +
		"\ncomposants : ");
		afficheComposants(4);
	}
}