package coffretscadeaux;

public class EtapeSejour implements Iprestation, IetapeSejour {

	private double duree;
	private String descriptif;
	private double longueur;
	private double prixHebergementDemiPension;
	
	public double getDuree() {
		return duree;
	}
	public void setDuree(double duree) throws DureeTropCourteException {
		this.duree = duree;
	}
	public String getDescriptif() {
		return descriptif;
	}
	public void setDescriptif(String descriptif) {
		this.descriptif = descriptif;
	}
	public double getLongueur() {
		return longueur;
	}
	public void setLongueur(double longueur) {
		this.longueur = longueur;
	}
	
	public double getPrixHebergementDemiPension() {
		return prixHebergementDemiPension;
	}
	public void setPrixHebergementDemiPension(double prixHebergementDemiPension) {
		this.prixHebergementDemiPension = prixHebergementDemiPension;
	}
	
	@Override
	public double getPrix() {
		return this.getPrixHebergementDemiPension() + 2;
	}
	
public static void main(String[] argv) throws DureeTropCourteException
{
	EtapeSejour e = new EtapeSejour();
	e.setDuree(2);
	System.out.println(e.getDuree());
	e = new EtapeGastronomique();
	//e.setDuree(2);
	System.out.println(e.getDuree());
	System.out.println(e.getClass().getName());
	
}
}