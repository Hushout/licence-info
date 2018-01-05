package coordonnees;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		CoordonneesCartesiennes cc=new CoordonneesCartesiennes(20,10);
		System.out.println(cc); // System.out.println(cc.toString();
		cc.translation(0,10);
		System.out.println(cc);
		CoordonneesPolaires cp=cc.translateToPolaire();
		System.out.println(cp);
		CoordonneesCartesiennes cc2=cp.translateToCartesien();
		System.out.println(cc2);
	}

}
