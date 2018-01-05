package bibliotheque;

import java.util.ArrayList;

import bibliotheque.notices.Contributeur;
import bibliotheque.notices.NatureContribution;
import bibliotheque.notices.NoticeBibliographique;
import bibliotheque.notices.PublicCible;

public class TestBibli {
public static void main(String[] args){
	Contributeur dp=new Contributeur("Pennac", "Daniel");
	Contributeur am=new Contributeur("Mizubayashi", "Akira");
	Contributeur eg=new Contributeur("Gravett", "Emily");
	
	NoticeBibliographique feeCarabine=new NoticeBibliographique("la féé carabine", null, "????", PublicCible.adulte);
	feeCarabine.ajoutContribution(dp, NatureContribution.redaction);
	System.out.println(feeCarabine);
	
	NoticeBibliographique ulvda=new NoticeBibliographique("unlangue venue d'ailleurs", null,  "????", PublicCible.adulte);
	ulvda.ajoutContribution(am, NatureContribution.redaction);
	ulvda.ajoutContribution(dp, NatureContribution.redactionPreface);
	System.out.println(ulvda);
	
	NoticeBibliographique encore=new NoticeBibliographique("Encore", null, "??????", PublicCible.enfant);
	ArrayList<NatureContribution> nat=new ArrayList<NatureContribution>();
	nat.add(NatureContribution.redaction);
	nat.add(NatureContribution.illustration);
	encore.ajoutContribution(eg,  nat);
	System.out.println(encore);
	
}
}
