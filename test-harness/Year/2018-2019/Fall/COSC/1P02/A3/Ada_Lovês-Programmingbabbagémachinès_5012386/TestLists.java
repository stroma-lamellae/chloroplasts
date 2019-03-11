package TestLists;

import Collections.*;
import BasicIO.*;

/**
    * @author  Ada Lovês
    * @studentNum 5012386
    */


/** This class is a test class for testing the List implementations: ConList and
  * LnkList. It performs a number of tests including add, remove, traversing,
  * iteratating, searching and tests of the exceptions.
  *
  * @see  List
  * @see  Keyed
  * @see  ConList
  * @see  LnkList
  *
  * @author  D. Hughes
  *
  * @version  1.0 (Jan. 2014)                                                    */

public class TestLists {


    private ASCIIDisplayer out;


    /** The constructor uses the method testList to test the list implementations*/

    public TestLists ( ) {

        List<Character> l;   // a list

        out = new ASCIIDisplayer();

        l = new ConList<Character>(100);
        out.writeString("Testing Contiguous List");
        out.newLine();
        out.newLine();
        testList(l);
        out.newLine();
        out.newLine();

        l = new LnkList<Character>();
        out.writeString("Testing Linked List");
        out.newLine();
        out.newLine();
        testList(l);

        out.close();

    }; // constructor


    /** This method does the actual test of a list.
      *
      * @param  l  a list to test                                                */

    private void testList ( List<Character> l ) {

        out.writeString("Initial list length: ");
        out.writeInt(l.length());
        out.newLine();
        out.newLine();
        out.writeString("Loading list, sequential order...");
        out.newLine();
        for ( char c='A' ; c<='H' ; c++ ) {
            l.add(c);
            l.advance();
        };
        out.writeString("List loaded.");
        out.newLine();
        out.writeString("List length: ");
        out.writeInt(l.length());
        out.newLine();
        out.writeString("Dumping list (sequential order)..");
        l.toFront();
        while ( ! l.offEnd() ) {
            out.writeChar(l.remove());
        };
        out.newLine();
        out.writeString("List length: ");
        out.writeInt(l.length());
        out.newLine();
        out.newLine();
        out.writeString("Loading list, reverse order...");
        out.newLine();
        for ( char c='A' ; c<='H' ; c++ ) {
            l.add(c);
        };
        out.writeString("List loaded.");
        out.newLine();
        out.writeString("List length: ");
        out.writeInt(l.length());
        out.newLine();
        out.writeString("Dumping list (reverse order)..");
        l.toFront();
        while ( ! l.offEnd() ) {
            out.writeChar(l.remove());
        };
        out.newLine();
        out.writeString("List length: ");
        out.writeInt(l.length());
        out.newLine();
        out.newLine();
        out.writeString("Searching List");
        out.newLine();
        for ( char c='B' ; c<='H' ; c++ ) {
            l.add('A');
            l.advance();
            l.add(c);
            l.advance();
        };
        l.add('A');
        out.writeString("List: ");
        l.toFront();
        while ( ! l.offEnd() ) {
            out.writeChar(l.get());
            l.advance();
        };
        out.newLine();
        out.writeString("Add X in front of D: ");
        l.toFront();
        while ( ! l.offEnd() && l.get() != 'D' ) {
            l.advance();
        };
        l.add('X');
        l.toFront();
        while ( ! l.offEnd() ) {
            out.writeChar(l.get());
            l.advance();
        };
        out.newLine();
        out.writeString("Remove X:            ");
        l.toFront();
        while ( ! l.offEnd() && l.get() != 'X' ) {
            l.advance();
        };
        l.remove();
        l.toFront();
        while ( ! l.offEnd() ) {
            out.writeChar(l.get());
            l.advance();
        };
        out.newLine();
        out.newLine();
        while ( ! l.offEnd() && l.get() != 'Z' ) {
            l.advance();
        };
        out.writeString("Get at off end: ");
        try {
            out.writeChar(l.get());
        }
        catch ( NoItemException e ) {
            out.writeString("off list");
        };
        out.newLine();
        out.writeString("Remove at off end: ");
        try {
            out.writeChar(l.remove());
        }
        catch ( NoItemException e ) {
            out.writeString("off list");
        };
        out.newLine();
        out.writeString("Advance at off end: ");
        l.advance();
        out.writeString("OK");
        out.newLine();

    }; // testList


    public static void main ( String[] args ) { TestLists t = new TestLists(); };


} // TestLists
