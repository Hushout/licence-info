package tpTest.foobar;

public class SUT {
	private int x;
	private int y;
	private int z;

	public SUT(int x, int y, int z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	public SUT(){
		x=1;
		y=3;
		z=5;
	}

	/**
	 * Si t est strictement plus petit que x, on retourne x, sinon si t est strictement plus grand que z, on retourne z, sinon on retourne y.
	 * @param t un entier quelconque
	 * @return x si t<x, z si t>z, y sinon 
	 */
	public int foo(int t){
		int resultat=0;
		if (t<x) resultat=x;
		if (t>z) resultat=z;
		else resultat=y;
		return resultat;
	}
	
	/**
	 * décale circulairement les valeurs de x, y et z : x prend la valeur de y, y prend la valeur de z et z prend la valeur de x
	 */
	public void bar(){
		int temp=x;
		x=y;
		y=z;
		z=temp;
	}
	
	/**
	 * 
	 */
	public void foobar()throws FooBarException{
		if (x<0) throw new FooBarException();
	}
}
