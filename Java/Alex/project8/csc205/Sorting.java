// The methods in this package are adapted from the code provided with:
//   Java Foundations (2nd & 3rd ed) by  Lewis, DePasquale, & Chase
//   Algorithms (4th ed) by Sedgewick & Wayne

package projects.project8.csc205;

public class Sorting {

	// Helper methods
	// These operations will occur multiple times in our sorting methods,
	//   so we add methods for them here
	private static <T extends Comparable<T>> boolean less_than(T a, T b) {
		return (a.compareTo(b) < 0);
	}
	private static <T extends Comparable<T>> boolean less_than_equal(T a, T b) {
		return (a.compareTo(b) <= 0);
	}
	private static <T extends Comparable<T>> boolean greater_than(T a, T b) {
		return (a.compareTo(b) > 0);
	}
	private static void swap(Object[] a, int ii, int jj) {
		Object swap = a[ii];
		a[ii] = a[jj];
		a[jj] = swap;
	}
	public static <T extends Comparable<T>> 
	boolean isSorted(T[]data){
		return isSorted(data, 0, data.length-1);
	}
	public static <T extends Comparable<T>> 
	boolean isSorted(T[]data, int min, int max){
		for (int ii=min+1; ii<=max; ii++) {
			if (less_than(data[ii], data[ii-1]))
				return false;
		}
		return true;
	}

	// Selection Sort
	public static <T extends Comparable<T>> 
	void selectionSort (T[] data) {
		selectionSort (data, 0, data.length-1);
	}

	public static <T extends Comparable<T>> 
	void selectionSort (T[] data, int min, int max) {
		int indexOfSmallest;		// Index of the smallest element this pass
		
		// Make sure min isn't too small and max isn't too big
		min = Math.max(min, 0);
		max = Math.min(max, data.length-1);
		
		// next is the starting point for each pass (where the next smallest
		//  element will go
		for(int next = min; next <= max; next ++) {
			indexOfSmallest = next;
			for(int scan=next+1; scan<=max; scan++) {
				if (less_than(data[scan], data[indexOfSmallest])) {
					indexOfSmallest = scan;
				}
			}
			swap(data, indexOfSmallest, next);
		}
	}
	
    public static <T extends Comparable<T>> 
	void insertionSort(T[] data) {
    	insertionSort(data, 0, data.length-1);
    }

    public static <T extends Comparable<T>> 
	void insertionSort(T[] data, int min, int max)
    {
    	int start = Math.max(min,  1);
    	int end = Math.min(max,  data.length-1);
    	
    	// Current is the length of the sorted sub-list at the start of the array
    	for (int current = start; current <= end; current++) {
    		int position = current;
    		
    		// shift larger values to the right
    		while (position > 0 && greater_than(data[position-1], data[position])) {
    			swap(data, position, position-1);
    			position--;
    		}
    	}
    }

    public static <T extends Comparable<T>> 
	void bubbleSort(T[] data) {
    	bubbleSort(data, 0, data.length-1);
    }
    public static <T extends Comparable<T>> 
	void bubbleSort(T[] data, int min, int max) {
    	int position, scan;
    	
    	int start = Math.max(min,  1);
    	int end = Math.min(max,  data.length-1);
    	
    	// position is the "stopping point" for each pass
    	for (position = end; position >= start; position--) {
    		for (scan = 0; scan < position; scan++) {
    			if(greater_than(data[scan], data[scan+1])) {
    				swap(data, scan, scan+1);
    			}
    		}
    	}
    }
    
	public static <T extends Comparable<T>>
	void mergeSort(T[] data) {
		mergeSort(data, 0, data.length-1);
	}

	private static <T extends Comparable<T>>
	void mergeSort(T[] data, int min, int max) {
		if (min < max)
		{
			int mid = min + ((max - min) / 2);
			mergeSort(data, min, mid);
			mergeSort(data, mid+1, max);
			merge(data, min, mid, max);
		}
	}
	
	private static <T extends Comparable<T>>
	void merge(T[] data, int min, int mid, int max) {
		T[] temp = (T[])(new Comparable[data.length]);  // temp array
		
		// The two subarrays have already been sorted 
		int first1 = min, last1 = mid;   // endpoints of the first subarray
		int first2 = mid+1, last2 = max;  // endpoints of the second subarray
		int index = first1;   // next index open in temp array
		
		// Copy the smaller item from each subarray until one of the subarrays is empty
		
		// While both subarrays have items left
		while ((first1 <= last1) && (first2 <= last2)) {
			if(less_than(data[first1], data[first2])) {
				// Move first1 to the temp array
				temp[index] = data[first1];
				first1++;
			}
			else {
				// Move first2 to the temp array
				temp[index] = data[first2];
				first2++;
			}
			index ++;  // Move the index of the next available cell in the temp array
		}
	
		// Only one of the while loops below will execute
		
		// Copy the remaining elements from the first subarray, if any
		while(first1 <= last1) {
			temp[index] = data[first1];
			first1++;
			index++;
		}
		
		// Copy the remaining elements from the second subarray, if any
		while(first2 <= last2) {
			temp[index] = data[first2];
			first2++;
			index++;
		}
		
		// Copy merged data into original array
		for(index=min; index<=max; index++) {
			data[index] = temp[index];
		}
	}

	public static <T extends Comparable<T>> 
	void quickSort(T[] data) {
		quickSort(data, 0, data.length-1);
	}

	private static <T extends Comparable<T>> 
	void quickSort(T[] data, int min, int max) {
		if (min < max)
		{
			// create partitions
			int indexofpartition = partition(data, min, max);
			
			// sort the left partition (lower values)
			quickSort(data, min, indexofpartition - 1);
			
			// sort the right partition (higher values)
			quickSort(data, indexofpartition + 1, max);
		}
	}

	private static <T extends Comparable<T>> 
	int partition(T[] data, int min, int max) {
		T partitionElement;
		int left, right;
		int middle = min + ((max - min) / 2);
		
		// use the middle data value as the partition element
		partitionElement = data[middle];
		// move the middle element out of the way for now
		swap(data, middle, min);
		
    	left = Math.max(min,  0);
    	right = Math.min(max,  data.length-1);
		while (left < right) {
			// search for an element that is > the partition element
			while ((left < right) && (less_than_equal(data[left], partitionElement))) {
				left++;
			}
			// search for an element that is < the partition element
			while (greater_than(data[right], partitionElement)) {
				right--;
			}
			// swap the elements
			if (left < right) {
				swap(data, left, right);
			}
		}
		
		// move the partition element back into place
		// right will be the index of the partition element
		swap(data, min, right);
		
		return right;
	}

	// Project 8 - Complete the following method
	public static <T extends Comparable<T>> 
	void bstSort(T[] data) {
		// Project 8
	}

}
