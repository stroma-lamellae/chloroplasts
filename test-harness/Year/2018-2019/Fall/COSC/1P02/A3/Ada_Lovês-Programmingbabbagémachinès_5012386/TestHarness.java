package Assign_3;

import Sequence.*;
import BasicIO.*;

/** This class tests the ConCharSequence class from the package Sequence.
 *
 * @author  Ada Lovês
 * @studentNum 5012386
 */

public class TestHarness {

    private ASCIIDisplayer out;


    /** The constructor opens an ASCIIDisplayer and performs the tests.          */

    public TestHarness ( ) {

        char c;                            // char for testing
        char[] helloA, spacesA;            // char[] for testing
        String str, two, blank, spaces;    // Strings for testing
        CharacterSequence cs, test;        // CharacterSequence for testing
        boolean e;                         // boolean for testing
        int  n;                            // int for testing

        blank = "";
        c = '$';
        str = "hello lleh";
        spaces = "  spacesarehere  ";


        helloA = str.toCharArray();
        spacesA = spaces.toCharArray();


        out = new ASCIIDisplayer();

        cs = new ConCharSequence(blank);                        //creates a blank ConCharSequence
        out.writeString("Blank character sequence =" + cs);
        out.newLine();
        cs = new ConCharSequence(c);                            //creates a ConCharSequence with 1 char
        out.writeString("This is the $ character =" + cs);
        out.newLine();
        e = new ConCharSequence(spaces).equals(cs);             //checks whether two ConCharSequences are the same
        out.writeString("This is false, right? " + e);
        e = new ConCharSequence("  spacesarehere  ").equals(spaces);
        out.writeString("   And this is true, right? " + e);    //checks whether two ConCharSequences are the same
        out.newLine();
        n = new ConCharSequence(spaces).compareTo(cs);          //compares two ConCharSequences
        out.writeString("This is negative = " + n);
        n = new ConCharSequence(cs).compareTo(cs);              //compares two ConCharSequences
        out.writeString("   This is 0 = " + n);
        n = new ConCharSequence(cs).compareTo(spaces);          //compares two ConCharSequences
        out.writeString("   This is positive = " + n);
        out.newLine();
        cs = new ConCharSequence(spaces).trim().toUpperCase();  //trims a ConCharSequence and converts to uppercase
        out.writeString("spacesarehere   trimmed and touppercase = " + cs);
        out.newLine();
        cs = new ConCharSequence(cs).toLowerCase().concat("SURE"); //converts a ConCharSequence to lowercase and concatenates a string
        out.writeString("SPACESAREHERE tolowercase and concat SURE = " + cs);
        out.newLine();
        cs = new ConCharSequence(helloA).replace('l', 'k');     //changes each character of a ConCharSequence to another
        out.writeString("replace l with k: hekko kkeh = " + cs);
        out.newLine();
        c = new ConCharSequence(helloA).charAt(4);              //checks char at specified index
        out.writeString("the character at index 4 is 'o' = " + c);
        out.newLine();
        n = new ConCharSequence(cs).length();                   //checks length of ConCharSequence
        out.writeString("the length of hekko kkeh is 10 = " + n);
        out.newLine();
        cs = (CharacterSequence) new ConCharSequence(spaces).subSequence(3, 7);  //checks specified subsequence of a ConCharSequence
        out.writeString("This is a subsequence of spaces = " + cs);
        out.newLine();
        out.newLine();

        /** Error checking **/
       try {
            cs = (CharacterSequence)new ConCharSequence(helloA).subSequence(0, 25);
            out.writeString("Subsequence 0, 25 is = " +cs);
            out.newLine();

       }
        catch ( Sequence.IndexOutOfBoundsException i ) {
            out.writeString("Subsequence 0 and/or 25 is an invalid index");
            out.newLine();

        };
         try {
            cs = (CharacterSequence)new ConCharSequence(helloA).subSequence(10, 11);
            out.writeString("Subsequence 10, 11 is = " +cs);
            out.newLine();
         }
        catch ( Sequence.IndexOutOfBoundsException i ) {
            out.writeString("Subsequence 10 and/or 11 is an invalid index");
            out.newLine();
        }
        try {
            n = new ConCharSequence(helloA).charAt(10
        );
            out.writeString("the character at index 10 is = " +n);
            out.newLine();
        }
        catch ( Sequence.IndexOutOfBoundsException i ) {
            out.writeString("10 is an invalid index");
            out.newLine();
        };
        out.newLine();
        out.close();

    }; // constructor

    public static void main(String[] args) {TestHarness t = new TestHarness();};

    }
