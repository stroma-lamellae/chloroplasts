package Course_Records;


import BasicIO.*;


/** This class is a test harness for unit testing of the StudentImpl class. It
  * requires a CourseStub as implementation for Course and a MarkingSchemeStub as
  * implementation for MarkingScheme. It creates the course (which creates the
  * MarkingScheme) and one Student object reading the student data from a text
  * file. It then calculates the final grades, does an update of the student and
  * calculates the final grades a second time.
  *
  * @author  D. Hughes
  *
  * @version 1.0 (July 2014)                                                     */


public class StudentTest {
    
    
    private Course         aCourse;   // course stub for testing
    private MarkingScheme  aScheme;   // marking scheme stub for testing
    private ASCIIDataFile  from;      // file for student data
    private Student        aStudent;  // student to test
    private int            numWork;   // number of pieces of work
    
    
    /** The constructor performs unit testing of the StudentImpl class.         */
    
    public StudentTest ( ) {
        
        aScheme = new MarkingSchemeStub();
        aCourse = new CourseStub(aScheme);
        numWork = aCourse.getScheme().getNumWork();
        from = new ASCIIDataFile();
        aStudent = new StudentImpl(from,aCourse);
        from.close();
        System.out.println();
        System.out.println("New Student created: "+aStudent);
        display();
        System.out.println();
        System.out.println("Calculate Final Grades");
        aStudent.calcFinalGrade();
        display();
        System.out.println();
        System.out.println("Update");
        aStudent.update();
        display();
        System.out.println();
        System.out.println("Calculate Final Grades");
        aStudent.calcFinalGrade();
        display();
        
    };  // constructor
    
    
    /** This method displays the data in the Student object to the console.     */
    
    private void display ( ) {
        
        System.out.println("Student: "+aStudent);
        System.out.println("    stNum:   "+aStudent.getStNum());
        System.out.println("    Name:    "+aStudent.getName());
        for ( int i=0; i<numWork ; i++ ) {
            System.out.println("    Mark["+i+"]: "+aStudent.getMark(i));
        };
        System.out.println("    Final:   "+aStudent.getFinalGrade());
        
    };  // display
    
    
    public static void main ( String[] args ) { StudentTest s = new StudentTest(); };
    
    
}  // StudentTest