import java.util.*;

public class FeuilleSalaire implements Iterable<Object> {
	
	private String employeur;
	private String salarie;
	private String conventionCollective;
	private int nbHeuresPayees;
	private int prelevFisc;
	private int netAPayer;

	public FeuilleSalaire() {

	}

	public IteratorFeuilleSalaire iterator(){
		return new IteratorFeuilleSalaire();
	}
}