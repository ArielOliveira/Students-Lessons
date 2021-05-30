package projects.project8;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

import projects.project8.bst.LinkedBSTOrderedSet;
import projects.project8.bst.LinkedBinarySearchTree;
import projects.project8.exceptions.ElementNotFoundException;
import projects.project8.csc205.Sorting; 

public class Project8TestDriver {

	public static void main(String[] args) {
		LinkedBinarySearchTree<Integer> t = new LinkedBinarySearchTree<Integer>();
		LinkedBSTOrderedSet<Integer> o = new LinkedBSTOrderedSet<Integer>();
		
		// Set up test data
		for(int ii=0;ii<30;ii++) {
			Integer num = (int)(Math.random()*10);
			t.addElement(num);    // BinarySearchTree
			o.addElement(num);    // LinkedBSTOrderedSet
		}
		
		System.out.println("Binary Search Tree (" + t.size() + "): " + t);
		System.out.println("\nFind:");

		for (int jj=0;jj<4;jj++) 
			try { 
				Integer res = t.find(jj*4 + 1);
				System.out.println("  Found " + (jj*4+1) + ": " + res);
			}
			catch (ElementNotFoundException e) {
				System.out.println("  Did not find " + (jj*4+1));
			}
		
		System.out.println("BST min: " + t.findMin());
		System.out.println("BST max: " + t.findMax());
		System.out.println("BST remove min: " + t.removeMin());
		System.out.println("BST remove max: " + t.removeMax());
		t.removeMin();
		t.removeMax();
		t.removeMax();
		t.removeMin();
		t.removeMax();
		t.removeMin();
		System.out.println("Binary Search Tree (" + t.size() + "): " + t);
		
		System.out.print("\nIn-Order: ");
		Iterator<Integer> inorder = t.iteratorInOrder();
		while (inorder.hasNext()) {
			System.out.print(inorder.next() + " ");
		}		
		
		System.out.print("\nPost-Order: ");
		Iterator<Integer> postorder = t.iteratorPostOrder();
		while (postorder.hasNext()) {
			System.out.print(postorder.next() + " ");
		}

		System.out.println("\n\nOrdered Set: " + o);

		System.out.println("\nbstSort Testing:");
		ArrayList<Integer[]> testArray = new ArrayList<Integer[]>();
		Integer[] a1 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		Integer[] a2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		Integer[] a3 = generateRandomArray(10);
		testArray.add(a1);
		testArray.add(a2);
		testArray.add(a3);
		
		int count = 0;
		for (Integer[] ta : testArray) {
			count ++;
			Sorting.bstSort(ta);
			if (Sorting.isSorted(ta)) {
				System.out.print("Array" + count + ": ");
				printArray(ta);
			}
			else {
				System.out.println("SORTING FAILED FOR ARRAY " + count);
			}
		}

		System.out.println("\nprintTree Testing: ");
		System.out.println(t.printTree());
		LinkedBinarySearchTree<Integer> bst = new LinkedBinarySearchTree<Integer>();
		bst.addElement(5);
		bst.addElement(3);
		bst.addElement(2);
		bst.addElement(4);
		bst.addElement(7);
		System.out.println(bst.printTree());
		System.out.println("DONE");
	}

	// Helper methods
	public static Integer[] generateRandomArray(int len) {
		Integer[] a = new Integer[len];
		Random rand = new Random();

	    for (int ii=0;ii<a.length;ii++) {
	    	a[ii] = rand.nextInt(1000);
	    }			
	    return a;
	}
	
	public static void printArray(Object[] a) {
		for (int ii=0;ii<a.length;ii++) {
			System.out.print (a[ii] + " ");
		}
		System.out.println();
	}

}
