package Pieces;

public class TestPieces{

	public static void main(String[] args){
		Piece Clou = new Piece("Clou", "003481", 0.01F, 0, 1);
		Piece Planche = new Piece("Planche", "00342", 1, 0, 1);
		
		PieceCompositeMontee PlancheCloue = new PieceCompositeMontee("PlancheCloue", "021293", 1, 0, 1, 1, 1);
		PlancheCloue.ajoute(Clou);
		PlancheCloue.ajoute(Planche);
		
		PieceCompositeKit Palette = new PieceCompositeKit("Palette en kit", "01234", 1, 0, 1, 1);
		Palette.ajoute(Planche);
		Palette.ajoute(Clou);
		Palette.ajoute(PlancheCloue);
		Palette.affiche();
	}
}