package exer_2_3;

import Media.*;
import static java.lang.Math.*;


/** This class is a program to draw a hexagon using Turtle Graphics.
  *
  * @author Alan Turing-Test
  *
  * @studentNum 4561234
  *
  * new concepts: for loop, index variable                                       */

public class pentagram {


    private TurtleDisplayer  display;  // display to draw on
    private Turtle           yertle;   // turtle to do drawing


    /** The constructor draws a hexagon using a for loop.                        */

    public pentagram( ) {

        display = new TurtleDisplayer();
        yertle = new Turtle();
        display.placeTurtle(yertle);

        yertle.penDown();
        for ( int i=1 ; i<=5 ; i++ ) {
            yertle.forward(80);
            yertle.right(4*PI/5);
        };
        yertle.penUp();

        display.close();

    };  // constructor


    public static void main ( String[] args ) { pentagram h = new pentagram(); };


}
