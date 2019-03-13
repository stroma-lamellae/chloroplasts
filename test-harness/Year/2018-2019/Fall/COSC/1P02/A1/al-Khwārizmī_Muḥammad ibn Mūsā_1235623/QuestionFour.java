package B_1;

/**
 * @author al-Khwārizmī Muḥammad ibn Mūsā
 * @studentNum  1235623
 */

import BasicIO.*;
import static BasicIO.Formats.*;
import static java.lang.Math.*;

public class QuestionFour {

  private ASCIIPrompter  prompt;
  private ASCIIDisplayer display;
// Instance variable declarations

  public QuestionFour ( ) {
    int number;
    int length = 0;
    int max = 0;

    prompt = new ASCIIPrompter();
    display = new ASCIIDisplayer();
    prompt.setLabel("Enter a number");
    number = prompt.readInt();
    display.writeInt(number);
    for(;;){
      checkMax(number, max);
    if(number == 1) break;
    nextNumber(number);
    length = length +1;
    if(length%10 == 0) {display.newLine();};
    display.writeInt(number);
    }

    display.newLine();
    display.newLine();
    display.writeString("Length of Sequence: ");
    display.writeInt(length);
    display.newLine();
    display.writeString("Maximum value reached: ");
    display.writeInt(max);

};
// constructor
// constructor

private int nextNumber (int number) {
  int newNum;

  if (number%2 == 0){
    newNum = number/2;
    return newNum;
  }
  else{
    newNum = number*3 +1;
    return newNum;
  }
}

private int checkMax(int num, int maxi){
  if(num>maxi){
    maxi = num;
}
  return maxi;
}

// Method declarations
public static void main ( String[] args ) { QuestionFour c = new QuestionFour(); };
}
