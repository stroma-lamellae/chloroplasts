package Course_Records;


import BasicIO.*;


/** This class represents the user interface (a form) for update and display of
  * student information.
  * 
  * @see Student
  * @see MarkingScheme
  * 
  * @author D. Hughes
  * 
  * @version 1.0 (Jan. 2014)                                                     */

class StudentForm {
    
    
    private BasicForm  display;     // form for display
    private Student    theStudent;  // student being displayed
    private int        numWork;     // number of pieces of work
    
    
    /** This constructor builds the form to display and/or update the student's
      * marks in the pieces of work of the marking scheme.
      * 
      * @param  aStudent  student to be displayed
      * @param  scheme    marking scheme                                         */
    
    public StudentForm ( Student aStudent, MarkingScheme aScheme ) {
        
        int  row;  // pixel row position
        
        theStudent = aStudent;
        display = new BasicForm();
        display.addLabel("sn",aStudent.getStNum(),10,10);
        display.addLabel("nm",aStudent.getName(),70,10);
        row = 40;
        numWork = aScheme.getNumWork();
        for ( int i=0 ; i<aScheme.getNumWork() ; i++ ) {
            display.addTextField("n"+i,10,10,row);
            display.writeString("n"+i,aScheme.getName(i));
            display.setEditable("n"+i,false);
            display.addTextField("m"+i,5,100,row);
            row = row + 30;
        };
        display.addTextField("fm","Final Mark  ",5,10,row);
        display.setEditable("fm",false);
        
    }; // constructor
    
    
    /** This method returns the mark in the specified mark field.
      * 
      * @param i workpiece number to read                                        */
    
    public double readMark ( int i ) {
        
        double  mark;
        
        if ( display.readString("m"+i).equals("N/A") ) {
            mark = -1;
        }
        else {
            mark = display.readDouble("m"+i);
        };
        return mark;
        
    };  // readMark
    
    
    /** This method presents the form to allow update of student information. It
      * returns true if the user requests an update (pressing Update). If Update
      * was pressed the values of the fields can be read.
      * 
      * @param  aStudent  student info to be updated
      * 
      * @return  boolean  user pressed Update                                    */
    
    public boolean update ( ) {
        
        int  button;  // button pressed
        
        fillForm();
        button = display.accept("Update","Skip");
        display.hide();
        return button == 0;
        
    };  // update
    
    
    /** This method closes the form. The form should no longer be used.          */
    
    public void close ( ) {
        
        display.close();
        
    };  // close
    
    
    /** This method fills the form to display the student mark information.
      * 
      * @param  student  student being displayed                                 */
    
    private void fillForm ( ) {
        
        double  mark;
        
        for ( int i=0 ; i<numWork ; i++ ) {
            mark = theStudent.getMark(i);
            if ( mark == -1 ) {
                display.writeString("m"+i,"N/A");
            }
            else {
                display.writeDouble("m"+i,mark);
            };
        };
        mark = theStudent.getFinalGrade();
        if ( mark == -1 ) {
            display.writeString("fm","N/A");
        }
        else {
            display.writeDouble("fm",mark);
        };

    }; // fillForm
    
    
}  // StudentForm