package Example_9_4;


import BasicIO.*;
import static BasicIO.Formats.*;


/** This class is a program to calculate a class average.
  *
  * @author al-Khwārizmī Muḥammad ibn Mūsā
  * @studentNum  1235623
*/

public class ClassAve4 {


    private ReportPrinter  report;   // printer for report
    private ASCIIDataFile  stData;   // data file for student marks


    /** The constructor generates a report, reading the students' marks, computing
      * the average and displaying the results.                                  */

    public ClassAve4 ( ) {

        String  course;  // course name
        String  work;    // name of piece of work
        int     numStd;  // number of students
        double  sum;     // sum of marks
        String  stNum;   // student number
        double  mark;    // a student's mark
        double  ave;     // average mark

        report = new ReportPrinter();
        stData = new ASCIIDataFile();
        course = stData.readString();
        work = stData.readString();
        setUpReport(course,work);
        numStd = 0;
        sum = 0;
        for ( ; ; ) {
            stNum = stData.readString();
        if ( stData.isEOF() ) break;
            numStd = numStd + 1;
            mark = stData.readDouble();
            sum = sum + mark;
            writeDetail(stNum,mark);
        };
        ave = sum / numStd;
        writeSummary(ave);
        report.close();
        stData.close();

    };  // constructor


    /** This method sets up the report, adding all fields.
      *
      * @param  courseName  name of the course
      * @param  workName    name of the piece of work                            */

    private void setUpReport ( String courseName, String workName ) {

        report.setTitle(courseName,workName);
        report.addField("stNum","Student #",10);
        report.addField("mark","Mark",getDecimalInstance(1),5);

    };  // setUpReport


    /** This method generates a report detail line.
      *
      * @param  stNum  student number
      * @param  mark   mark                                                      */

    private void writeDetail ( String stNum, double mark ) {

        report.writeString("stNum",stNum);
        report.writeDouble("mark",mark);

    };  // writeDetail


    /** This method generates the report summary.
      *
      * @param  average  average mark in course                                  */

    private void writeSummary ( double average ) {

        report.writeString("stNum","Average");
        report.writeDouble("mark",average);

    };  // writeSummary


    public static void main ( String[] args ) { ClassAve4 c = new ClassAve4(); };


}  // ClassAve4
