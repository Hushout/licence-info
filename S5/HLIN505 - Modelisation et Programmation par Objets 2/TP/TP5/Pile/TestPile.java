public class TestPile {

	public static void main(String[] args){
		
		Pile<Integer> p = new Pile<>();

		System.out.println("Integer:");

		for(int i = 0 ; i < 10 ; i++)
			p.empile(i);

		System.out.println(p);

		for(int i = 0 ; i < 3 ; i++)
			p.depile();

		System.out.println(p);

		System.out.println("String:");

		Pile<String> p2 = new Pile<>();

		p2.empile("Romain");
		p2.empile("Beaucoup");
		p2.empile("J'aime");

		System.out.println(p2);
		System.out.println(p2.nbElements());

	}
}
