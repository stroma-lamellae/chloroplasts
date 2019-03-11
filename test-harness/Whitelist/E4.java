package Exercise_4_1;


/** This class demonstrates the action of various control
  ** structures.
  **
  ** @author D. Hughes & D. Bockus
  ** @author D. Hughes
  **
  ** @version 1.1 (Oct. 2002)
  ** @version 2.0 (Oct. 2010)
  ** @version 3.0 (Ict. 2011)                                                    */

public class E4 {
    
    
    /** The constructor demonstrates the action of various control structures.   */
    
    public E4 ( ) {
        
        int  k;
        int  m;
        
        // *************  Part I  *************
        System.out.println("Part I");
        k = 1;
        m = 16;
        while ( k < m ) {
            System.out.println(k);
            k = k + 1;
            m = m - 2;
        };
        System.out.println();
        
        // *************  Part II  *************
        System.out.println("Part II");
        k = 1;
        m = 16;
        if ( k < m ) {
            System.out.println(k);
            k = k + 1;
            m = m - 2;
        };
        System.out.println();
        
        // *************  Part III  *************
        System.out.println("Part III");
        for ( int i=1 ; i<5 ; i++ ) {
            for ( int j=2 ; j<=i ; j++ ) {
                System.out.println(j);
            };
        };
        System.out.println();
        
        // *************  Part IV  *************
        System.out.println("Part IV");
        for ( int i=10 ; i>0 ; i=i/2 ) {
            System.out.println(i);
        };
        System.out.println();
        
        // *************  Part V  *************
        System.out.println("Part V");
        k = 10;
        while( k>0 ) {
            System.out.println(k);
            k = k / 2;
        };
        System.out.println();
        
        // *************  Part VI  *************
        System.out.println("Part VI");
        k = 1;
        m = 10;
        while ( k < m ) {
            if ( k%2 == m%2 ) {
                k = k + 1;
            }
            else {
                m = m - 1;
            };
            System.out.println(k);
        };
        System.out.println();
        
        // *************  Part VII  *************
        System.out.println("Part VII");
        for ( int i=1 ; i<=5 ; i++ ); {
            System.out.println('x');
            System.out.println('y');
        };
        System.out.println();
        
        // *************  Part VIII  *************
        System.out.println("Part VIII");
        for ( int i=1 ; i<=5 ; i++ ) 
            System.out.println('x');
            System.out.println('y');
        System.out.println();
        
    }; // constructor
    
    
    public static void main ( String args[] ) { E4 e = new E4(); };
    
    
} // E4
