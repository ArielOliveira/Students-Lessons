package project3HeapStructure;

import java.util.Scanner;

import project3HeapStructure.DatabaseAccess;


public class Main {

	public static void main(String[] args) {
		
		
		 //@SuppressWarnings("resource")
		 //heap <String> heapS =new heap<String>();
		//@SuppressWarnings("resource")
		Scanner scanner = new Scanner(System.in);
		DatabaseAccess<String> db = new DatabaseAccess<String>();
	      
	        

	        while (true) {
	            System.out.println("Please enter an action you'd like to take:");
	            System.out.println("\t-1) quit program");
	            System.out.println("\t1) insert a new element into the heap structure");
	            System.out.println("\t2) delete the max heap and print");
	            System.out.println("\t3) heap sort and print");
	            System.out.println("\t4) Print the heap structure");
	           int userOption = scanner.nextInt();
	            scanner.nextLine();  

	            switch (userOption){
	                case -1:
	                    break;
	                case 1:
	                	//enter the object to insert 
	                    System.out.println("Please enter a object to insert into the heap structure");
	                    String object = scanner.next();
	                    db.addEntry(object);
	                    break;
	                case 2:
	                	//
	                	System.out.println("heap structure after max deletion ");
	                	db.removeMax();
	                case 3:
	                    System.out.println("heap sructure after heap sort");
	                    
	                 
	                    break;
	                case 4:
	                    //Print the heap structure 
	                	System.out.println("print the heap structure");
	                	db.printDB();
	                    break;
	             
	            }

	            if (userOption == -1){
	            	//end the program 
	            	System.out.println("the program has ended");
	                break;
	            }
	        }
	    }


	}


	


