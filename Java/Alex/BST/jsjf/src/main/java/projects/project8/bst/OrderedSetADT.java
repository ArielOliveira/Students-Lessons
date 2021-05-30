package projects.project8.bst;

import java.util.Iterator;
 
public interface OrderedSetADT<T> {
    /** 
     * Adds the specified element to the proper location in this set. 
     *
     * @param element the element to be added to this set
     */
    public void addElement(T element);
 
    /** 
     * Removes and returns the specified element from this set. 
     *
     * @param targetElement the element to be removed from the set
     * @return the element to be removed from the set
     */
    public T removeElement(T targetElement);
 
    /** 
     * Returns the specified element from the set
     * 
     * @param targetElement the element to be removed from the set
     * @return the smallest element in the set
     */
    public T find(T targetElement);
 
    /** 
     * Returns the smallest element in this set without removing it. 
     * 
     * @return the smallest element in the set
     */
    public T findMin();
 
    /** 
     * Returns the largest element in this set without removing it. 
     * 
     * @return the largest element in the set
     */
    public T findMax();
    /** 
     * Returns true if this set is empty and false otherwise.
     *
     * @return true if this set is empty, false otherwise
     */
 
    /** 
     * Returns true if the set contains an element that matches
     * the specified element and false otherwise. 
     *
     * @param targetElement the element being sought in the tree
     * @return true if the tree contains the target element
     */
    public boolean contains(T targetElement);
 
    /**  
     * Returns the string representation of the elements in the set in order.
     *
     * @return a string representation of the elements in the set in order.
     */
    public String toString();
 
    /**  
     * Returns an iterator over the elements of this set in order.
     *
     * @return an iterator over the elements of this set
     */
    public Iterator<T> iterator();

}
