import java.io.*;

public class Personne {

	class Date {
		int jour;
		int mois;
		int annee;

		Date(){
			this.jour = 1;
			this.mois = 1;
			this.annee = 1900;
		}

		Date(String s){
			if(s.matches("[0-3][0-9]/[0-1][0-9]/[1-2][0-9][0-9][0-9]")){
				j = Integer.parseInt(s.substring(0, 2));
				m = Integer.parseInt(s.substring(3, 5));
				a = Integer.parseInt(s.substring(6, 10));
			}
			else {
				System.out.println("Format de date incorrect");
			}
		}
	}

	boolean verifDate(){
		return (jour > 0 && jour < 31) && (mois > 1 && mois < 12) && (annee > 1900 && annee <= new GregorianCalendar().get(Calendar.YEAR));
	}

	String formateInt(int v){
		if(v < 10)
			return "0" + v;
		else
			return v;
	}

	String formateDate(Date d){
		return formateInt
	}
}
