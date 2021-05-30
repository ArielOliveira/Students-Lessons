package th.ac.assignment2021;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import java.util.NoSuchElementException;

import th.ac.assignment2021.codeprovided.*;

public class WineSampleCellar extends AbstractWineSampleCellar {
    /**
     * Constructor - reads wine sample datasets and list of queries from text file,
     * and initialises the wineSampleRacks Map
     *
     * @param redWineFilename
     * @param whiteWineFilename
     */
    public WineSampleCellar(String redWineFilename, String whiteWineFilename) {
        super(redWineFilename, whiteWineFilename);
    }
    
    // Delete this documentation later (was pasted from the abstract class)
    /**
     * Parse the properties from a given line from a wine file.
     * You can expect that each value appears in the same order as the columns in the file),
     * and that this order will not change.
     * Example line:
     * 7.9;0.6;0.06;1.6;0.069;15;59;0.9964;3.3;0.46;9.4;5
     *
     * @param line the line to parse
     * @return a WinePropertyMap constructed from the parsed row, containing values for every property
     * @throws IllegalArgumentException if the line is malformed (i.e. does not include every property
     * for a single wine, or contains undefined properties)
     */
    @Override
    public WinePropertyMap parseWineFileLine(String line) throws IllegalArgumentException {
        // TODO implement
    	
    	String[] parsedLine= line.split(";");
    	
    	//Checking if parsedLine length is equal to the number of wine properties
    	if (parsedLine.length != 12) {
    		throw new IllegalArgumentException("Number of properties doesn't match");
    	}
    	
    	WinePropertyMap wineMap = new WinePropertyMap();
    	
    	Double[] parsedLineIntoDoubles = new Double[WineProperty.values().length];
    	
    	WineProperty[] wproperty = WineProperty.values();
    	
    	
    	try {
    		for (int i=0; i<WineProperty.values().length; i++) {
        		parsedLineIntoDoubles[i] = Double.parseDouble(parsedLine[i]);
        	}
    	} catch (Exception e) {
    		throw new IllegalArgumentException("Value of properties is invalid");
    	}
    	
    	
    	// The 12 here refers to the total number of properties you can have (same as WineProperty.values().length)
    	for (int i=0; i<WineProperty.values().length; i++) {
    		wineMap.put(wproperty[i], parsedLineIntoDoubles[i]);
    	}   	    	
    	
        return wineMap;
    }

    @Override
    public void updateCellar() {
        // TODO delete next line and implement
    	
    	// Create an empty list
    	ArrayList<WineSample> allWineTypes = new ArrayList<>();
    	
    	// Adding all samples of white and red wine
    	allWineTypes.addAll(getWineSampleList(WineType.WHITE));
    	allWineTypes.addAll(getWineSampleList(WineType.RED));
    	
        wineSampleRacks.put(WineType.ALL, new ArrayList<>(allWineTypes));
    }

    @Override
    public double getMinimumValue(WineProperty wineProperty, List<WineSample> wineList)
            throws NoSuchElementException {
        // TODO implement
    	
    	// Check this later for better implementation?
    	try {
    		WineProperty.fromName(wineProperty.getName());
    	} catch (Exception e) {
    		throw new NoSuchElementException(e);
    	}
    	
    	double minValue = Double.POSITIVE_INFINITY;
    	
//    	List<Double> helperList = new ArrayList<>();
    	
    	for (int i=0; i<wineList.size(); i++) {
//    		helperList.add(wineList.get(i).getProperty(wineProperty));
    		if (minValue > wineList.get(i).getProperty(wineProperty)) {
    			minValue = wineList.get(i).getProperty(wineProperty);
    		}
    	}
    	
    	//String nameOfProperty = wineProperty.getName();
    	//List<WineSample> getMin = Collections.min();
    	//To prevent running through the list twice we are returning minValue
    	
    	//return Collections.max(helperList);
    	return minValue;
    }

    @Override
    public double getMaximumValue(WineProperty wineProperty, List<WineSample> wineList)
            throws NoSuchElementException {
        // TODO implement
    	
    	// Check this later for better implementation?
    	try {
    		WineProperty.fromName(wineProperty.getName());
    	} catch (Exception e) {
    		throw new NoSuchElementException(e);
    	}
    	
    	double maxValue = Double.NEGATIVE_INFINITY;
    	
    	List<Double> helperList = new ArrayList<>();
    	for (int i=0; i<wineList.size(); i++) {
//    		helperList.add(wineList.get(i).getProperty(wineProperty));
    		if (maxValue < wineList.get(i).getProperty(wineProperty)) {
    			maxValue = wineList.get(i).getProperty(wineProperty);
    		}
    	}
    	//String nameOfProperty = wineProperty.getName();
    	//List<WineSample> getMax = Collections.max();
        //return Collections.max(helperList);
    	
    	return maxValue;
    }

    @Override
    public double getMeanAverageValue(WineProperty wineProperty, List<WineSample> wineList)
            throws NoSuchElementException {
        // TODO implement
    	
    	try {
    		WineProperty.fromName(wineProperty.getName());
    	} catch (Exception e) {
    		throw new NoSuchElementException(e);
    	}
    	
    	List<Double> helperList = new ArrayList<>();
    	for (int i=0; i<wineList.size(); i++) {
    		helperList.add(wineList.get(i).getProperty(wineProperty));
    	}
    	
    	double totalSum = 0.0;
    	for (Double value : helperList) {
    		totalSum += value;
    	}
    	
        return (totalSum/helperList.size());
    }

    @Override
    public List<WineSample> getFirstFiveWines(WineType type) {
        // TODO implement
    	
    	ArrayList<WineSample> wineSample = new ArrayList<WineSample>();
    	
    	wineSample.addAll(getWineSampleList(type));
    	
    	ArrayList<WineSample> fiveWines = new ArrayList<WineSample>();
    	
    	for (int i=0; i<5; i++) {
    		fiveWines.add(i, wineSample.get(i));
    	}
    	
        return new ArrayList<>(fiveWines);
    }
}
