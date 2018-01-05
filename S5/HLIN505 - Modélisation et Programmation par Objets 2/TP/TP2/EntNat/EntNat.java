public class EntNat {
	private int m_entier;

	public EntNat(int n) throws ErrNat {
	    if(n < 0) throw new ErrConst(n);
	    m_entier = n;
	}

	public int getN() {
	    return m_entier;
	}

	public void decremente() throws ErrNat {
		m_entier--;
		if(m_entier < 0) throw new ErrModif(m_entier);
	}

	public static void decremente(EntNat e) throws ErrNat {
		e.decremente();
	}

	public void setN(int n) throws ErrNat{
		if(n < 0) throw new ErrModif(n);
	    this.m_entier = n;
	}

	public static void main(String[] args) throws ErrNat{
		try{
			EntNat n = new EntNat(-1);
			n.decremente();
		}
		catch(ErrConst e){System.out.println("ErrConst: " + e.getErrorNumber());}
		catch(ErrModif e){System.out.println("ErrModif: " + e.getErrorNumber());}

		System.out.println("Sortie du main");
	}
}