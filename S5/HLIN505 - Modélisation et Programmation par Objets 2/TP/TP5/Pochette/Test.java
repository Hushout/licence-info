public class Test {

	public static void main(String[] args){
		Document doc = new Livre();
		DocumentJeunesse docJ = new LivreJeunesse();
		GuideVoyage guide = new GuideVoyage();
		GuideVoyage guide2 = new GuideVoyage();
		Livre livre = new Livre();
		LivreJeunesse livreJ = new LivreJeunesse(5);
		LivreJeunesse livreJ2 = new LivreJeunesse(10);

		Pochette<GuideVoyage> p = new Pochette<>();
		Pochette<Document> pD = new Pochette<>();

		Pochette<Livre> pL = new Pochette<>();
		Pochette<LivreJeunesse> pLJ = new Pochette<>();
		PochetteJeunesse<LivreJeunesse> pJLJ  = new PochetteJeunesse<>();

 		PochetteJeunesse<DocumentJeunesse> pJ = new PochetteJeunesse<>(7);

		try{
			pD.add(doc);
			pD.add(docJ);

			p.add(guide);
			p.add(guide2);

			p.transferTo(pD);

			pJLJ.transferTo(pL);
			//pLJ.transferTo(pL);
			//pD.add(guide);
			//p.add(doc);

			pJ.add(livreJ);
			System.out.println("1er livre ajouter");

			pJ.add(livreJ2);
			System.out.println("2eme livre ajouter");

		}
		catch(DocumentMinAgeException e){System.out.println("Mauvais age");}
		catch (Exception e) {System.out.println(e.getMessage());}
		finally{System.out.println("Fin du main");}
	}
}