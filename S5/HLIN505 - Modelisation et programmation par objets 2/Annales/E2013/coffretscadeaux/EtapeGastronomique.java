package coffretscadeaux;
import substitution.*;

public class EtapeGastronomique extends EtapeSejour {
	private String nomRestaurant;
	private double prixRepasUnePersonne;

	@substitutionComportementale(isRespected=true) 
	public String getNomRestaurant() {
		return nomRestaurant;
	}

	@substitutionComportementale(isRespected=true) 
	public void setNomRestaurant(String nomRestaurant) {
		this.nomRestaurant = nomRestaurant;
	}

	@substitutionComportementale(isRespected=true) 
	public double getPrixRepasUnePersonne() {
		return prixRepasUnePersonne;
	}

	@substitutionComportementale(isRespected=true) 
	public void setPrixRepasUnePersonne(double prixRepasUnePersonne) {
		this.prixRepasUnePersonne = prixRepasUnePersonne;
	}
	
	@substitutionComportementale(isRespected=true) 
	@Override
	public double getPrix()
	{
		return super.getPrix()+this.prixRepasUnePersonne;
	}
	
	@substitutionComportementale(isRespected=true) 
	public void setDuree2(double duree) throws DureeTropCourteException {
		if (this.getDuree() >=3) super.setDuree(duree);
		else System.out.println("la durŽe d'une Žtape gastronomique doit dŽpasser 3h");
	}

	@substitutionComportementale(isRespected=false) 
	@Override
	public void setDuree(double duree) throws DureeTropCourteException {
		if (this.getDuree() >=3) super.setDuree(duree);
		else throw new DureeTropCourteException("dans setDuree");
	}
}
