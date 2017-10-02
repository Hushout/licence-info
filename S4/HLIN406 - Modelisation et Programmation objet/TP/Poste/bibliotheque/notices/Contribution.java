package bibliotheque.notices;

import java.util.ArrayList;

public class Contribution {
	private ArrayList<NatureContribution> nature;
	private NoticeBibliographique notice;
	private Contributeur contributeur;
	public NoticeBibliographique getNotice() {
		return notice;
	}
	public Contributeur getContributeur() {
		return contributeur;
	}
	public Contribution(NoticeBibliographique notice, Contributeur contributeur) {
		this.nature = new ArrayList<NatureContribution>(); 
		this.notice = notice;
		this.contributeur = contributeur;
	}
	public Contribution(ArrayList<NatureContribution> nature, NoticeBibliographique notice, Contributeur contributeur) {
		this(notice, contributeur);
		this.nature = nature;
	}
	
	public Contribution(NatureContribution nature, NoticeBibliographique notice, Contributeur contributeur) {
		this(notice, contributeur);
		this.nature.add(nature);
	}
	
	public ArrayList<NatureContribution> getNature() {
		return nature;
	}
	
	public void addNature(NatureContribution nature){
		this.nature.add(nature);
	}
}
