package bibliotheque.abonnes;

import bibliotheque.exemplaires.Exemplaire;
import bibliotheque.notices.PublicCible;

public class Mineur extends Abonne{
public void emprunter(Exemplaire e){
	if (!(e.getNotice().getCible()==PublicCible.adulte)){
		super.emprunter(e);
	}
}

public Mineur(String nom, String prenom) {
	super(nom, prenom);
}

}
