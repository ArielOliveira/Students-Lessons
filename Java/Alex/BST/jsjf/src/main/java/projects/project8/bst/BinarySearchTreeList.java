package projects.project8.bst;

import java.util.Iterator;

import projects.project8.bst.LinkedBinarySearchTree;
import projects.project8.bst.ListADT;
import projects.project8.bst.OrderedListADT;

/**
 * BinarySearchTreeList represents an ordered list implemented using a binary
 * search tree.
 * 
 * @author Java Foundations
 * @version 4.0
 */
public class BinarySearchTreeList<T> implements ListADT<T>, OrderedListADT<T>, Iterable<T>
{
	LinkedBinarySearchTree<T> tree;
	/**
	 * Creates an empty BinarySearchTreeList.
	 */
	public BinarySearchTreeList() 
	{
		super();
		tree = new LinkedBinarySearchTree<T>();
	}

	/**
	 * Adds the given element to this list.
	 * 
	 * @param element the element to be added to the list
	 */
	@Override
	public void add(T element)
	{
		tree.addElement(element);
	}

	/**
	 * Removes and returns the first element from this list.
	 *
	 * @return the first element in the list
	 */
	public T removeFirst()
	{
		return tree.removeMin();
	}

	/**
	 * Removes and returns the last element from this list.
	 *
	 * @return the last element from the list
	 */
	public T removeLast()
	{
		return tree.removeMax();
	}

	/**
	 * Removes and returns the specified element from this list.
	 *
	 * @param element the element being sought in the list
	 * @return the element from the list that matches the target
	 */
	public T remove(T element)
	{
		return tree.removeElement(element);
	}

	/**
	 * Returns a reference to the first element on this list.
	 *
	 * @return a reference to the first element in the list
	 */
	public T first()
	{
		return tree.findMin();
	}

	/**
	 * Returns a reference to the last element on this list.
	 *
	 * @return a reference to the last element in the list
	 */
	public T last()
	{
		return tree.findMax();
	}

	/**
	 * Returns an iterator for the list.
	 *
	 * @return an iterator over the elements in the list
	 */
	public Iterator<T> iterator()
	{
		return tree.iteratorInOrder();
	}

	@Override
	public boolean contains(T target) {
		return tree.contains(target);
	}

	@Override
	public boolean isEmpty() {
		return tree.isEmpty();
	}

	@Override
	public int size() {
		return tree.size();
	}
}

