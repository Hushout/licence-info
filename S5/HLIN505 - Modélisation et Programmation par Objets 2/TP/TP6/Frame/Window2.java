import javax.swing.*;
import java.awt.*;

public class Window2 extends JFrame{


	public Window2(){
		super();
		setTitle("essai2");
		//setSize(400, 250);
		setLocation(500, 100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		setLayout(new BorderLayout());

		JPanel pUp = new JPanel();
		pUp.add(new Button("haut"));

		JPanel pDown = new JPanel();
		pDown.add(new Button("Bas"));

		JPanel pCenter = new JPanel();
		pCenter.setLayout(new BorderLayout());
		pCenter.add(new Button("Button 0"), "North");
		pCenter.add(new Button("Button 4"), "South");

		JPanel pMiddle = new JPanel();
		pMiddle.add(new Button("Button 1"));
		pMiddle.add(new Button("Button 2"));
		pMiddle.add(new Button("Button 3"));

		pCenter.add(pMiddle);

		add(pUp, "North");
		add(pDown, "South");
		add(pCenter);

		pack();

		setVisible(true);
	}

}