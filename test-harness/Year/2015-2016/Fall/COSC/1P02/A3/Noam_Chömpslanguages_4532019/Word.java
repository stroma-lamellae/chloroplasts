package Assign_2;

/**
 * This class sets the conditions for a word object with 
 * String word and int frequency and contains appropriate
 * accessor and updater methods
 * 
 * @author Lindsey Tulloch
 *  
 * @student Number 594 3907
 * 
 * @date February 21st 2016
 * 
 */
public class Word {
    private String word;
    private int    frequency;

    public Word(String w){
        this.word = w;
        frequency = 1;
               
    }
    
    public String getWord(){
        return word;
    } 
    
    public int getFreq(){
      return frequency;
    }
    
    public void addFreq(){
      frequency = frequency +1;
    }
}

