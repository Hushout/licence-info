import javax.swing.*;
import java.awt.*;

public class Window1 extends JFrame {

	public Window1(){
		super();
		setTitle("essai1");
		setSize(400, 250);
		setLocation(100, 100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		setLayout(new BorderLayout());

		JPanel p = new JPanel();
	//	p.setLayout(new Flow)

		JButton up = new JButton("haut");
		JButton down = new JButton("bas");
		add(up, "North");
		add(down, "South");

		JButton[] b =  new JButton[10];

		for (int i = 0; i < b.length; i++) {
			b[i] = new JButton("Button " + i);
			p.add(b[i]);
		}
		add(p, "Center");

		setVisible(true);
	}

}