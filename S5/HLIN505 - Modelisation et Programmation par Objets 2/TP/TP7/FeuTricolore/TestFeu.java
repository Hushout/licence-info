import java.util.*;
import java.awt.Color;
public class TestFeu {
	public static void main(String[] args) {
		FeuTricolore f = new FeuTricolore();
		Iterator<Color> it = f.iterator();

		for (int i = 0 ; i < 3 ; i++) {
			System.out.println(it.next());
		}
	}
}