public class CoupleConventionnel<A extends Animal & Male, B extends Animal & Femelle> extends Paire<A, B> {

	public CoupleConventionnel() {
		super();
	}

	public CoupleConventionnel(A a, B b) {
		super(a, b);
	}
}