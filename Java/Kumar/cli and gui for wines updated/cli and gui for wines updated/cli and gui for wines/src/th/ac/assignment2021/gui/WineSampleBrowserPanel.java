package th.ac.assignment2021.gui;

import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import javax.swing.JComboBox;
import javax.swing.SwingConstants;

import th.ac.assignment2021.codeprovided.AbstractQueryParser;
import th.ac.assignment2021.codeprovided.Query;
import th.ac.assignment2021.codeprovided.SubQuery;
import th.ac.assignment2021.codeprovided.WineProperty;
import th.ac.assignment2021.codeprovided.WineSample;
import th.ac.assignment2021.codeprovided.WineType;
import th.ac.assignment2021.QueryParser;
import th.ac.assignment2021.codeprovided.AbstractWineSampleCellar;
import th.ac.assignment2021.codeprovided.gui.AbstractWineSampleBrowserPanel;

public class WineSampleBrowserPanel extends AbstractWineSampleBrowserPanel {
	//Map<WineType, List<WineSample>> filteredSample;
	//List<Query> queries;
	
    public WineSampleBrowserPanel(AbstractWineSampleCellar cellar) {
        super(cellar);
        
       // queries = new ArrayList<Query>();
        //filteredSample = new HashMap<WineType, List<WineSample>>();
        
        filteredWineSamplesTextArea.setEditable(false);
    	statisticsTextArea.setEditable(false);
    	subQueriesTextArea.setEditable(false);
    	
    	/*Font  f1  = new Font(Font.MONOSPACED, Font.PLAIN,  14);
    	
    	filteredWineSamplesTextArea.setFont(f1);
    	statisticsTextArea.setFont(f1);
    	subQueriesTextArea.setFont(f1);*/
    	
    	updateStatistics();
    	updateWineDetailsBox();
    	updateHistogram();
    }
    
    public enum Action {
    	NewQuery,
    	NewSubQuery,
    	QueryExists
    } 
    

    @Override
    public void addListeners() {
        // TODO implement
    	
    	buttonAddFilter.addActionListener(new ActionListener(){
    	   public void actionPerformed(ActionEvent e) {
    		   if (fieldsSet()) {
    			   	QueryParser.isGUI = true;
    	       		addFilter();
    	       		QueryParser.isGUI = false;
    		   }
    	    }
    	});
    	
    	buttonClearFilters.addActionListener(new ActionListener(){
     	   public void actionPerformed(ActionEvent e) {
     	       clearFilters();
     	    }
     	});
    	
    	comboHistogramProperties.addActionListener(new ActionListener() {
    		public void actionPerformed(ActionEvent e) {
    			System.out.println("actionPerformed");
    			updateHistogram();
    		}
    	});
    }

    @Override
    public void addFilter() {
        // TODO implement
    	
    	// List of string that will hold the components for the subquery
    	// TODO check if this filter doesn't already exist
    	// TODO add "and" to separate the subqueries accordingly
    	wineType = WineType.valueOf((String) comboWineTypes.getSelectedItem());
    	WineProperty property = WineProperty.fromName((String) comboQueryProperties.getSelectedItem());
    	
    	String operator = (String) comboOperators.getSelectedItem();
    	Double valueN = Double.parseDouble(value.getText());
    	
    	
    	SubQuery subQuery = new SubQuery(property, operator, valueN);
    	
    	//if (addAction(subQuery) == true) {
    	if (addAction(subQuery)) {
    		subQueryList.add(subQuery);
    	}
    		
    	printQueries();
    	
    	executeQuery();
    	
    	updateStatistics();
    	updateWineDetailsBox();
    	updateHistogram();
    }

    @Override
    public void clearFilters() {
        // TODO implement
    	filteredWineSamplesTextArea.setText("");
    	statisticsTextArea.setText("");
    	subQueriesTextArea.setText("");
    	value.setText("");
    	
    	comboWineTypes.setSelectedIndex(0);
    	
    	subQueryList.clear();
    	
    	wineType = WineType.ALL;
    	filteredWineSampleList = cellar.getWineSampleList(wineType);
    	
    	updateStatistics();
    	updateWineDetailsBox();
    	updateHistogram();
    	
    }

    @Override
    public void updateStatistics() {
        // TODO implement
    	String rows = "\t";
    	for (WineProperty property : WineProperty.values())
    		rows += property.getName() + "\t";
    	    	
    	rows += "\n" + "\n";
    	rows += "Minimum:\t";
    	
    	for (WineProperty property : WineProperty.values())
    		rows += Math.floor(cellar.getMinimumValue(property, filteredWineSampleList) * 1000) / 1000.0 + "\t";
    	
    	rows += "\n";
    	rows += "Maximum:\t";
    	
    	for (WineProperty property : WineProperty.values())
    		rows += Math.floor(cellar.getMaximumValue(property, filteredWineSampleList) * 1000) / 1000.0 + "\t";
    	
    	rows += "\n";
    	rows += "Mean:\t";
    	
    	for (WineProperty property : WineProperty.values())
    		rows += Math.floor(cellar.getMeanAverageValue(property, filteredWineSampleList) * 1000) / 1000.0 + "\t";
    	
    	rows += "\n" + "\n";
    	rows += "Showing " + filteredWineSampleList.size() + " of " + cellar.getNumberWineSamples(WineType.ALL) + " samples.";
    	
    	statisticsTextArea.setText(rows);
    }

    @Override
    public void updateWineDetailsBox() {
        // TODO implement
    	String detailsBoxString = "WineType\t\tID\t\t";
    	for (WineProperty property : WineProperty.values())
    		detailsBoxString += property.getName() + "\t\t";
    	
    	detailsBoxString += "\n" + "\n";
    	for (WineSample sample : filteredWineSampleList) {
    		detailsBoxString += sample.getWineType().name() + "\t\t";
			detailsBoxString += sample.getId() + "\t\t";
    		for (WineProperty property : WineProperty.values()) {
    			detailsBoxString += Math.floor(sample.getProperty(property) * 1000) / 1000.0 + "\t\t";
    		}
    		detailsBoxString += "\n";
    	}
    		
    	filteredWineSamplesTextArea.setText(detailsBoxString);
    }

    @Override
    public void executeQuery() {
        // TODO implement
    	Query query = new Query(subQueryList, wineType);
    	
    	filteredWineSampleList = query.executeQuery(cellar);
    	
    	System.out.println(filteredWineSampleList.size());
    }
    
    public boolean fieldsSet() {
    	return !value.getText().isEmpty();
    }
    
    public void printQueries() {
    	String queriesString = "";
    	
    	for (SubQuery s : subQueryList)
    		queriesString += (s.toString()) + "; ";
    	
    	subQueriesTextArea.setText(queriesString);
    }
    
    public boolean addAction(SubQuery subQuery) {
    	if (subQueryList.isEmpty())
    		return true;
    	  
    	subQuery.toString();

    	boolean contains = false;  		
    	for (SubQuery s : subQueryList) {
    		s.toString();
    		if (s.equals(subQuery)) {
    			contains = true;
    			break;
    			}		
    		}
    		if (!contains)
    			return true;
    	
    	return false;
    }
}
