package TestCCS;

import Sequence.*;
import BasicIO.*;
import java.lang.*;

/**
    * @author  Ada Lovês
    * @studentNum 5012386
    */

public class TestCCS {

  private ASCIIDataFile  test;
  private ASCIIDisplayer out;

  public TestCCS () {
  String s;
  CharacterSequence c;
  boolean b;


    test = new ASCIIDataFile();
    out = new ASCIIDisplayer();
    for(;;){
        s = test.readLine();
    if(test.isEOF()) break;
    System.out.println("Not EOF");
    c = new ConCharSequence(s).trim().toLowerCase();
    b = isPalindrome(c);
    if(b){
        out.writeString("'"+ c +"'"+" is a Palindrome");
        out.newLine();
    }
    else{
        out.writeString("'"+ c +"'"+" is not a Palindrome");
        out.newLine();
    }
    }
    test.close();
    out.close();

  } //constructor

  private boolean isPalindrome(CharacterSequence cs){
      char [] csArray, check;
      CharacterSequence a;
      if (cs.length() == 0 || Character.isWhitespace(cs.charAt(0))){
          return false;
      }
      csArray = cs.toString().toCharArray();
      check = new char[csArray.length];

      for(int i=0; i<csArray.length; i++){
          check[i] = csArray[csArray.length-1-i];
      }
      return new ConCharSequence(csArray).equals(new ConCharSequence(check));
       }

  public static void main (String[] args) {TestCCS t = new TestCCS();};

}


