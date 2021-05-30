package th.ac.assignment2021.codeprovided;

public enum WineType {
    ALL("all"),
    RED("red"),
    WHITE("white");

    private final String wineTypeName;

    WineType(String wTName) { wineTypeName = wTName; }

    public String getName()
    {
        return wineTypeName;
    }
}