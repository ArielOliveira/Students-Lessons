package th.ac.assignment2021.codeprovided.gui;

import javax.swing.*;
import java.awt.*;

public class WineSampleBrowser extends JFrame {

	public WineSampleBrowser(AbstractWineSampleBrowserPanel panel) {
		setTitle("Portuguese Wine Sample Browser");
		add(panel);
		// maximises the JFrame
		setExtendedState(MAXIMIZED_BOTH);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
}
