package Course_Records;


import java.io.*;
import BasicIO.*;


/** This class represents a student in a course. A student has a student
  * number, a name and marks in a number of pieces of work. Student marks can be
  * updated and a final grade can be computed according to a marking scheme. 
  *
  * @see Course
  * @see MarkingScheme
  *
  * @author D. Hughes
  *
  * @version 1.0 (Jan. 2014)                                                     */

public class StudentImpl implements Student, Serializable {
    
    
    private static final long  serialVersionUID = 99990003L;
    
    private Course    theCourse;   // course student is in
    private String    stNum;       // student number
    private String    name;        // student's name
    private double[]  marks;       // marks
    private double    finalGrade;  // final grade
    
    
    /** This constructor creates a new student reading the student number and name
      * from a specified file and initializing the marks for the pieces of work and
      * final grade to unspecified (-1). If there are no more students in the file,
      * it returns and from.isEOF() will be true.
      * 
      * @param  from the file to read from
      * @param  c    the course the student is in.                               */
    
    public StudentImpl ( ASCIIDataFile from, Course c ) {
        
        theCourse = c;
        stNum = from.readString();
        name = from.readString();
        marks = new double[theCourse.getScheme().getNumWork()];
        for ( int i=0 ; i<marks.length ; i++ ) {
            marks[i] = -1;
        };
        finalGrade = -1;
          
    }; // constructor
    
    
    /** This method returns the student number of the student.
      * 
      * @return  String  the student number                                      */
    
    public String getStNum ( ) {
        
        return stNum;
        
    }; // getStNum
    
    
    /** This method returns the student's name.
      *
      * @return  String  the student's name                                      */
    
    public String getName ( ) {
        
        return name;
        
    }; // getName
    
    
    /** This method returns the student's mark in a piece of work. If a mark
      * hasn't been entered for the piece of work, it returns N_A.
      *
      * @param  num  piece of work number (from 0)
      *
      * @return  double  the student's mark                                      */
    
    public double getMark ( int num ) {
                
        return marks[num];
        
    }; // getMark
    
    
    /** This method returns the final grade for the student. If the final grade
      * has not yet been calculated it returns N_A.
      *
      * @return  double  the student's final grade                               */
    
    public double getFinalGrade ( ) {
        
        return finalGrade;
        
    }; // getFinalGrade
    
    
    /** This method calculates the final grade for the student by applying the
      * course marking scheme to the student's marks.                            */
    
    public void calcFinalGrade( ) {
        
        finalGrade = theCourse.getScheme().apply(this);
        
    }; // calcFinalGrade
    
    
    /** This method updates the student's marks for the pieces of work in the
      * marking scheme for the course.                                           */
    
    public void update ( ) {
        
        StudentForm  display;
        
        display = new StudentForm(this,theCourse.getScheme());
        if ( display.update() ) {
            for ( int i=0 ; i<marks.length ; i++ ) {
                marks[i] = display.readMark(i);
            };
        };
        display.close();
        
    }; // update
    
    
} // StudentImpl