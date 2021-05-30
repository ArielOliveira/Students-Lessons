package project3HeapStructure;
import java.util.ArrayList;
class heap<T> {
  @SuppressWarnings("unchecked")
/*public void heapify(ArrayList<T> hT, int i) {
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
  }*/

private void heapifyUp(ArrayList<T> hT, int i) {
  T temp = hT.get(i);

  while (i > 0 && ((Comparable<T>)temp).compareTo(hT.get(parent(i))) > 0) {
    hT.set(i, hT.get(parent(i)));
    i = parent(i);
  }

  hT.set(i, temp);
}

private void heapifyDown(ArrayList<T> hT, int i) {
  if (isLeaf(hT, i))
    return;

  T leftChild = null;
  T rightChild = null;
    
  if (leftChild(i) < hT.size()) {
    if (((Comparable<T>)hT.get(i)).compareTo(hT.get(leftChild(i))) < 0) {
        leftChild = hT.get(leftChild(i));
    }
  }

  if (rightChild(i) < hT.size()) {
    if (((Comparable<T>)hT.get(i)).compareTo(hT.get(rightChild(i))) < 0) {
      rightChild = hT.get(rightChild(i));
    }
  }

  if (leftChild != null && rightChild != null) {
    if (((Comparable<T>)hT.get(leftChild(i))).compareTo(hT.get(rightChild(i))) > 0) {
      swap(hT, i, leftChild(i));
      heapifyDown(hT, leftChild(i));
    } else {
      swap(hT, i, rightChild(i));
      heapifyDown(hT, rightChild(i));
    }
  }

  if (leftChild != null) {
    swap(hT, i, leftChild(i));
    heapifyDown(hT, leftChild(i));
  }

  if (rightChild != null) {
    swap(hT, i, rightChild(i));
    heapifyDown(hT, rightChild(i));
  }
}

private void sortHeapify(ArrayList<T> hT, int n, int i)
    {
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;
 
        // finding the maximum of left and right
        if (l < n && ((Comparable<T>)hT.get(l)).compareTo(hT.get(largest)) > 0)
            largest = l;
 
        if (r < n && ((Comparable<T>)hT.get(r)).compareTo(hT.get(largest)) > 0)
            largest = r;
 
        //swapping if child >parent
        if (largest != i) {
            swap(hT, i, largest);
 
            sortHeapify(hT, n, largest);
        }
}

public void sort(ArrayList<T> hT) {
    int n = hT.size();

  //build heap by calling heapify on non leaf elements
    for (int i = n / 2 - 1; i >= 0; i--)
        sortHeapify(hT, n, i);

 //extract elements from the root and call healpify
    for (int i=n-1; i>0; i--)
    {
      // swap the last element with root
        swap(hT, 0, i);

        // i is the size of the reduced heap
        sortHeapify(hT, i, 0);
    }
}

private void swap(ArrayList<T> hT, int lhs, int rhs) {
  T left = hT.get(lhs);
  T right = hT.get(rhs);
  hT.set(lhs, right);
  hT.set(rhs, left);
}

private int parent(int pos) {
  return pos / 2;
}

private int leftChild(int pos) {
  return (2 * pos) ;
}

private int rightChild(int pos) {
  return (2 * pos) + 1;
}

private boolean isLeaf(ArrayList<T> hT, int pos) {
  if (pos >= (hT.size()-1 / 2) && pos <= hT.size()-1) {
      return true;
  }
  return false;
}

public void insert(ArrayList<T> hT, T newObject) { 
	  hT.add(newObject);

	  heapifyUp(hT, hT.size()-1);
  }
  
  public boolean DeleteMax(ArrayList<T> hT) {
	  boolean hasDeleted = false;
	  
	 if(!hT.isEmpty()) {
		hT.set(0, hT.get(hT.size()-1));
    hT.remove(hT.get(hT.size()-1));
    System.out.print("list after removed ");
    printArray(hT);

    if (!hT.isEmpty()) {
		  heapifyDown(hT,0);
    }
		
		hasDeleted = true;
	 }
	 
	 return hasDeleted;
  } 
 
  public String printArray(ArrayList<T> array) {
    String heapString = new String();
    for (T i : array) {
      heapString += i + " ";
    }
    return heapString;
  }
}
   

