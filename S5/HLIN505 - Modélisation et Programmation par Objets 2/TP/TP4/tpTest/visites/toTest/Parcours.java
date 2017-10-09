package tpTest.visites.toTest;
import java.util.Vector;


public class Parcours {
	private Vector<Troncon> troncons=new Vector<Troncon>();

	public void ajoutTroncon(Troncon t){
		boolean ajout=true;

		if (!troncons.isEmpty()){
			Troncon dernierTroncon = troncons.lastElement();
			if (dernierTroncon.getArrivee()!=t.getDepart()){
				System.out.println("erreur");
				ajout=false;
			}
		}
		if (ajout){
			troncons.add(t);
		}		
	}
/***
 * Calcul de la durée du parcours
 * @return somme des temps de trajet des tronçons et des visites des étapes
 */
	public int calculDuree(){
		int resultat=0;
		for (Troncon t:troncons){
			resultat+=t.getTempsTrajet();
			resultat+=t.getDepart().getDureeVisite();
		}
		return resultat;
	}

	/**
	 *  méthode permettant de déterminer s'il y a des boucles dans le circuit, autre que début/arrivée si le parcours est un circuit.
	 *  On considère qu'il y a une boucle dès qu'il y a à l'intérieur du parcours deux passages par la même étape.
	 * @return retourne vrai ssi il y a au moins une boucle dans le parcours, autre que début/arrivée
	 */
	public boolean existeBoucle(){
		Vector<Etape> etapes=new Vector<Etape>();
		for (Troncon t:troncons){
			etapes.add(t.getDepart());
			etapes.add(t.getArrivee());
		}
		int posEtape=0;
		for (Etape etape:etapes){
			for (int i=posEtape+1;i<etapes.size();i++){
				// on regarde de posEtape+1 à la fin de etapes s'il y a une étape égale à etape
				if (etapes.get(i).equals(etape)){
					return false;
				}
			}
			posEtape++;
		}
		return true;
	}
/**
 * permet de déterminer si le parcours est un circuit (termine au point de départ)
 * @return vrai ssi le départ et l'arrivée sont indentiques.
 */
	public boolean estUnCircuit(){
		return troncons.firstElement().getDepart().equals(troncons.lastElement().getArrivee()); 
	}
}
