package bibliotheque;

import bibliotheque.abonnes.Abonne;
import bibliotheque.abonnes.Mineur;
import bibliotheque.exemplaires.Exemplaire;
import bibliotheque.notices.Contributeur;
import bibliotheque.notices.NatureContribution;
import bibliotheque.notices.NoticeBibliographique;
import bibliotheque.notices.PublicCible;

public class TestBibliotheque {

	public static void main(String[] args) {
		Contributeur ja=new Contributeur("Austen", "Jane");
		NoticeBibliographique emma=new NoticeBibliographique("Emma", null, "123",  PublicCible.adulte);
		emma.ajoutContribution(ja, NatureContribution.redaction);
		Exemplaire exEmma=emma.addExemplaire();
		System.out.println(emma);
		System.out.println(exEmma);
		Abonne lucie=new Abonne("Doe", "Lucie");
		Abonne sophie =new Abonne("Parmentier", "Sophie");
		System.out.println(lucie);
		lucie.emprunter(exEmma);
		sophie.emprunter(exEmma);
		System.out.println(lucie);
		System.out.println(exEmma);
		lucie.rendre(exEmma);
		System.out.println(lucie);
		System.out.println(exEmma);
		Mineur anna=new Mineur("Smith", "Anna");
		anna.emprunter(exEmma);
		System.out.println(anna);
		
		Catalogue bibli=new Catalogue();
		bibli.addNotice(emma);
		NoticeBibliographique l=bibli.getNoticeByISBN("123");
		System.out.println(l);
	}

}
