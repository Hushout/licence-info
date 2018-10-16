package coffretscadeaux;

public interface Iprestation {
	//Lieu getLieu(); void setLieu(Lieu l);
	double getPrix(); 
	double getDuree(); void setDuree(double duree) throws DureeTropCourteException;
	//int getNombrePersonnes(); void setNombrePersonnes(int nb);
	String getDescriptif(); void setDescriptif(String d);
}
