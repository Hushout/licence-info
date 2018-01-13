public class Mot {
	private String mot;

	public Mot() {
		
	}
	
	public Mot(String s) {
		this.mot = s;
	}
	
	public String toString() {
		return mot;
	}
	
	public boolean isEmpty() {
		return mot == " ";
	}
	
	public boolean isPalindrome() {
		for(int i = 0 ; i < mot.length() / 2 ; i++) {
			if(mot.charAt(i) != mot.charAt(mot.length() - i - 1)) {
				return false;
			}
		}
		return true;
	}
}
