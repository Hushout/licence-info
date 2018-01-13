package coordonnees;

public class CoordonneesCartesiennes {
	private double x;
	private double y;

	public CoordonneesCartesiennes(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public CoordonneesCartesiennes(){
		x=0;
		y=0;
	}

	public String toString() {
		return "CoordonneesCartesiennes [x=" + x + ", y=" + y + "]";
	}

	public CoordonneesPolaires translateToPolaire(){
		double distance=Math.sqrt(x*x+y*y);
		double angle;
		if (x>0){
			angle=Math.atan(y/x);}
		else if (x<0){
			angle=Math.atan(y/x)+Math.PI;
		}
		else {
			angle=0;
		}
		return new CoordonneesPolaires(distance, angle);
	}

	public void translation(double x, double y){
		//this.x=this.x+x;
		this.x+=x;
		this.y=this.y+y;
	}

}
