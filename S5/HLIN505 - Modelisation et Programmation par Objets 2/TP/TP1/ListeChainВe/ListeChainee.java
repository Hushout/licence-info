public class ListeChainee {

	private Node racine;
	
	public class Node {

		private int valeur;
		private Node next;

		public Node(){
			this.valeur = 0;
			this.next = null;
		}

		public Node(int v){
			this.valeur = v;
			this.next = null;
		}

		public Node(int v, Node next){
			this.valeur = v;
			this.next = next;
		}

		public int nbFils(){
			if(this.next == null){
				return 1;
			}
			else {
				return 1 + next.nbFils();
			}
		}

		public String toString(){
			if(this.next == null){
				return "" + this.valeur;
			}
			else{
				return this.valeur + ", " + next.toString();
			}
		}
	}
	
	public ListeChainee(){
		racine = null;
	}

	public void addTete(int v){
		Node next = this.racine;
		racine = new Node(v, next);
	}


	public int getLength(){
		if(racine == null){
			return 0;
		}
		else{
			return racine.nbFils();
		}
	}

	public String toString(){
		return "{" + this.racine.toString() + "}";
	}

	public ListeChainee reverse(){
		ListeChainee reversed = new ListeChainee();
		Node n = racine;
		while(n != null){
			reversed.addTete(n.valeur);
			n = n.next;
		}
		return reversed;
	}
}
