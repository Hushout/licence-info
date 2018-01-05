package RectangleTortue;

public class Main {

	public static void main(String[] args){
		
		Rectangle R = new Rectangle(10, 3, 5, 5, "bleu");
		Rectangle R2 = new Rectangle(10, 3, 5, 5, "rouge");
		System.out.println(R);
		System.out.println("NbrRectangle total: " + R.getNbrRectangle());
	}
}
