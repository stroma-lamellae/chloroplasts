/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assign_2;

import BasicIO.*;
import static java.lang.Character.*;


/** This class is a filter class that reads and returns words from an
  * ASCIIDataFile.
  *
  * @author  Ada-Lovês-Programmingbabbagémachinès
  * @studentNumber 5012386
  * @version  1.0 (Feb, 2016)                                                    */

public class WordReader {


    private ASCIIDataFile  source;  // source of text for reading words


    /** The constructor initializes the reader opening an ASCIIDataFile to read
      * from.                                                                    */

    public WordReader ( ) {

        source = new ASCIIDataFile();

    };  // construtor


    /** This method returns true if the underlying data file has reached EOF.
      *
      * @return  boolean  true if the file has reached EOF.                      */

    public boolean isEOF ( ) {

        return source.isEOF();

    };  // isEOF


    /** This method returns the next word (string of alphabetic characters) in the
      * data file. If the end of file is reached, a subsequent call to isEOF will
      * return true and the result of readWord is undefined.                     */

    public String readWord ( ) {

        String  result;  // next word read
        char    c;       // next character in input

        result = "";
        for ( ; ; ) {  // skip to alphabetic
            c = source.readC();
        if ( source.isEOF() || isLetter(c) ) break;
        };
        while ( !source.isEOF() && isLetter(c) ) {
            result = result + c;
            c = source.readC();
        };
        return result;

    };  // readWord


    /** This method closes the WordReader                                          */

    public void close ( ) {

        source.close();

    };  // close


}  // WordReader

