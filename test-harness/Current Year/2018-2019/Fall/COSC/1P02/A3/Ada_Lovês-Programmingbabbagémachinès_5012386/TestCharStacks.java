package TestCharStacks;


import CharStacks.*;
import BasicIO.*;


/** This class is a test class for testing the CharStack implementations: ConStack
  * and LnkStack. It consecutively creates a stack (in each of the representations)
  * and then loads it with the characters from 'A' to 'Z'. It then pops the items
  * from the stack until empty, printing them. The result should be the letters in
  * reverse order.
  *
  * @see  CharStack
  * @see  ConCharStack
  * @see  LnkCharStack
  *
  * @author  Ada Lovês
  * @studentNum 5012386
  */

public class TestCharStacks {


    private ASCIIDisplayer  out;  // output stream


    /** The constructor tests the CharStack implementation classes: ConStack and
      * LnkStack using the method testStack.                                     */

    public TestCharStacks ( ) {

        CharStack  s;  // a stack

        out = new ASCIIDisplayer();

        s = new ConCharStack(100);
        out.writeString("Testing Consecutive Stack");
        out.newLine();
        out.newLine();
        testStack(s);
        out.newLine();
        out.newLine();

        s = new LnkCharStack();
        out.writeString("Testing Linked Stack");
        out.newLine();
        out.newLine();
        testStack(s);

        out.close();

    };  // constructor


    /** This method does the actual test of a CharStack.
      *
      * @param  s  a stack to test                                               */

    private void testStack ( CharStack s ) {

        char  c;

        out.writeString("Loading Stack...");
        out.newLine();
        for ( c='A' ; c<='Z' ; c++ ) {
            s.push(c);
        };
        out.writeString("Stack loaded.");
        out.newLine();
        out.writeString("Top item: ");
        out.writeChar(s.top());
        out.newLine();
        out.writeString("Dumping stack");
        out.newLine();
        while ( ! s.empty() ) {
            out.writeChar(s.pop());
        };
        out.newLine();
        out.writeString("Stack emptied");
        out.newLine();
        out.writeString("Top item: ");
        try {
            out.writeChar(s.top());
        }
        catch ( UnderflowException e ) {
            out.writeString("underflow");
        };
        out.newLine();
        out.writeString("Pop at empty: ");
        try {
            out.writeChar(s.pop());
        }
        catch ( UnderflowException e ) {
            out.writeString("underflow");
        };
        out.newLine();

    };  // testStack


    public static void main ( String[] args ) { new TestCharStacks(); };


} // TestCharStacks
