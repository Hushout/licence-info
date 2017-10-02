public class FileAttenteStat extends FileAttente implements IFileAttenteStat {

    private int nbSorties;
    private int nbEntrees;

    public int getNbEntrees(){return nbEntrees;}

    public int getNbSorties(){return nbSorties;}

    //@override
    public void entre(Personne p){
	super.entre(p);
	nbEntrees++;
    }

    //@override
    public Personne sort(){
	nbSorties++;
	return super.sort();
    }
}
