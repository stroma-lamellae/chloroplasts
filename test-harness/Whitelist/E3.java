package Assign_2;

import Media.*;  //
import static java.awt.Color.*;  //
import static java.lang.Math.*;  //
/** This class
  * 
  * @author Lindsey Tulloch
  * @student #: 594 3907
  * @version 1 (October 2015)
**/

public class Cover {
  
  private TurtleDisplayer   display;
  private Turtle            donatello;
  

  
  public Cover ( ) {
    
    display = new TurtleDisplayer();
    donatello = new Turtle.FAST;
    display.placeTurlte(donatello);
    
    drawTriangle();
    
  };  //constructor
  
  private void drawTriangle() {
    
    double sideA;
    double sideB;
    double eAngle;
    double iAngle;
    
    sideA=30.0;
    sideB= 60.0;
    eAngle= 3*PI/4 ;
    rAngle= PI/2 ;
    
    
    donatello.penDown();
    donatello.forward(sideA);
    donatello.left(eAngle);
    donatello.forward();
    donatello.left(eAngle);
    donatello.forward(sideA);
    donatellor.left(rAngle);
    
  }; //drawTriangle
  
  public static void main (String args[]) (Cover c = new Cover(););
}


