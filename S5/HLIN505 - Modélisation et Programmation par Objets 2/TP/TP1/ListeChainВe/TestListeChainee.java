import java.io.*;

public class TestListeChainee {

    public static void main(String[] args){

	ListeChainee list = new ListeChainee();

	list.addTete(5);
	list.addTete(4);
	list.addTete(3);
	list.addTete(2);
	list.addTete(1);

	System.out.println(list);
	System.out.println(list.reverse());
	System.out.println("Taille de la liste: " + list.getLength());
    }
}
