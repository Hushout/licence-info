package Panier;

import java.util.*;
import Pieces.*;

public class Achat {

	private Piece piece;
	private int quantitee;

	public Achat(Piece piece, int quantitee){
		this.piece = piece;
		this.quantitee = quantitee;
	}
	
	public int quantitee(){
		return quantitee;
	}

	public Piece piece(){
		return piece;
	}
	
	public void incrementer(){
		quantitee += 1;
	}
	
	public void decrementer(){
		if(quantitee > 0){
			quantitee -= 1;
		}
	}
	
	public static class Comparators {

        public static Comparator<Achat> NOM = new Comparator<Achat>() {
            public int compare(Achat A1, Achat A2) {
                return A1.piece().nom().compareTo(A2.piece().nom());
            }
        };
		
		public static Comparator<Achat> PRIX = new Comparator<Achat>() {
            public int compare(Achat A1, Achat A2) {
                return Float.compare(A1.piece().prix(), A2.piece().prix());
            }
        };
    }
}