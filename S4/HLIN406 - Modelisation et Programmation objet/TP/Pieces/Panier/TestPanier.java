package Panier;

import Pieces.*;

public class TestPanier{

	public static void main(String[] args){
		Piece Clou = new Piece("Clou", "003481", 0.01F, 0, 1);
		Piece Planche = new Piece("Planche", "00342", 10, 0, 1);
		Piece Couteau = new Piece("Couteau", "00442", 2, 0, 1);
		Piece Fourchette = new Piece("Fourchette", "00542", 1, 0, 1);
		Piece Arbalette = new Piece("Arbalette", "00142", 100, 0, 1);
		
		Achat A = new Achat(Clou, 3);
		
		Panier panier = new Panier();
		
		panier.ajouter(Clou);
		panier.ajouter(Planche);
		panier.ajouter(Clou);
		panier.ajouter(Couteau);
		panier.ajouter(Fourchette);
		panier.ajouter(Arbalette);
		panier.affiche();
		
		System.out.println("//////////////////////////");
		panier.triAlpha();
		panier.affiche();
	}
}