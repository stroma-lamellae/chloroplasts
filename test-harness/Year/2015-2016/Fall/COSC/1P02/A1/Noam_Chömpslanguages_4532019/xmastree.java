package A_1;

import Media.*;
import Media.Turtle.*;
import static java.lang.Math.*;
import static java.awt.Color.*;

public class xmastree {
  private    TurtleDisplayer       display;
  private    Turtle                franklin;
  
  public xmastree () {
    display = new TurtleDisplayer();
    franklin = new Turtle();
    display.placeTurtle(franklin);
    drawTree();  
    
    display.close();
    
  }  //constructor
  
  private void drawTree() {
    drawRectangle(10,20);
    franklin.left(PI/2);
    franklin.forward(20);
    franklin.right(PI/2);
    franklin.backward(25);
    drawTriangle(60);
    franklin.left(PI/2);
    franklin.forward(20);
    franklin.right(PI/2);
    drawTriangle(60);
  }  //drawTree
  
  private void drawRectangle(double width, double height){
    franklin.setPenWidth(3);
    franklin.penDown();
    for(int i=0; i<2;i++){
    franklin.forward(width);
    franklin.left(PI/2);
    franklin.forward(height);
    franklin.left(PI/2);
    };
    franklin.penUp();
  }  //drawRectangle
  
  private void drawTriangle(double side) {
    franklin.setPenColor(GREEN);
    franklin.setPenWidth(6);
    franklin.penDown();
    for(int i=0; i<3; i++) {
      franklin.forward(side);
      franklin.left(2*PI/3);
    };
    franklin.penUp();
  }  //drawTriangle
  
  public static void main (String[] args) {xmastree x = new xmastree();};
}