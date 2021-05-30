package projects.project8;

import projects.project8.bst.LinkedBinarySearchTree;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        LinkedBinarySearchTree<Integer> tree = new LinkedBinarySearchTree<>();

        tree.addElement(5);
        tree.addElement(3);
        tree.addElement(7);
        tree.addElement(2);
        tree.addElement(4);
        
        
        System.out.println( tree.printTree() );
    }
}
