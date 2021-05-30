package project3HeapStructure;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import project3HeapStructure.heap;

//Class that represents a Database
public class DatabaseAccess<T> {

	//Fields of the class
	private heap<T> database;
	private final String filename = "database.txt";
	private ArrayList<T> list;

	//Constructor of the class
	public DatabaseAccess() {
		//Initializes an empty tree
		database = new heap<T>();
		list = new ArrayList<T>();
	}

	//Helper method that loads the database from the file
	@SuppressWarnings("unchecked")
	public void loadDatabaseFromFile() {
		//to load, we read the serialized file
		try (FileInputStream fis = new FileInputStream(filename);
			// creates a FileInputStream, then an ObjectInputStream reads the whole database from it
			ObjectInputStream ois = new ObjectInputStream(fis)) {
			database = (heap<T>)ois.readObject();
			
		} catch (Exception e) {
			//Print a message if any errors when loading
			System.out.println("Unable to read file correctly. Database cannot be loaded");
		} 
	}

	//Helper method that saves the database to the file
	public void saveDatabaseToFile() {
		// creates a file with the serialized database
		try (FileOutputStream fos = new FileOutputStream(filename); 
			// creates a FileOutputStream, then an ObjectOutputStream from it and saves the whole database to it

			ObjectOutputStream oos = new ObjectOutputStream(fos)) {
			oos.writeObject(database);
			
		} catch (Exception e) {
			//Print a message if any errors when saving
			System.out.println("Unable to save to file correctly.");
		}
	}
	
	//Method that adds a new entry into the database
	public void addEntry(T object) {
		database.insert(list, object);
	}

	public void sortHeap() {
		database.sort(list);
	}
	
	//Method that removes a given entry from the database
	public void removeMax() {
		if(database.DeleteMax(list) == true) {
			System.out.println("Data removed.");
		} else {
			System.out.println("Heap is empty");
		}
	}	
	
	public void printDB(){
		System.out.print(database.printArray(list));
	}
}