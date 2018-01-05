import java.util.*;
import java.awt.Color;

public class FeuTricolore implements Iterable<Color> {
	private Color[] colors = {Color.red, Color.orange, Color.green};

	public FeuTricolore(){}

	public IteratorColor iterator(){
		return new IteratorColor(colors);
	}
}