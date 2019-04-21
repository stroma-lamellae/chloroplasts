package A_3;
import Media.*;
import BasicIO.*;
import java.awt.*;
import static BasicIO.Formats.*;
import static java.lang.Math.*;
import static java.awt.Color.*;

/**
 * @author al-Khwārizmī Muḥammad ibn Mūsā
 * @studentNum  1235623
 */

public class QuestionThree {

  private  PictureDisplayer  display;
// Instance variable declarations
public QuestionThree ( ) {
  Picture oPic, nPic;

  oPic = new Picture();
  int h = oPic.getHeight();
  int w = oPic.getWidth();
  display = new PictureDisplayer(w,h);
  display.placePicture(oPic);
  display.waitForUser();
  display.close();

  nPic = new Picture(2*w,2*h);
  fill (nPic, 0, 0, oPic);
  fill (nPic, w-1, 0, oPic);
  fill (nPic, 0, h-1, oPic);
  fill (nPic, w-1, h-1, oPic);
  display = new PictureDisplayer();
  display.placePicture(nPic);
  display.close();
  nPic.save();
};

private double getLuminance (Pixel pix) {

  int r = pix.getRed();
  int g = pix.getGreen();
  int b = pix.getBlue();

  double lum = r+b+g/3;
  double ratio = lum/255;
  return ratio;

}

private void fill ( Picture n, int x, int y, Picture orig){

 int w = orig.getWidth();
 int h = orig.getHeight();
 int rand = (int)(16777216*random()+0);

  for(int c=0; c<w; c++){
    for(int r=0; r<h; r++){
       Pixel p = orig.getPixel(c,r);
       double ratio = getLuminance(p);
       double col = ratio * rand;
       double factor = pow(col, (1/3));
       Pixel g = n.getPixel(c+x,r+y);
       int red = p.getRed();
       int green = p.getGreen();
       int blue = p.getBlue();
       g.setRed(clip(red*factor));
       g.setGreen(clip(green*factor));
       g.setBlue(clip(blue*factor));
    }
  }
}  //fill

private int clip (double number){
  if(number>255){
    return 255;
  }
  else {
    return (int)(number);
  }
}

public static void main ( String[] args ) { QuestionThree c = new QuestionThree(); };
}
