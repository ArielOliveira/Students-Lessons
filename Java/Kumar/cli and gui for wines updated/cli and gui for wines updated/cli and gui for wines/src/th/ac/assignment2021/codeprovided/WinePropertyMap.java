package th.ac.assignment2021.codeprovided;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class WinePropertyMap {

    // Consult the Javadocs for Map & HashMap for more information
    private final Map<WineProperty, Double> propertyToValuesMap = new HashMap<>();

    /**
     * Add a WineProperty and value pair. See HashMap.put() for more technical details.
     * @param wineProperty the property to store
     * @param value the value associated with the property
     */
    public void put(WineProperty wineProperty, double value) {
        propertyToValuesMap.put(wineProperty, value);
    }

    /**
     * Retrieve a value associated with a given WineProperty. See HashMap.get() for more technical details.
     * @param wineProperty the WineProperty to retrieve the value of
     * @return the retrieved value
     */
    public double get(WineProperty wineProperty) {
        return propertyToValuesMap.get(wineProperty);
    }

    /**
     * Get the properties stored in the map. See HashMap.keySet() for more technical details.
     * @return the properties stored in the map
     */
    public Set<WineProperty> propertySet() {
        return propertyToValuesMap.keySet();
    }

}
