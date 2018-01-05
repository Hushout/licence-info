public class Test {

	public static void main(String [] args) {
		String operation = "2 23 7 + 2 *";
		Evaluateur eval = new Evaluateur();
		System.out.println(operation);
		System.out.println(eval.resoudre(operation));
	}
}
