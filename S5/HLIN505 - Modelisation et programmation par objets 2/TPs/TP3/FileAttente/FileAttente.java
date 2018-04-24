import java.util.ArrayList;
public class FileAttente implements IFileAttente {
    
    private String nomFile;
    private static String reglementationFile = "sans priorité";
    private ArrayList<Personne> contenu;
    
    public FileAttente(){contenu=new ArrayList<Personne>();}
    
    public void entre(Personne p){contenu.add(p);}
    
    public Personne sort()
    {
	Personne p=null;
	if (!contenu.isEmpty())
	    {p=contenu.get(contenu.size()-1);
		contenu.remove(contenu.size()-1);}
	return p;
    }
    
    public boolean estVide(){return contenu.isEmpty();}
    
    public int taille(){return contenu.size();}
    
    public String toString(){return ""+descriptionContenu();}
    
    private String descriptionContenu()
    {
	String resultat = "";
	for (Personne p:this.contenu)
	    resultat += p + " ";
	return resultat;
    }
    public void vider(){
	for (int i=0; i<taille(); i++)
	    this.sort();
    }
}
