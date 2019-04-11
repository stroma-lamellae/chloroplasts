import java.util.*;
import java.io.*;

public class Decrypt {
    public static void main(String args[]) throws IOException {
        final File in = new File("input.txt");
        final String outFile = "output.txt";
        final String key = "MYKEY";
        final int SIZE = 8;
        int hash = key.hashCode();
        Scanner scanner = new Scanner(in);
        String fileString = "";

        while (scanner.hasNext()) {
            fileString += scanner.nextLine().toUpperCase();
        }

        String origAlphabet = createAlphabet();
        String alphabet = alphabetEncryptor(hash, origAlphabet);

        int[] pattern = pattern(hash, SIZE);

        String encryptedString = "";

        while (fileString.length() != 0 || fileString.length() != -1) {
            char[][] encrypted = encryptedArray(SIZE, fileString, pattern);
            if (fileString.length() >= 64) {
                fileString = fileString.substring((SIZE * SIZE), fileString.length());
            } else {
                fileString = "";
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    encryptedString += encrypted[i][j];
                }
            }
        }
        String decryptedString = "";
        while (encryptedString.length() > 0) {
            decryptedString += origAlphabet.charAt(alphabet.indexOf(encryptedString.charAt(0)));
            encryptedString = encryptedString.substring(1, encryptedString.length());
        }
        System.out.println(decryptedString);

        PrintWriter out = new PrintWriter(outFile);
        out.println(decryptedString);
        out.close();
    }

    public static String createAlphabet() {
        return "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    }

    /**
     * This method does a thing
     */
    public static String alphabetEncryptor(int hash, String alphabet) {
        Random random = new Random(hash);
        for (int i = 0; i < 100; i++) {
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
     * Here we create a pattern
     */
    public static int[] pattern(int hash, int size) {
        int[] pattern = new int[size];
        for (int i = 0; i < size; i++) {
            pattern[i] = i;
        }
        Random random = new Random(hash);
        for (int i = 0; i < 100; i++) {
            int indPattern1 = random.nextInt(8);
            int indPattern2 = random.nextInt(8);
            int tempPattern = pattern[indPattern1];
            pattern[indPattern1] = pattern[indPattern2];
            pattern[indPattern2] = tempPattern;
        }
        return pattern;
    }

    // And here we make an encrypted array
    public static char[][] encryptedArray(int SQUARE, String fileString, int[] pattern) {
        char[][] encryptedArray = new char[SQUARE][SQUARE];
        // Looping algorithm
        for (int j = 0; j < SQUARE; j++) {
            for (int i = 0; i < SQUARE; i++) {
                if (fileString.length() != 0) {
                    encryptedArray[i][pattern[j]] = fileString.charAt(0);
                    fileString = fileString.substring(1, fileString.length());
                } else {
                    break;
                }

            }
        }
        return encryptedArray;
    }
}
