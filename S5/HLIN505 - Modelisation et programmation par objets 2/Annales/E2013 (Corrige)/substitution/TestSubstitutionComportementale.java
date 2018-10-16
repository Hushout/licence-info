package substitution;

import java.lang.reflect.*;

public class TestSubstitutionComportementale {
	public static void afficheMethodesNeRespectantPasLaSubstitutionComportementale(String nomClasse) throws SecurityException, ClassNotFoundException
	{
		System.out.println("méthodes ne respectant pas la substitution comportementale :");
		for (Method m :  Class.forName(nomClasse).getMethods()) 
			{
				if (m.isAnnotationPresent(substitutionComportementale.class) &&              
					(! m.getAnnotation(substitutionComportementale.class).isRespected()))
					System.out.println(m.getName());
			}
	}
	
	public static void afficheMethodesRespectantLaSubstitutionComportementale(String nomClasse) throws SecurityException, ClassNotFoundException
	{
		System.out.println("méthodes respectant la substitution comportementale :");
		for (Method m :  Class.forName(nomClasse).getMethods()) 
			{
				if (m.isAnnotationPresent(substitutionComportementale.class) &&              
					(m.getAnnotation(substitutionComportementale.class).isRespected()))
					System.out.println(m.getName());
			}
	}
	
	public static void main(String[] argv) throws SecurityException, ClassNotFoundException
	{
		
		TestSubstitutionComportementale.afficheMethodesNeRespectantPasLaSubstitutionComportementale
		       ("coffretscadeaux.EtapeGastronomique");
		TestSubstitutionComportementale.afficheMethodesRespectantLaSubstitutionComportementale
	       ("coffretscadeaux.EtapeGastronomique");
	}
}
