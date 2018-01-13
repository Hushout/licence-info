package coordonnees;

public class CoordonneesPolaires {
	private double distance;
	private double angle; // en radians

	public CoordonneesPolaires(double distance, double angle) {
		this.distance = distance;
		this.angle = angle;
	}
	
	public CoordonneesPolaires(){
		distance=0;
		angle=0;
	}

	public String toString() {
		return "CoordonneesPolaires [angle=" + angle + ", distance=" + distance
		+ "]";
	}

	public CoordonneesCartesiennes translateToCartesien(){
		double x=distance*Math.cos(angle);
		double y=distance*Math.sin(angle);

		return new CoordonneesCartesiennes(x,y);
	}

}
