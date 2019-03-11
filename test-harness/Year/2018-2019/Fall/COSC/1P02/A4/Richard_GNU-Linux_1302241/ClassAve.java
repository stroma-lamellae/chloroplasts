package Example_9_1;


import BasicIO.*;


/** This class is a program to calculate a class average.
  *
  *@author  Richard GNU-Linux
  * @studentNum 1302241
  */

public class ClassAve {


    private ASCIIDisplayer  display;  // displayer for report
    private ASCIIPrompter   prompt;   // prompter for data input


    /** The constructor computes the class average, reading the students' marks,
      * computing the average and displaying the results.                        */

    public ClassAve ( ) {

        int     numStd;  // number of students
        double  sum;     // sum of marks
        double  mark;    // a student's mark
        double  ave;     // average mark

        display = new ASCIIDisplayer();
        prompt = new ASCIIPrompter();
        prompt.setLabel("# Students");
        numStd = prompt.readInt();
        prompt.setLabel("Mark");
        sum = 0;
        for ( int i=1 ; i<=numStd ; i++ ) {
            mark = prompt.readDouble();
            sum = sum + mark;
            display.writeDouble(mark);
            display.newLine();
        };
        ave = sum / numStd;
        display.writeString("Ave:");
        display.writeDouble(ave);
        display.newLine();
        display.close();
        prompt.close();

    };  // constructor


    public static void main ( String[] args ) { ClassAve c = new ClassAve(); };


}  // ClassAve
