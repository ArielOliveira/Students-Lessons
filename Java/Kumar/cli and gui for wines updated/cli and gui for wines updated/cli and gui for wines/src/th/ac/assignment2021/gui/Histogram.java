package th.ac.assignment2021.gui;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.NoSuchElementException;

import th.ac.assignment2021.codeprovided.AbstractWineSampleCellar;
import th.ac.assignment2021.codeprovided.WineProperty;
import th.ac.assignment2021.codeprovided.WineSample;
import th.ac.assignment2021.codeprovided.gui.AbstractHistogram;
import th.ac.assignment2021.codeprovided.gui.HistogramBin;

public class Histogram extends AbstractHistogram {
    /**
     * Constructor. Called by AbstractWineSampleBrowserPanel
     *
     * @param cellar              to allow for getting min / max / avg values
     * @param filteredWineSamples a List of WineSamples to generate a histogram for.
     *                            These have already been filtered by the GUI's queries.
     * @param property            the WineProperty to generate a histogram for.
     */
	
	
    public Histogram(AbstractWineSampleCellar cellar, List<WineSample> filteredWineSamples, WineProperty property)
    {
        super(cellar, filteredWineSamples, property);
    }

    @Override
    public void updateHistogramContents(WineProperty property, List<WineSample> filteredWineSamples) {
        // TODO implement
    	wineCountsPerBin.clear();
    	
    	if (filteredWineSamples == null) {
    		return;
    	}
    	
    	if (filteredWineSamples.isEmpty()) {
    		return;
    	}
    	
    	this.property = property;
    	this.filteredWineSamples = filteredWineSamples;
    	
    	this.minPropertyValue = cellar.getMinimumValue(property, filteredWineSamples);
    	this.maxPropertyValue = cellar.getMaximumValue(property, filteredWineSamples);
    	
    	Double distribution = (this.maxPropertyValue / NUMBER_BINS);
    	
    	// Create a copy of filteredWineSamples
    	List<Double> sortedProperties = new ArrayList<Double>();
    	for (WineSample sample : filteredWineSamples) 
    		sortedProperties.add(sample.getProperty(property));
    	
    	Collections.sort(sortedProperties);
    	
    	Map<Integer, List<Double>> mappedBins = new HashMap<>();
    	
    	for (int i = 0; i < NUMBER_BINS; i++) {
    		mappedBins.put(i, new ArrayList<Double>());
    		for (Double value: sortedProperties) {
    			if (value <= distribution * (double) (i+1)) {
    				mappedBins.get(i).add(value);
    			} else {
    				break;
    			}
    		}
    		for (Double value : mappedBins.get(i))
    			sortedProperties.remove(value);
    	}
    	
    	for (Map.Entry<Integer, List<Double>> entry : mappedBins.entrySet()) {
    		if (!entry.getValue().isEmpty()) {
    			List<Double> values = entry.getValue();
    			System.out.println(entry.getKey() + " " + !mappedBins.containsKey(entry.getKey()+1) + " " + values.size());
    			wineCountsPerBin.put(new HistogramBin(values.get(0), values.get(values.size()-1), !mappedBins.containsKey(entry.getKey()+1)), values.size());
    		} else {
    			//System.out.println(entry.getKey() + " " + NUMBER_BINS + " " + (entry.getKey() >= NUMBER_BINS-1));
    			//wineCountsPerBin.put(new HistogramBin(0, 0, entry.getKey() >= NUMBER_BINS-1), 0);
    		}
    	}
    }

    @Override
    public double getAveragePropertyValue() throws NoSuchElementException {
    	Double average = 0.0;
    	try {
    		average = cellar.getMeanAverageValue(property, filteredWineSamples);
    	} catch(NoSuchElementException e) {
    		// TODO: Deal with it
    		System.err.println(e);
    	}
    	return average;
    }
}
