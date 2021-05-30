package th.ac.assignment2021;

import th.ac.assignment2021.codeprovided.AbstractQueryParser;
import th.ac.assignment2021.codeprovided.Query;
import th.ac.assignment2021.codeprovided.SubQuery;
import th.ac.assignment2021.codeprovided.WineProperty;
import th.ac.assignment2021.codeprovided.WineType;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;


public class QueryParser extends AbstractQueryParser {
	public static boolean isGUI = false; 
	
    @Override
    public List<Query> readQueries(List<String> queryTokens) throws IllegalArgumentException {
        // TODO implement
    	//Should any common variables be initialised betweeen the class and this method? or between the QueryHandler class and the first method in there?
    	
    	List<Query> allQueries = new ArrayList<Query>();
    	ListIterator<String> it = queryTokens.listIterator();
    	
    	WineType wineType = null;
    	
    	while (it.hasNext()) {
    		String token = it.next();
    		
    		if (token.equals("select")) {    			
    			wineType = getWineType(it);
    			
    			if (wineType == null) {
    				throw new IllegalArgumentException("Illegal wine type");
    			}
    		}
    		
    		if (token.equals("where")) {
    			List<SubQuery> queries = getSubQueries(it);
    			
    			if (!queries.isEmpty())
    				allQueries.add(new Query(queries, wineType));
    			else
    				throw new IllegalArgumentException("Invalid subquery");
    		}
    	}
    	
        return allQueries;       
    }
    
    public static WineType getWineType(ListIterator<String> it) {
    	String wineTypeString = "";
    	
    	boolean stop = false;
    	while(it.hasNext() && !stop) {
    		String token = it.next();
    		
    		token = token.toLowerCase();
    		switch(token) {
    			case "red":
    				wineTypeString += token;
    				break;
    			case "white": 
    				wineTypeString += token;
    				break;
    			case "or": 
    				wineTypeString += token;
    				break;
    			case "all":
    				wineTypeString += token;
    				break;
    			default:
    				stop = true;
    				break;	
    		}
    	}
    	
    	it.previous();
    	
    	return getWineTypeFromString(wineTypeString);
    }
    
    
    public static WineType getWineTypeFromString(String wineTypeString) {
    	switch(wineTypeString) {
		case "red":
			return WineType.RED;
		case "white": 
			return WineType.WHITE;
		case  "redorwhite", "whiteorred", "all": 
			return WineType.ALL;
		default:
			return null;
    	}
    }
    
    public static List<SubQuery> getSubQueries(ListIterator<String> it) {
    	List<SubQuery> subQueries = new ArrayList<SubQuery>();
    	
    	WineProperty property = null;
    	String operator = "";
    	Double value = null;
    	
    	String token = "";
    	while(it.hasNext() && !token.equals("select")) {
    		token = it.next();
    		WineProperty dummy = null;
    		
    		try {
    			if (!isGUI)
    				dummy = WineProperty.fromFileIdentifier(token);
    			else 
    				dummy = WineProperty.fromName(token);
    		} catch (Exception e) {	
    			if (SubQuery.isValidOperator(token)) 
    					operator = token;
    			else if (!token.equals("and") && !token.equals("select"))  
    					value = Double.parseDouble(token);
    		} finally {
    			if (dummy != null) 
    				property = dummy;
    			
    			if (property != null && SubQuery.isValidOperator(operator) && value != null) {
        			subQueries.add(new SubQuery(property, operator, value));
        			
        			property = null;
        			value = null;
        			operator = "";
        		}
    		}   		
    	}
    	
    	it.previous();
    	
    	return subQueries;
    }
     
    
}
