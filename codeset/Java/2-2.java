import java.util.*;
import java.io.*;

public class Decryptor {
    int hash;
    Random random;
    Scanner scanner;
    String fileString;

    public Decryptor(){
        final String key = "ABCDEFGH"; 
        final File in = new File("input.txt"); 
        final String outFile = "output.txt"; 

        final int SQUARE = 8;

        hash = key.hashCode(); 
        random = new Random(hash); 
        scanner = new Scanner(in); 
        fileString = ""; 
        while (scanner.hasNext()) 
        {
            fileString += scanner.nextLine();
        }
        fileString = fileString.toUpperCase(); 

        String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; 
        String origAlphabet = alphabet; 
        alphabet = alphabetEncryptor(hash, alphabet); 
        
        int[] pattern = pattern(hash, SQUARE); 
        

        String decryptedString = ""; 
        String encryptedString = ""; 
        while (fileString.length() > 0) {
            char[][] encryptedArray = encryptArray(SQUARE, fileString, pattern); 
                                                                                   
            if (fileString.length() >= 64) 
            {
                fileString = fileString.substring((SQUARE * SQUARE), fileString.length());
            } else 
            { 
                fileString = "";
            }
            for (int i = 0; i < SQUARE; i++) 
            {
                for (int j = 0; j < SQUARE; j++) 
                {
                    encryptedString += encryptedArray[i][j]; 
                }
            }
        }
        while (encryptedString.length() > 0) 
        {
            decryptedString += origAlphabet.charAt(alphabet.indexOf(encryptedString.charAt(0))); 
                                                                                                 
                                                                                                 
            encryptedString = encryptedString.substring(1, encryptedString.length()); 
                                                                                      
        }
        System.out.println(decryptedString);

        PrintWriter out = new PrintWriter(outFile);
        out.println(decryptedString);
        out.close();
    }

    public static void main(String args[]) throws IOException {
        new Decryptor();
    }

    public String alphabetEncryptor(int hash, String alphabet) {
        char[] chars = alphabet.toCharArray();
        Random random = new Random(hash);
        for (int i = 0; i < 100; i++) 
        {
            int indLetter1 = random.nextInt(27);
            int indLetter2 = random.nextInt(27);
            char temp = chars[indLetter1];
            chars[indLetter1] = chars[indLetter2];
            chars[indLetter2] = temp;
        }
        return new String(chars);
    }

    public char[][] encryptArray(int SQUARE, String fileString, int[] pattern) {
        char[][] arr = new char[SQUARE][SQUARE]; 
                                                            
        for (int j = 0; j < SQUARE; j++) {
            for (int i = 0; i < SQUARE; i++) {
                if (fileString.length() == 0) 
                {
                    break;
                }
                arr[i][pattern[j]] = fileString.charAt(0); 
                                                                      
                fileString = fileString.substring(1, fileString.length()); 
            }
        }
        return arr;
    }

    public int[] pattern(int hash, int size) {
        int[] pattern = new int[size];
        int i = 0;
        while (i < size){
            pattern[i] = i++;
        }
        Random random = new Random(hash); 
        for (i = 0; i < 100; i++) 
        {
            int indPattern1 = random.nextInt(8);
            int indPattern2 = random.nextInt(8);
            int tempPattern = pattern[indPattern1];
            pattern[indPattern1] = pattern[indPattern2];
            pattern[indPattern2] = tempPattern;
        }
        return pattern;
    }
}
