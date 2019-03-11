package Exercise_7_1;

import BasicIO.*;


/** This class demonstrates the various widgets for BasciForm.
  *
  * @author D. Hughes
  *
  * @version 1.0 (Nov. 2011)                                                     */

public class E7 {
    
    
    private BasicForm        display;        // form for mark input/validation
    
    
    /** The constructor creates the basic form with a title and buttons.         */
    
    public E7 ( ) {
        
        int  button;  // button pressed
        String  v;       // value read
        
        display = new BasicForm("Write","Read","Quit");
        display.setTitle("Title");
        buildForm();
        for ( ; ; ) {
            button = display.accept();
        if ( button == 2 ) break;
            if ( button == 0 ) {  // Write
                display.writeDouble("cbx",0);
                display.writeDouble("rbn",1);
                display.writeDouble("txt",2);
                display.writeDouble("sld",3);
            }
            else {  // Read
                v = display.readString("cbx");
                display.writeLine("msg","Checkbox: "+v);
                v = display.readString("rbn");
                display.writeLine("msg","Radio Buttons: "+v);
                v = display.readString("txt");
                display.writeLine("msg","Text Field: "+v);
                v = display.readString("sld");
                display.writeLine("msg","Slider: "+v);
            };
        };
        display.close();
        
    };  // constructor
    
    
    /** This method builds the form with various widgets.                        */
    
    public void buildForm ( ) {
        
        display.addLabel("lbl","Label",10,10);
        display.addCheckBox("cbx","Checkbox",220,10);
        display.addRadioButtons("rbn","Radio Buttons",false,10,40,"0","1","2","3");
        display.addTextField("txt","Text Field",10,170,60);
        display.addSlider("sld","Slider",0,100,200,30,110);
        display.addTextArea("msg","Text Area",10,40,10,160);
        
    };  // buildForm
        
    
    public static void main ( String[] args ) { E7 e = new E7(); };
    
    
} //  E7