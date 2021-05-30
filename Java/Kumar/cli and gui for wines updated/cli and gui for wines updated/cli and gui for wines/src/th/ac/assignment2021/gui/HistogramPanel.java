package th.ac.assignment2021.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import th.ac.assignment2021.codeprovided.gui.AbstractHistogram;
import th.ac.assignment2021.codeprovided.gui.AbstractHistogramPanel;
import th.ac.assignment2021.codeprovided.gui.AbstractWineSampleBrowserPanel;
import th.ac.assignment2021.codeprovided.gui.HistogramBin;

public class HistogramPanel extends AbstractHistogramPanel
{
	private int rectangleWidth;
	private double rectangleHeight;
	
    public HistogramPanel(AbstractWineSampleBrowserPanel parentPanel, AbstractHistogram histogram)
    {
        super(parentPanel, histogram);
    }


    // NOTE: your HistogramPanel must override JPanel's `protected void paintComponent(Graphics g)`,
    // in order to redraw your Histogram whenever it is updated.
    // For example: 

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Dimension d = getSize();
        
        List<HistogramBin> mappedBins = (getHistogram().getBinsInBoundaryOrder());
        
        rectangleWidth = d.width / 11;
         
        Graphics2D g2 = (Graphics2D) g;
        g2.setPaint(new Color(255, 120, 0));
        
        List<Rectangle2D> rects = new ArrayList<Rectangle2D>();
        
        double scaleFactor = (double)d.height / (double)getHistogram().largestBinCount();
        int totalWines = 0;
        int count = 0;
        for (HistogramBin bin : mappedBins) {
        	totalWines += getHistogram().getNumWinesInBin(bin);
        	rectangleHeight = (double)getHistogram().getNumWinesInBin(bin) * scaleFactor;
        	Rectangle2D rect = new Rectangle2D.Double(((rectangleWidth) * count), 0, rectangleWidth, (int)-rectangleHeight - 15);
        	rects.add(rect);
        	
        	g2.fillRect((int)((rectangleWidth) * count), d.height-10, (rectangleWidth), (int)-rectangleHeight - 15);
        	count++;
        }
        
        g2.setPaint(new Color(0, 0, 0));
        for (int i = 0; i < 11; i++) {
        	g2.drawString(Integer.toString(i+1), i * rectangleWidth + (rectangleWidth/2), d.height);
        }
        
        int splittedMax = getHistogram().largestBinCount() / 4;
        for (int i = 0; i <= 4; i++) {
        	g2.drawString(Integer.toString(i * splittedMax), 0f, d.height - (float)((i * splittedMax) * (scaleFactor * 0.93f)));
        }
        
        double average = (double)(totalWines / 11);
        double XscaleFactor = (double)(d.width / (double)getHistogram().largestBinCount());
        
        System.out.println(average + " " + XscaleFactor);
        g2.setPaint(new Color(255, 0, 0));
        g2.drawLine((int)(average * XscaleFactor), 0, (int)(average * XscaleFactor), d.height);
        
        for (Rectangle2D rectangle : rects)
        	g2.draw(rectangle);
    }
    
    @Override
    public void repaint() {
    	super.repaint();
    }
    
    //public void update(Map<Integer, List<Double>> mappedBins, ) {
    	
    //}
}
