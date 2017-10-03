import java.io.*;

public class TestException {

	private class Exc1 extends RuntimeException {}
	private class Exc2 extends IOException {}
	
	public void f1() { throw new Exc1();}
	public void f2() { throw new Exc2();}
	
	static void main(String[] args){
		try{
			//f1();
			throw new Exc1();
		}catch(Exc1 e1) { System.out.println("Exception1");}
	}
}