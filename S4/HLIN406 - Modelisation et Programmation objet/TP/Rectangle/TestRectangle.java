public class TestRectangle {

	public static void main(String[] args){
		
		IRectangle R = new Rectangle(10, 12, 5, 5, "blanc");
		IRectangle R2 = new Rectangle(1, 2, 2, 5, "rouge");
		Rectangle R3 = new Rectangle(1, 2, 10, 10, "rose");
		
		System.out.println(R);
		System.out.println(R2);
		System.out.println(R3);
		
		System.out.println();
		
		System.out.println(R.plusGrandRectangle());
		System.out.println(R2.plusGrandRectangle());
		System.out.println(R3.plusGrandRectangle());
	}
}