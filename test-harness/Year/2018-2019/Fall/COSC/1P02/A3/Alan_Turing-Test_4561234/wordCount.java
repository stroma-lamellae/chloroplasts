package Assign_2;

import BasicIO.*;

/**
 * This class sets the conditions for a word object with
 * String word and int frequency and contains appropriate
 * accessor and updater methods
 * @author  Alan Turing-Test
 * @studentNum 4561234
 */

public class wordCount {
    private  Node             random;   //a sequentially linked structure containing occuring words and their frequency
    private  ASCIIDisplayer   display;  //used to display final sorted list
    private  Node             sorted;   //a sequentially linked structure containing the final sorted list of words

    /**
 * Constructor
 *
 * Reads all words from a text file, entering unique words into
 * a sequentially linked structure "random" and increasing the frequency
 * of each word that is not unique. Once the list is created, methods sortList()
 * and list(sorted) are called to sort and list the sorted words before the
 * program is closed.                                                  */

    public wordCount(){
        String     read;     //a word read from the text
        NodeReader reader;   //an instance of the NodeReader class
        Node       aNode;    //an instance of the word class
        boolean    b;
        random = null;       //initialize lists to null
        sorted = null;
        reader = new NodeReader();

        for(;;){
            read = reader.readNode();
        if(reader.isEOF()) break;
            aNode = new Node(read);
            b = wordSearch(read);
            if (!b){
             addNode(aNode);
            }
        }
        sortList();
        list(sorted);
        reader.close();
        display.close();
    } //constructor

    /**sortList()
      * this method sets p to random and calls the maxFreq() method
      * to set the first value of the sorted list. Each node of the
      * random list is sent to the addSorted method to be sorted.
     */

    private void sortList(){
      Node p,q;
      p = random;
      maxFreq();

      while(p!=null){
        addSorted(p.item);
        p = p.next;
      }
    } //sortList

    /** addSorted()
      * sorts each word object sent from the random list by frequency
      * against each node in the sorted list and inserts node in decending
      * order by frequency
     * @param w a word object taken from the random list
     */

    private void addSorted(Node w){
      Node p,q;
      p = sorted;
      q = null;

      while(p!=null && w.getFreq()<p.item.getFreq()){
        q = p;
        p = p.next;
      }
      if (q==null){
        sorted = new Node (w, p);
      }
      else {
        q.next = new Node(w, p);
      }
    } //addSorted

    /** maxFreq()
     * this method finds the word object on the random list with the
     * highest frequency and inserts it as the first item on the sorted list
     */

    private void maxFreq(){
      Node p;
      int  f;
      Node w;

      p = random;
      f = p.item.getFreq();
      w = p.item;
      p = p.next;
      while(p!=null){
        if(p.item.getFreq()>f) {
          w = p.item;
        }
        p=p.next;
      }
      sorted = new Node(w, sorted);
    }

    /**wordSearch()
      * searches for a word from the text within the random list and
      * returns a boolean value depending on whether or not the word is
      * found. If the word is found, the frequency is increased by one and
      * true is returned.
      *
     * @param r a word from the text file used as a search key
     * @return boolean
     */

    private boolean wordSearch(String r){
      Node p;
      p = random;
      while(p!=null){
        if (p.item.getNode().equalsIgnoreCase(r)){
          p.item.addFreq();
          return true;
        }
        p = p.next;
      }
      return false;
    } //wordSearch

    /**addNode()
      * adds a word object as a node to the end of the random list
     * @param w
     */
    private void addNode(Node w){
      random = new Node(w, random);

    } //addNode

    /**list()
      * prints the frequency followed by the word of the object contained
      * in each node followed by a new line of the passed list
     * @param list to be printed out to an ASCIIDisplayer
     */

    private void list(Node list){
      Node p;
      display = new ASCIIDisplayer();
      p = list;
      while (p!=null){
        display.writeInt(p.item.getFreq());
        display.writeString(p.item.getNode());
        display.newLine();
        p = p.next;
      }
    } //list

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {wordCount w = new wordCount();}
}


