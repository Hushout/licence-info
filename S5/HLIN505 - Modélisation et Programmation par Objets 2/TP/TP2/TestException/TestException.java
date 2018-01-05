import java.io.*;

public class TestException {

	class E1 extends RuntimeException {}
	class E2 extends IOException {}

	class E3 extends Exception {}

	class E31 extends E3 {}
	class E311 extends E31 {}

	class E32 extends E3 {}
	class E321 extends E32 {}

	public void f1() { throw new E1(); }
	public void f2() throws E2 { throw new E2(); }

	public void f3() throws E3 {
		System.out.println("debut\\_f3");
		try{
			f4();
		}
		catch(E31 e) {System.out.println(e.getClass().getName());}	
		finally {System.out.println("finally\\_f3");}
		System.out.println("suite\\_f3");
	}

	public void f4() throws E3 {
		System.out.println("debut\\_f4");
		try{
			f5();
		}
		catch(E321 e) {System.out.println(e.getClass().getName());}	
		catch(E32 e) {System.out.println(e.getClass().getName());}	
		finally {System.out.println("finally\\_f4");}
		System.out.println("suite\\_f4");
	}

	public void f5() throws E3 {
		System.out.println("debut\\_f5");
		E3 e = new E321();
		throw e;
	}

	public static void main(String[] args) throws E3{

		TestException t = new TestException();

		t.f3();
	}
}