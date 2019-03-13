package Assign_2;

/**
 * This class sets the conditions for a word object with
 * String word and int frequency and contains appropriate
 * accessor and updater methods
 * @author  Alan Turing-Test
 * @studentNum 4561234

 */

public class Node {
    private String word;
    private int    frequency;

    public Node(String w){
        this.word = w;
        frequency = 1;

    }

    public String getNode(){
        return word;
    }

    public int getFreq(){
      return frequency;
    }

    public void addFreq(){
      frequency = frequency +1;
    }
}

