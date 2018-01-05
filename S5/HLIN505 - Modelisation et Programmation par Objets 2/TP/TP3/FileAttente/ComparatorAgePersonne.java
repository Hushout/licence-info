import java.util.*;

public class ComparatorAgePersonne implements Comparator<Personne> {

    public int compare(Personne p1, Personne p2){
	if(p1.getAge() == p2.getAge())
	    return 0;
	else if(p1.getAge() < p2.getAge())
	    return -1;
	else
	    return 1;
    }

}
