package Billing;


import BasicIO.*;
import static BasicIO.Formats.*;

/**
    * @author  Richard GNU-Linux
    * @studentNum 1302241
    */

public class Update {

    /* Instance Variables */
    private BasicForm        usageForm;  // meter reading form
    private Account          recognizer;

    public Update ( ) {

      ASCIIDataFile   accountData;
      int             button;
      String          expr;

      accountData = new ASCIIDataFile();
      recognizer = new Account(accountData);
      accountData.close();
      form = new BasicForm("Update");
      setupForm();
      for(;;){
        form.clearAll();
        button = form.accept();
        expr = form.readString("expr");
        if ( recognizer.recognize(expr) == True){

        }
      }
      form.close();


    };  // construtor


    private void loadAccts ( ) {


    };  // loadAccts


    private void writeAccts ( ) {


    };  // writeAccts


    private Account findAcct ( String acctNum ) {


    };  // findAcct


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


    private void fillForm ( Account anAcct ) {


    };  // fillForm


    public static void main ( String[] args ) { Update u = new Update(); };


}  // Update
