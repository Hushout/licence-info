package bibliotheque;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Set;

import bibliotheque.notices.NoticeBibliographique;

public class Catalogue {
	private Hashtable<String, NoticeBibliographique> ouvrages=new Hashtable<String, NoticeBibliographique>();

	public void addNotice(NoticeBibliographique l){
		ouvrages.put(l.getIsbn(), l);
	}
	
	public NoticeBibliographique getNoticeByISBN(String isbn){
		return ouvrages.get(isbn);
	}
	
	public ArrayList<NoticeBibliographique> rechercheContrib(String nomContrib){
		ArrayList<NoticeBibliographique> liste = new ArrayList<NoticeBibliographique>();
		Set<String> listeIsbn = ouvrages.keySet();
		for (String isbn:listeIsbn){
			NoticeBibliographique not = ouvrages.get(isbn);
			if (not.aPourContributeur(nomContrib))
				liste.add(not);
		}
		return liste;
	}
}
