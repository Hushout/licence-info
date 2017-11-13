import javax.swing.*;
import java.awt.*;

public class Window3 extends JFrame {
	public Window3(){
		super();
		setTitle("essai3");
		setLocation(900, 100);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JComboBox<String> cb = new JComboBox<>();
		ButtonGroup bg = new ButtonGroup();
		JRadioButton rbr = new JRadioButton("Rouge");
		JRadioButton rbv = new JRadioButton("Vert");
		JRadioButton rbb = new JRadioButton("Bleu");
		bg.add(rbr);
		bg.add(rbv);
		bg.add(rbb);

		cb.addItem("Rouge");
		cb.addItem("Vert");
		cb.addItem("Bleu");

		JPanel pUp = new JPanel();
		pUp.setBackground(Color.green);
		pUp.add(new JLabel("Couleur de texte:"));
		pUp.add(cb);

		JPanel pCenter = new JPanel();
		pCenter.setBackground(Color.yellow);
		pCenter.add(new JLabel("Couleur de fond:"));
		pCenter.add(rbr);
		pCenter.add(rbv);
		pCenter.add(rbb);

		JPanel pDown = new JPanel();
		pDown.setBackground(Color.blue);
		pDown.add(new JLabel("Style:"));
		pDown.add(new JCheckBox("Italique"));
		pDown.add(new JCheckBox("Gras"));

		add(pUp, "North");
		add(pCenter);
		add(pDown, "South");

		pack();

		setVisible(true);
	}
}