package RectangleTortue;

public class Rectangle {
	
	private float x;
	private float y;
	private float longueur;
	private float largeur;
	private String color;
	
	private static final int nbc = 4;
	private static final float angleC = 90;
	
	private static int nbrRectangle;
	
	public Rectangle(){
		this.x = 0;
		this.y = 0;
		this.longueur = 0;
		this.largeur = 0;
		this.color = "aucune";
		nbrRectangle++;
	}
	
	public Rectangle(float x, float y, float longueur, float largeur, String color){
		this.x = x;
		this.y = y;
		this.longueur = longueur;
		this.largeur = largeur;
		this.color = color;
		nbrRectangle++;
	}
	
	public String toString(){
		return "Rectangle, position: (" + x + ", " + y + "), format: (" + longueur + ", " + largeur + "), Couleur: " + color; 
	}
	
	public float getX(){
		return x;
	}
	
	public float getY(){
		return y;
	}
	
	public float getLongueur(){
		return longueur;
	}
	
	public float getLargeur(){
		return largeur;
	}
	
	public String getColor(){
		return color;
	}
	
	public float getPerimetre(){
		return 2 * longueur + 2 * largeur;
	}
	
	public float getAire(){
		return longueur * largeur;
	}
	
	public int getNbc(){
		return nbc;
	}
	
	public float getAngleC(){
		return angleC;
	}
	
	public int getNbrRectangle(){
		return nbrRectangle;
	}
}