public class ExpressionComplexe {

	private Constante c1;
	private Constante c2;
	private String op;

	public ExpressionComplexe(){
		c1 = new Constante();
		c2 = new Constante();
		op = new String();
	}

	public ExpressionComplexe(Constante c1, String op, Constante c2){
		this.c1 = c1;
		this.op = op;
		this.c2 = c2;
	}

	public ExpressionComplexe(ExpressionComplexe e1, String op, Constante c2){
		this.c1 = new Constante(e1.eval());
		this.op = op;
		this.c2 = c2;
	}

	public ExpressionComplexe(Constante c1, String op, ExpressionComplexe e1){
		this.c1 = c1;
		this.op = op;
		this.c2 =  new Constante(e1.eval());
	}

	public float eval() {
		if(op == "*")
			return this.c1.eval() * this.c2.eval();

		if(op == "+")
			return this.c1.eval() + this.c2.eval();

		if(op == "-")
			return this.c1.eval() - this.c2.eval();

		if(op == "/")
			return this.c1.eval() / this.c2.eval();

		return 0;
	}
}
