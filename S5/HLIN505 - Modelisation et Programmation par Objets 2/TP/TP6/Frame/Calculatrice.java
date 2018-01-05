import javax.swing.*;
import java.awt.*;

public class Calculatrice extends JFrame {

	public Calculatrice(){
		super();
		setTitle("Calculatrice");
		setLocation(500, 400);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


		JButton[] b =  new JButton[16];
		b[0] = new JButton("7");
		b[1] = new JButton("8");
		b[2] = new JButton("9");
		b[3] = new JButton("/");
		b[4] = new JButton("4");
		b[5] = new JButton("5");
		b[6] = new JButton("6");
		b[7] = new JButton("*");
		b[8] = new JButton("1");
		b[9] = new JButton("2");
		b[10] = new JButton("3");
		b[11] = new JButton("-");
		b[12] = new JButton("0");
		b[13] = new JButton(".");
		b[14] = new JButton("=");
		b[15] = new JButton("+");

		add(new JTextField(), "North");

		JPanel pCenter = new JPanel();
		pCenter.setLayout(new GridLayout(4, 4));


		for (int i = 0; i < b.length; i++) {
			pCenter.add(b[i]);
		}

		add(pCenter);

		pack();

		setVisible(true);
	}
}