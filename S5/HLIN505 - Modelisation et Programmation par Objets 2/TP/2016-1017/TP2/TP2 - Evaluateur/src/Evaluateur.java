import java.util.*;

public class Evaluateur {
	private String operateurs = "+-*/";
	private Stack<Integer> operandes = new Stack<Integer>();
	
	public Evaluateur() {
	}
	
	public double resoudre(String operation){
		traiterOp(operation);
		return operandes.pop();
	}
	

	public void traiterOp(String operation){
		char caractereCourant;
		String valeurCourante = "";
		
		for(int i = 0 ; i < operation.length() ; i++) {
			caractereCourant = operation.charAt(i);
			
			if(!(estOperateur(caractereCourant))) {
				if(caractereCourant != ' ') {
					valeurCourante += caractereCourant;
				}
				else if(valeurCourante != "") {
					int foo = Integer.parseInt(valeurCourante);
					operandes.push(foo);
					valeurCourante = "";
				}
			}
			else {
				traiterOperateur(caractereCourant);
			}
		}
	}
	
	public boolean estOperateur(char c) {
		return operateurs.indexOf(c) != -1;
	}
	
	public void traiterOperateur(char ope) {		
		int total;
		
		switch(ope) {		
		case '+' :
			total = 0;
			for(int i = 0 ; i < operandes.size() ; i++){
				total += operandes.pop();
			}
			operandes.push(total);
			break;
			
		case '-' :
			total = 0;
			for(int i = 0 ; i < operandes.size() ; i++){
				total -= operandes.pop();
			}
			operandes.push(total);
			break;
			
		case '*' :
			total = 1;
			for(int i = 0 ; i < operandes.size() ; i++){
				total *= operandes.pop();
			}
			operandes.push(total);
			break;
			
		case '/' :
			total = 1;
			for(int i = 0 ; i < operandes.size() ; i++){
				total /= operandes.pop();
			}
			operandes.push(total);
			break;
			
		}
	}
}
