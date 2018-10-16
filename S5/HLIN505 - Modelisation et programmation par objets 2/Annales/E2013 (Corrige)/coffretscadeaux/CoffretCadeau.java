package coffretscadeaux;

import java.util.ArrayList;

public class CoffretCadeau<T extends Iprestation> {

	private ArrayList<T> listePrestations = new ArrayList<T>();
	public void ajoute(T p)
	{
		if (! this.listePrestations.contains(p))
			this.listePrestations.add(p);
	}
	public double getPrix()
	{
		double prix = 0;
		for (T t : this.listePrestations)
			prix += t.getPrix();
		return prix;
	}
}
