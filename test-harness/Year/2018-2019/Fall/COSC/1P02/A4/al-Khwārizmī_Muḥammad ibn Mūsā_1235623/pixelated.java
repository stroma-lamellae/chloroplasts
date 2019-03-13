package Assign_6;

import java.awt.*;
import static java.awt.Color.*;
import java.util.*; ;
import Media.*;


public class pixelated {
     private    PictureDisplayer    display;


     public pixelated() {
       Picture   pic;
       display = new PictureDisplayer();
       pic = new Picture();
       display.placePicture(pic);
       display.waitForUser();
       pixelate(pic, 4);
       display.close();
       pic.save();

     }  //constructor

     private Color aveColor (Picture pix, int c, int r, int blockSize) {
       int rouge;
       int red;
       int b;
       int blue;
       int g;
       int green;
       Color color;

       red = 0;
       blue = 0;
       green = 0;

       for (int i=r; i<blockSize; i++){
         for (int j=c; j<blockSize; j++){
           rouge = pix.getPixel(c,r).getRed();
           b = pix.getPixel(c,r).getBlue();
           g = pix.getPixel(c,r).getGreen();
           red = red +rouge;
           blue = blue +b;
           green = green +g;
         };
       };
       rouge = (red/blockSize^2);
       b = (blue/blockSize^2);
       g = (green/blockSize^2);
       return Color(rouge, g, b);
     }  //aveColor

     private void paint (Picture pix, int c, int r, int blockSize, Color color) {
       Pixel p;

       for (int i=r; i<blockSize; i++){
         for (int j=c; j<blockSize; j++){
           p = pix.getPixel(j, i);
           p.setColor(color);
         };
       };
     }  //paint

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


     private void pixelate (Picture pix, int blockSize) {
       Pixel p;
       do{
         for (int r=0; r<pix.getHeight(); r=r+4){
         for (int c=0; c<pix.getWidth(); c=c+4){
           p= pix.getPixel(c,r);
           color = aveColor(pix, c, r, blockSize);
           paint(pix, c, r, blockSize, color);
         };
       };

       } while(pix.hasNext());


     }  //pixelate




  public static void main (String[] args) {pixelated p = new pixelated();};
}
