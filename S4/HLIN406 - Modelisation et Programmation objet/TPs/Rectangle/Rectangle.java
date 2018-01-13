public class Rectangle implements IRectangle {
	
	private	float x;
	private float y;
	private float largeur;
	private float hauteur;
	private String couleur;
	
	private static Rectangle plusGrandRectangle;
	
	public Rectangle(){
		this.x = 0;
		this.y = 0;
		this.largeur = 0;
		this.hauteur = 0;
		this.couleur = "blanc";
		
		if(plusGrandRectangle == null){
			plusGrandRectangle = this;
		}
	}
	
	public Rectangle(float x, float y, float largeur, float hauteur, String couleur){
		this.x = x;
		this.y = y;
		this.largeur = largeur;
		this.hauteur = hauteur;
		this.couleur = couleur;
		
		if(plusGrandRectangle == null){
			plusGrandRectangle = this;
		}
		else{
			if(aire() > plusGrandRectangle.aire()){
				plusGrandRectangle = this;
			}
		}
	}
	
	public String toString(){
		return "position: (" + x + ", " + y + "), format: (" + largeur + ", " + hauteur + "), Couleur: " + couleur; 
	}
	
	public float x(){return x;}
	
	public float y(){return y;}
	
	public float largeur(){return largeur;}
	
	public float hauteur(){return hauteur;}
	
	public String couleur(){return couleur;}
	
	public float perimetre(){return 2 * hauteur + 2 * largeur;}
	
	public float aire(){return hauteur * largeur;}
	
	public float angle(){return angle;}
	
	public Rectangle plusGrandRectangle(){return plusGrandRectangle;}
}