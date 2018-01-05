public class PochetteJeunesse<E extends DocumentJeunesse> extends Pochette<E> {
	private int minAge;

	public PochetteJeunesse() {
		super();
	}

	public PochetteJeunesse(int minAge){
		super();
		this.minAge = minAge;
	}

	public void add(E e) throws DocumentException {
		if(e.getMinAge() > minAge) 
			throw new DocumentMinAgeException();
		else
			super.add(e);
	}
}