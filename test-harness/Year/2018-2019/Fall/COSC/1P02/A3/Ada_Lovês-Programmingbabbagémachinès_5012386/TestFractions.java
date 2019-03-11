package TestFractions1;


import Fractions.*;
import BasicIO.*;


/** This class is a program to serve as a testbed for the Fraction interface
  * and the RatioFraction class.
  *
  * @see Fraction
  * @see RatioFraction
  *
  * @author  Ada Lovês
  * @studentNum 5012386
  */

public class TestFractions {


    private ASCIIDisplayer out;


    /** The constructor opens an ASCIIDisplayer and performs the tests.          */

    public TestFractions ( ) {

        Fraction  f, g, h;  // fractions for testing
        int       r;

        out = new ASCIIDisplayer();

        f = new RatioFraction(1,3);
        out.writeString("1/3 = " + f);
        out.newLine();
        f = new RatioFraction(3,9);
        out.writeString("3/9 = " + f);
        out.newLine();
        f = new RatioFraction(9,3);
        out.writeString("9/3 = " + f);
        out.newLine();
        f = new RatioFraction(-1,3);
        out.writeString("-1/3 = " + f);
        out.newLine();
        f = new RatioFraction(1,-3);
        out.writeString("1/-3 = " + f);
        out.newLine();
        f = new RatioFraction(-1,-3);
        out.writeString("-1/-3 = " + f);
        out.newLine();
        f = new RatioFraction(0,3);
        out.writeString("0/3 = " + f);
        out.newLine();
        try {
            f = new RatioFraction(1,0);
            out.writeString("1/0 = " + f);
        }
        catch ( ZeroDenominatorException e ) {
            out.writeString("1/0 = zero denominator");
        };
        out.newLine();

        out.close();

    }; // constructor


    public static void main ( String[] args ) { TestFractions t = new TestFractions(); };


} // TestFractions
