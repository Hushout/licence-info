package coffretscadeaux;

public class CoffretSejour extends CoffretCadeau<IetapeSejour> {

	public static void main(String[] argv)
	{
		CoffretSejour c = new CoffretSejour();
		c.ajoute(new EtapeSejour());
		c.ajoute(new EtapeGastronomique());
		
		CoffretBienEtre cb = new CoffretBienEtre();
	}
}
