import java.io.*;

public class TestExpression{

	public static void main(String[] arg){
		Constante a = new Constante(5);
		Constante b = new Constante(2);
		Constante c = new Constante(3);
		
		ExpressionComplexe e1 = new EéxpressionComplexe(a, "+", b);
		ExpressionComplexe e2 = new ExpressionComplexe(e1, "*", c);
		ExpressionComplexe e3 = new ExpressionComplexe(new Constante(4), "*", e2);

		System.out.println(a.eval());
		System.out.println(e1.eval());
		System.out.println(e2.eval());
		System.out.println(e3.eval());
	}
}
