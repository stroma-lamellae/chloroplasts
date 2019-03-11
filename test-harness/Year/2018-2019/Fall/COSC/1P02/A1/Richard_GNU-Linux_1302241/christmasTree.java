package Test_A_1;

import Media.*;
import java.awt.*;
import Media.Tortoise.*;
import static java.awt.Color.*;
import static java.lang.Math.*;

/** This class is a filter class that reads and returns words from an
  * ASCIIDataFile.
  *
  * @author  Richard GNU-Linux
  * @studentNumber 1302241
  * @version  1.0 (Feb, 2016)                                                    */

public class christmasTree {
  private    TortoiseDisplayer       display;
  private    Tortoise                morla;

  public christmasTree() {
    display = new TortoiseDisplayer();
    morla = new Tortoise(20);

    display.placeTortoise(morla);
    drawTree();
    display.close();


  } //christmasTree

  private void drawRectangle(double width, double height) {
    morla.setPenColor(black);
    morla.setPenWidth(3);
    morla.penDown();
    for (int i=0; i<2;i++) {
      morla.forward(width);
      morla.left(PI/2);
      morla.forward(height);
      morla.left(PI/2);
    };
    morla.penUp();
  } //drawRectangle

  private void drawTriangle(double side) {
    morla.setPenColor(green);
    morla.setPenWidth(6);
    morla.penDown();
    for(int i=0; i<3;i++) {
      morla.forward(side);
      morla.left(2*PI/3);
    }
    morla.penUp();
  }

  private void drawTree() {
    drawRectangle(10,25);
    morla.left(PI/2);
    morla.forward(25);
    morla.left(PI/2);
    morla.forward(25);
    morla.left(PI);
    drawTriangle(60);
    morla.left(PI/2);
    morla.forward(20);
    morla.right(PI/2);
    drawTriangle(60);
  }


  public static void main (String[] args) {christmasTree x = new christmasTree();};
}
