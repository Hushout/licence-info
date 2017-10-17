public class Personne implements ElementAvecPriorite {

    private String nom;
    private int age;
    public Personne(){}
    public Personne(String n, int a){nom = n; age = a;}
    public String getNom(){return nom;}
    public void setNom(String n){nom = n;}
    public int getAge(){return age;}
    public void setAge(int a){age = a;}
    public String toString(){return nom+" "+age;}

    public int priorite(){
	if(age >= 0 && age <= 12)
	    return 1;
	else if(age >= 60)
	    return 2;
	else
	    return 3;
    }
}
