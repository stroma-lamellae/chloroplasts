package E8;

/**
 * @author  Alan Turing-Test
 * @studentNum 4561234
 */

public class PermutationGenerator {

    private int numPermutations;
    private int MAX_PERMUTATIONS = 10000;
    private String[] permutations;

    public PermutationGenerator(String s) {
        permutations = new String[MAX_PERMUTATIONS];
        permute(s.toCharArray(),s.length());
    }

    public void printPermutations() {
        for (int i=0;i<numPermutations;i++) {
            System.out.println(permutations[i]);
        }

    }

    private void permute(char[] a, int length) {
        if (length == 1) {
            permutations[numPermutations++] = new String(a);
            return;
        }

        for (int i = 0; i < length; i++) {
           swap(a, i, length-1);
           permute(a, length-1);
           swap(a, i, length-1);
        }
    }

    private void swap(char[] a, int i, int j) {
        char c;
        c = a[i];
        a[i] = a[j];
        a[j] = c;
    }




}
