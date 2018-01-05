public class Operation {
	public static int addition(int a, int b){
		return a + b;
	}

	public static int soustraction(int a, int b){
		return a - b;
	}

	public static int multiplication(int a, int b){
		return a * b;
	}

	public static int division(int a, int b){
		if(b == 0){
			throw new IllegalArgumentException("Argument 'divisor' is 0");
		}
		return a / b;
	}

	public static int modulo(int a, int b){
		return a % b;
	}
}