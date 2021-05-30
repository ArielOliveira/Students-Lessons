package th.ac.assignment2021.codeprovided.gui;

import javax.swing.*;

public class AbstractHistogramPanel extends JPanel {

    @SuppressWarnings({"FieldCanBeLocal", "unused"})
    private final AbstractWineSampleBrowserPanel parentPanel;
    private final AbstractHistogram histogram;

    public AbstractHistogramPanel(AbstractWineSampleBrowserPanel parentPanel, AbstractHistogram histogram) {
        super();
        this.parentPanel = parentPanel;
        this.histogram = histogram;
    }

    /* NOTE: your HistogramPanel must override JPanel's `protected void paintComponent(Graphics g)`,
    in order to redraw your Histogram whenever it is updated.
    For example:

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Dimension d = getSize();
        Graphics2D g2 = (Graphics2D) g;

        Line2D l = new Line2D.Double(
            0,
            0,
            d.width,
            d.height
        );
        g2.draw(l);
    }

     */

    public AbstractHistogram getHistogram()
    {
        return histogram;
    }
}
