package Etudiant;

public class Main{

    public static void main(String args[]){

	Etudiant E = new Etudiant(15, 1990, "Bob", CodeIns.Prem, CodePays.Francais, Float.valueOf(args[0]), Float.valueOf(args[1]), Float.valueOf(args[2]));

	System.out.println(E.ligneResultat());
    }
}
