import java.io.*;

public class ErrNat extends Exception {

	private int errorNum;

	public ErrNat(){super();}
	
	public ErrNat(int n){
		super();
		errorNum = n;
	}

	public int getErrorNumber(){
		return errorNum;
	}
}