import java.util.*;
import java.io.*;

public class Decrypt {
	
	public static void main (String args[]) throws IOException
    {
		//final String key = args[0].toUpperCase;
        //final File in = new File(args[1]);
        //final String out = args[2];
        
        final String key = "ABCDEFGH";                                // variable to store encryption key
        final File in = new File("input.txt");                         // variable to store input file
        final String outFile = "output.txt";                         // name of output file
        
        final int SQUARE = 8;
        
        int hash = key.hashCode();                              // hashed key
        Random random = new Random(hash);                       // created random generator using hashed value as seed
        Scanner scanner = new Scanner(in);                      // created a scanner from the input file
        String fileString ="";                                  // created a variable to hold the contents of the input file
        while(scanner.hasNext())                                // appended every value from the scanner to the variable
        {
            fileString += scanner.nextLine();
        }
        fileString = fileString.toUpperCase();                  // converted the input text to uppercase
        
        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";        // created a variable to store the proper alphabet
        String origAlphabet = alphabet;                         // made another variable to store the alphabet for later
        alphabet = alphabetEncryptor(hash, alphabet);           // replaced the alphabet with an encrypted version
        //System.out.println(alphabet);
        int[] pattern = pattern(hash, SQUARE);                  // generated the pattern used to read the array
        //System.out.println(fileString);
        
        String decryptedString = "";                            // location to store the decrypted string
        String encryptedString = "";                            // location to store the re-sorted string
        while(fileString.length() > 0)
        {
            char[][] encryptedArray = encryptedArray(SQUARE, fileString, pattern);              // temporary array of 64 encrypted characters
            if(fileString.length() >= 64)                                                       // removes the 64 characters from the string
            {
                fileString = fileString.substring((SQUARE*SQUARE), fileString.length());
            }
            else                                                    // if there is less than 64 characters left in the string
            {                                                       // clear the string
                fileString = "";
            }
            for(int i = 0; i < SQUARE; i++)                         // for every row
            {
                for(int j = 0; j < SQUARE; j++)                     // for every column
                {   
                    encryptedString += encryptedArray[i][j];        // add all of the sorted characters to the string
                }
            }
        }
        while(encryptedString.length() > 0)                     // while there are values to decrypt
        {
            decryptedString += origAlphabet.charAt(alphabet.indexOf(encryptedString.charAt(0)));    // match the letter to the original and add it to the new string
            encryptedString = encryptedString.substring(1, encryptedString.length());       // remove the first character of the encrypted string
        }
        System.out.println(decryptedString);
        
        PrintWriter out = new PrintWriter(outFile);
        out.println(decryptedString);
        out.close();
        
	}
    
    /**
     * @param hash
     * @param alphabet
     * @return
     */
    public static String alphabetEncryptor(int hash, String alphabet)
    {
        Random random = new Random(hash);
        for(int i = 0; i < 100; i++)                            // swap two random letters in the alphabet 100 times
        {
            int indLetter1 = random.nextInt(27);
            int indLetter2 = random.nextInt(27);
            char letter1 = alphabet.charAt(indLetter1);
            char letter2 = alphabet.charAt(indLetter2);
            alphabet = alphabet.replace(letter1, '$');
            alphabet = alphabet.replace(letter2, letter1);
            alphabet = alphabet.replace('$', letter2);
        }
        return alphabet;
    }
    
    /**
     * @param hash
     * @param size
     * @return
     */
    public static int[] pattern(int hash, int size)
    {
        int[] pattern = new int[size];
        for(int i = 0; i < size; i++)
        {
            pattern[i] = i;
        }
        Random random = new Random(hash);                       // set the random generator
        for(int i = 0; i < 100; i++)                            // swap two random numbers in the order 100 times
        {
            int indPattern1 = random.nextInt(8);
            int indPattern2 = random.nextInt(8);
            int tempPattern = pattern[indPattern1];
            pattern[indPattern1] = pattern[indPattern2];
            pattern[indPattern2] = tempPattern;
        }
        return pattern;
    }
    
    /**
     * @param SQUARE
     * @param fileString
     * @param pattern
     */
    public static char[][] encryptedArray(int SQUARE, String fileString, int[] pattern)
    {
        char[][] encryptedArray= new char[SQUARE][SQUARE];      // created a square 2d array to store the encrypted characters
        for(int j = 0; j < SQUARE; j++)
        {
            for(int i = 0; i < SQUARE; i++)
            {
                if(fileString.length() == 0)            // fill the array while there are values left in the string
                {
                    break;
                }
                encryptedArray[i][pattern[j]] = fileString.charAt(0);       // filled the array with the first character from the file
                fileString = fileString.substring(1, fileString.length());  // removed the character from the string
            }
        }
        return encryptedArray;
    }
}
