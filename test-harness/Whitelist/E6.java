package Exercise_6_1;

import BasicIO.*;


/** This program uses prints the average of the squares
  ** from 1 to 10.
  **
  ** @author D. Hughes, D. Bockus
  **
  ** @version 1.2 (Oct. 2011)                                                    */

public class E6 {
    
    
    private ASCIIDisplayer  display;  // displayer for output
    
    
    /** The constructor sets up the displayer.                                   */
    
    public E6 ( ) {
        
        int     sum;
        double  ave;
        
        display = new ASCIIDisplayer();
        sum = 0;
        for ( int i=1 ; i<=10 ; i++ ) { 
            sum = sum + square(i);
        };   
        
        ave = (double)sum / 10;
        display.writeString("Average of squares from 1 to 10: ");
        display.writeDouble(ave);
        display.newLine();
        
        display.close();
        
    }; // constructor
    
    
    public int square ( int x ) {         
        return x * x;
        
    }; // square
    
    
    public static void main ( String args[] ) { E6 e = new E6(); };
    
    
} // E6
