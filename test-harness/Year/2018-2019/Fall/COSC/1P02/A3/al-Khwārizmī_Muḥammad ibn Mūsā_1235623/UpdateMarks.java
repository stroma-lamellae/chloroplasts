package Course_Records;


import BasicIO.*;


/** This class is an implementation of a mark updating program for a university
  * course. It allows the user to enter student numbers and selectively update
  * the marks for the selected students.
  *  @author al-Khwārizmī Muḥammad ibn Mūsā
  * @studentNum  1235623
*/

public class UpdateMarks {


    /** The constructor reads the course from the course file and allows the user
      * to select students to update marks.                                      */

    public UpdateMarks ( ) {

        BinaryDataFile     courseData;     // input file for course data
        BinaryOutputFile   newCourseData;  // output file for updated course data
        Course             aCourse;        // course being processed
        CourseForm         form;           // form for display
        MarkingScheme      scheme;         // the marking scheme
        MarkingSchemeForm  mform;          // form for MS display
        BasicForm          prompt;         // form top prompt for student number
        int                button;         // button pressed
        Student            aStudent;       // student being updated

        courseData = new BinaryDataFile();
        aCourse = (Course)courseData.readObject();
        courseData.close();
        form = new CourseForm(aCourse);
        if ( form.confirm() ) {
            scheme = aCourse.getScheme();
            mform = new MarkingSchemeForm(scheme);
            mform.display();
            mform.close();
            prompt = new BasicForm();
            prompt.addTextField("sn","Student #",6);
            for ( ; ; ) {
                prompt.clearAll();
                button = prompt.accept("OK","Quit");
                prompt.hide();
            if ( button == 1 ) break;
                aStudent = aCourse.getStudent(prompt.readString("sn"));
                if ( aStudent != null ) {
                    aStudent.update();
                };
            };
            newCourseData = new BinaryOutputFile();
            newCourseData.writeObject(aCourse);
            newCourseData.close();
        };
        form.close();

    }; // constructor


    private void setUpForm ( ) {

        usageForm.setTitle("Over The Horizon Utilities");
        usageForm.addTextField("acctNum","Account #",getIntegerInstance(),
                               6,10,10);
        usageForm.addTextField("name","Name",20,10,40);
        usageForm.addTextField("prev","Previous Reading",getDecimalInstance(1),
                               6,10,70);
        usageForm.addTextField("reading","Current Reading",getDecimalInstance(1),
                               6,10,100);

    };  // setUpForm


    public static void main ( String[] args ) { UpdateMarks u = new UpdateMarks(); };


} // UpdateMarks
