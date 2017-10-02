public class ExpressionComplexe extends Expression {
	private double v1;
	private double v2;
	private char op;
	
	public ExpressionComplexe(Expression v1 , char op , Expression v2) {
		this.v1 = v1.eval();
		this.v2 = v2.eval();
		this.op = op;
	}
	
	public double eval() {
		switch(op) {
		case '+' :
			return v1 + v2;
			
		case '-' :
			return v1 - v2;
			
		case '/' :
			return v1 / v2;
			
		case '*' :
			return v1 * v2;	
		}
		return 0;
	}
}
