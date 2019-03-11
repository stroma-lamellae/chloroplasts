package Exercise_5_1;


/** Lab 6 examines boolean expressions.
  **
  ** @author Dave Hughes
  **
  ** @version 1.0 (Oct. 2012)                                                    */

public class E5 {
    
    
    public E5 ( ) {
        
        boolean b1, b2;
        int  i, j, k;
        
        b1 = true;
        b2 = false;
        
// part 1: which is most appropriate?
        System.out.println("*************  Part 1 ************");
        if ( b1 == true ) {
            System.out.println("b1 is true with equals");
        };
        // or
        if ( b1 ) {
            System.out.println("b1 is true without equals");
        };
        
// part 2: which is most appropriate?
        System.out.println("*************  Part 2 ************");
        if ( b2 == false ) {
            System.out.println("b2 is false with equals");
        };
        // or
        if ( ! b2 ) {
            System.out.println("b2 is false with not");
        };
        
// part 3: which of the following will print "TRUE"?
        System.out.println("*************  Part 3 ************");
        if( ! (b1 & b2) ) {
            System.out.println("One not: TRUE");
        };
        // or
        if ( ! b1 & ! b2 ) {
            System.out.println("Two nots: TRUE");
        };
        
// part 4: which stops when i is negative or j is negative?
        System.out.println("*************  Part 4 ************");
        i = 10;
        j = 4;
        while ( i >= 0 & j >= 0 ) {
            System.out.println("i: "+i+" j: "+j);
            i = i - 2;
            j = j - 1;
        };
        System.out.println("after: i: "+i+" j: "+j);
        // or
        i = 10;
        j = 4;
        while ( i >= 0 | j >= 0 ) {
            System.out.println("i: "+i+" j: "+j);
            i = i - 2;
            j = j - 1;
        };
        System.out.println("after: i: "+i+" j: "+j);
        
// part 5: which displays i only when i is between 3 and 8?
       System.out.println("*************  Part 5 ************");
        for ( i=1 ; i<=10 ; i++ ) {
            if ( i > 3 | i < 8 ) {
                System.out.println("i: "+i);
            };
        };
        // or
        for ( i=1 ; i<=10 ; i++ ) {
            if ( i > 3 & i < 8 ) {
                System.out.println("i: "+i);
            };
        };
        
        
// part 6: what is the output of each code fragment?
        System.out.println("*************  Part 6 ************");
        i=3;
        j=6;
        k=8;
        while (j <= 10){
            if ( i==j/3 | !(j >= 7 && j <= k)){
                System.out.println("i: "+i+" j: "+j+" k: "+k);
            };
            j++;
        };
        //or
        System.out.println("....");
        
        i=3;
        j=6;
        k=8;
        while (j <= 10){
            if ( i==j/3 | j < 7 | j > k){
                System.out.println("i: "+i+" j: "+j+" k: "+k);
            };
            j++;
        };  
        
        
// part 7: which runs without crashing?
        System.out.println("*************  Part 7 ************");
        i = 8;
        j = 5;
        while ( j != 0 && Math.abs(i/j) >= 1 ) {
            System.out.println("i: "+i+" j: "+j);
            j = j - 1;
            i = i - 1;
        };
        System.out.println("first part");
        // or
        i = 8;
        j = 5;
        while ( j != 0 & Math.abs(i/j) >= 1 ) {
            System.out.println("i: "+i+" j: "+j);
            j = j - 1;
            i = i - 1;
        };
        System.out.println("second part");
        
        
    }; // constructor
    
    
    public static void main ( String args[] ) { E5 e = new E5(); };
    
    
} // E5

