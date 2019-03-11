package Example_9_2;


import BasicIO.*;


/** This class is a program to calculate a class average.
    * @author  Ada Lovês
    * @studentNum 5012386
    */

public class ClassAve2 {


    private ASCIIDisplayer  display;  // displayer for report
    private ASCIIDataFile   stData;   // data file for student marks


    /** The constructor generates a report, reading the students' marks, computing
      * the average and displaying the results.                                  */

    public ClassAve2 ( ) {

        String  course;  // course name
        String  work;    // name of piece of work
        int     numStd;  // number of students
        double  sum;     // sum of marks
        String  stNum;   // student number
        double  mark;    // a student's mark
        double  ave;     // average mark

        display = new ASCIIDisplayer();
        stData = new ASCIIDataFile();
        course = stData.readString();
        work = stData.readString();
        writeHeader(course,work);
        numStd = stData.readInt();
        sum = 0;
        for ( int i=1 ; i<=numStd ; i++ ) {
            stNum = stData.readString();
            mark = stData.readDouble();
            sum = sum + mark;
            writeDetail(stNum,mark);
        };
        ave = sum / numStd;
        writeSummary(ave);
        display.close();
        stData.close();

    };  // constructor


    /** This method generates the report header.
      *
      * @param  courseName  name of the course
      * @param  workName    name of the piece of work                            */

    private void writeHeader ( String courseName, String workName ) {

        display.writeString(courseName);
        display.newLine();
        display.writeString(workName);
        display.newLine();
        display.newLine();

    };  // writeHeader


    /** This method generates a report detail line.
      *
      * @param  stNum  student number
      * @param  mark   mark                                                      */

    private void writeDetail ( String stNum, double mark ) {

        display.writeString(stNum);
        display.writeDouble(mark,5,1);
        display.newLine();

    };  // writeDetail


    /** This method generates the report summary.
      *
      * @param  average  average mark in course                                  */

    private void writeSummary ( double average ) {

        display.writeString("Ave:  ");
        display.writeDouble(average,5,1);
        display.newLine();

    };  // writeSummary


    public static void main ( String[] args ) { ClassAve2 c = new ClassAve2(); };


}  // ClassAve2
