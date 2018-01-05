import java.util.*;
import java.awt.Color;

public class IteratorColor implements Iterator<Color> {
	private Color[] colors;
	private int i = 0;

	public IteratorColor(Color[] colors){
		this.colors = colors;
	}

	public boolean hasNext(){
		return true;
	}

	public Color next(){
		if(i == 2)
			i = 0;
		else
			i++;
		return colors[i];
	}

	public void remove() throws UnsupportedOperationException {
		throw new UnsupportedOperationException();
	}
}