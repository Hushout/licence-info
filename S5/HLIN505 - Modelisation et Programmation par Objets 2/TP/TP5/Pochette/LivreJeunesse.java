public class LivreJeunesse extends Livre implements DocumentJeunesse {
	private int minAge;

	public LivreJeunesse() {
	    minAge = 1;
	}

	public LivreJeunesse(int minAge){
		this.minAge = minAge;
	}

	public int getMinAge() {
	    return minAge;
	}
}