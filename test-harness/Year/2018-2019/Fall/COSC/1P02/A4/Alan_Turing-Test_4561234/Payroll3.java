package Example_12_1;


import java.util.*;
import BasicIO.*;
import static BasicIO.Formats.*;


/**
    * @author  Alan Turing-Test
    * @studentNum 4561234
    */

public class Payroll3 {


    private BinaryDataFile    empData;     // data file for employee info
    private BasicForm         display;     // form for user input
    private BinaryOutputFile  newEmpData;  // data file for updated emp info
    private ReportPrinter     report;      // printer for report


    /** The constructor does the weekly payroll for a small company generating a
      * report.                                                                  */

    public Payroll3 ( ) {

        Employee  anEmp;      // the employee
        double    hours;      // hours worked
        double    pay;        // employee's pay
        double    totPay;     // total pay
        double    totYTDPay;  // total year-to-date pay

        empData = new BinaryDataFile();
        display = new BasicForm();
        newEmpData = new BinaryOutputFile();
        report = new ReportPrinter(false);
        buildForm();
        setUpReport(new Date());
        totPay = 0;
        totYTDPay = 0;
        for ( ; ; ) {
            anEmp = (Employee)empData.readObject();
        if ( empData.isEOF() ) break;
            fillForm(anEmp);
            display.accept();
            hours = display.readDouble("hours");
            pay = anEmp.payForHours(hours);
            writeDetail(anEmp,hours,pay);
            newEmpData.writeObject(anEmp);
            totPay = totPay + pay;
            totYTDPay = totYTDPay + anEmp.getYTDPay();
        };
        writeSummary(totPay,totYTDPay);
        empData.close();
        newEmpData.close();
        display.close();
        report.close();

    };  // constructor

     private void drawTriangle() {

    double sideA;
    double sideB;
    double eAngle;
    double iAngle;

    sideA=30.0;
    sideB= 60.0;
    eAngle= 3*PI/4 ;
    rAngle= PI/2 ;


    donatello.penDown();
    donatello.forward(sideA);
    donatello.left(eAngle);
    donatello.forward();
    donatello.left(eAngle);
    donatello.forward(sideA);
    donatellor.left(rAngle);

  }; //drawTriangle

    /** This method builds the form for user input                               */

    private void buildForm ( ) {

        display.addTextField("empNum","Employee",8,10,10);
        display.setEditable("empNum",false);
        display.addTextField("empName","Name",20,10,40);
        display.setEditable("empName",false);
        display.addTextField("rate","Pay Rate",getCurrencyInstance(),6,10,70);
        display.setEditable("rate",false);
        display.addTextField("hours","Hours Worked",
                                              getDecimalInstance(1),6,10,100);
        display.addTextField("YTDPay","YTD Gross Pay",
                                             getCurrencyInstance(),11,10,130);
        display.setEditable("YTDPay",false);

    };  // buildForm


    /** This method fills in the fields of the form for the Employee.
      *
      * @param  anEmployee  employee for information                             */

    private void fillForm ( Employee anEmployee ) {

        display.clearAll();
        display.writeString("empNum",anEmployee.getEmpNum());
        display.writeString("empName",anEmployee.getEmpName());
        display.writeDouble("rate",anEmployee.getRate());
        display.writeDouble("YTDPay",anEmployee.getYTDPay());

    };  // fillForm


    /** This method sets up the report, adding all fields.
      *
      * @param  date  date for payroll report                                    */

    private void setUpReport ( Date date ) {

        report.setTitle("Timmy's Coffee Bar",getDateInstance().format(date));
        report.addField("empNum","Employee #",10);
        report.addField("empName","Name",20);
        report.addField("rate","Pay Rate",getCurrencyInstance(),9);
        report.addField("hours","Hours",getDecimalInstance(2),6);
        report.addField("pay","Total Pay",getCurrencyInstance(),11);
        report.addField("YTDPay","YTD Pay",getCurrencyInstance(),12);

    };  // setUpReport


    /** This method generates a report detail line.
      *
      * @param  anEmployee  the employee
      * @param  hours       hours worked
      * @param  pay         gross pay                                            */

    private void writeDetail ( Employee anEmployee, double hours, double pay ) {

        report.writeString("empNum",anEmployee.getEmpNum());
        report.writeString("empName",anEmployee.getEmpName());
        report.writeDouble("rate",anEmployee.getRate());
        report.writeDouble("hours",hours);
        report.writeDouble("pay",pay);
        report.writeDouble("YTDPay",anEmployee.getYTDPay());

    };  // writeDetail


    /** This method generates the report summary.
      *
      * @param  totPay     total pay for all employees
      *
      * @param  totYTDPay  total YTD pay for all employees                       */

    private void writeSummary ( double totPay, double totYTDPay ) {

        report.writeString("empNum","Total");
        report.writeDouble("pay",totPay);
        report.writeDouble("YTDPay",totYTDPay);

    };  // writeSummary


    public static void main ( String[] args ) { Payroll3 p = new Payroll3(); };


}  // Payroll3
