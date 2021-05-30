package project3HeapStructure;
import java.util.ArrayList;
class heap<T> {
  @SuppressWarnings("unchecked")
public void heapify(ArrayList<T> hT, int i) {
    int size = hT.size();
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && ((Comparable<T>)hT.get(l)).compareTo(hT.get(largest))>0)


      largest = l;
    if (r < size && ((Comparable<T>)hT.get(l)).compareTo(hT.get(largest))<0)

      largest = r;
 
    if (largest != i) {
      T temp = hT.get(largest);
      hT.set(largest, hT.get(i));
      hT.set(i, temp);
 
      heapify(hT, largest);
    }
  }
 
  public void insert(ArrayList<T> hT, T newObject) {
   /* int size = hT.size();
    if (size == 0) {
      hT.add(newObject);
    } else {
      hT.add(newObject);
      for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(hT, i);
      }
    }*/
	  
	  hT.add(newObject);
	  heapify(hT, 0);
  }
  
  public boolean DeleteMax(ArrayList<T> hT) {
	  boolean hasDeleted = false;
	  
	 if(hT.size()>0) {
		 hT.remove(0);
		hT.add(0,hT.get(hT.size()-1)); 
		heapify(hT,0);
		
		hasDeleted = true;
	 }
	 
	 return hasDeleted;
  }
 
 
 
  public void printArray(ArrayList<T> array) {
    for (T i : array) {
      System.out.print(i + " ");
    }
    System.out.println();
  }
}
   

