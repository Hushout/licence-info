package Poste;

import java.util.Date;

public class ProgrammePoste {

	public static void main(String[] argv)
	{
	ObjetPostal o1; // = new ObjetPostal ... ne serait pas possible car la classe est abstraite
	o1 = new Lettre("Montpellier","pole nord","8809",0.02,0.01,TauxRecom.faible,true);
	System.out.println(o1); //ou o1.affiche();

	Colis o2 = 
			new Colis("pole sud","Paris","75000",2,3,TauxRecom.fort,"photos d'iceberg",3);
	System.out.println(o2); //ou o2.affiche();

	Colis o3 = 
			new ColisExpress("pole sud","Paris","75000",2,3,TauxRecom.fort,"photos d'iceberg",3,
					new Date(), true);
	System.out.println(o3); //ou o3.affiche();
	
	o3 = 
			new ColisExpress("Argentine","Clermont","000",80,3,TauxRecom.fort,"maté",3,
					new Date(), true);
	System.out.println(o3); //ou o3.affiche();

	}
}
