import java.util.*;

public class Test {

	public static void main(String [] args) {
		String mot = new String();
		if(args.length == 0) {
			Scanner sc = new Scanner(System.in);
			System.out.println("Entrez un mot");
			mot = sc.nextLine();
		}
		else{
			mot = args[0];
		}
		Mot m = new Mot(mot);
		
		if(m.isPalindrome()) {
			System.out.println("C'est un palindrome");
		}
		else {
			System.out.println("Ce n'est pas un palindrome");
		}
	}
}
