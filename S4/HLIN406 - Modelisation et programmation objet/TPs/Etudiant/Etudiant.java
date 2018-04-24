package Etudiant;

public class Etudiant extends Personne{
    
    public CodeIns codeIns;
    public CodePays codePays;
    public float note[] = new float[3];
    public Mention mention;

    public Etudiant(int age, int dateNaiss, String nom, CodeIns codeIns, CodePays codePays, float note1, float note2, float note3){

	super(age, dateNaiss, nom);
	this.codeIns = codeIns;
	this.codePays = codePays;
	this.note[0] = note1;
	this.note[1] = note2;
	this.note[2] = note3;
	this.mention = this.mention();
    }

    public float moy(){
	return (note[0] + note[1] + note[2])/3;
    }

    public Mention mention(){
	float m = this.moy();
	
	if(m >= 18){
	    return Mention.Feli;
	}
	else if(m >= 16){
	    return Mention.TB;
	}
	else if(m >= 14){
	    return Mention.B;
	}
	else if(m >= 12){
	    return Mention.AB;
	}
	else if(m >= 10){
	    return Mention.Pass;
	}
	else{
	    return Mention.AJ;
	}
    }

    public String ligneResultat(){
	return nom + " " + moy() + " " + mention.name();
    }
}
