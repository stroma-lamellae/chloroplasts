package Example_9_5;


import java.util.*;
import BasicIO.*;
import static BasicIO.Formats.*;




public class Payroll {


    private ASCIIDataFile    empData;     // data file for employee info
    private ASCIIPrompter    prompt;      // prompter for user input
    private ASCIIOutputFile  newEmpData;  // data file for updated emp info
    private ReportPrinter    report;      // printer for report

    /**
    * @author  Ada Lovês
    * @studentNum 5012386
    */

    public Payroll ( ) {

        String  empNum;     // employee number
        String  empName;    // employee name
        double  rate;       // pay rate
        double  hours;      // hours worked
        double  pay;        // employee pay
        double  YTDPay;     // employee year-to-date pay
        double  totPay;     // total pay
        double  totYTDPay;  // total year-to-date pay

        empData = new ASCIIDataFile();
        prompt = new ASCIIPrompter();
        newEmpData = new ASCIIOutputFile();
        report = new ReportPrinter(false);
        setUpReport(new Date());
        totPay = 0;
        totYTDPay = 0;
        for ( ; ; ) {
            empNum = empData.readString();
        if ( empData.isEOF() ) break;
            empName = empData.readString();
            rate = empData.readDouble();
            YTDPay = empData.readDouble();
            prompt.setLabel(empNum);
            hours = prompt.readDouble();
            pay = calcPay(hours,rate);
            YTDPay = YTDPay + pay;
            writeDetail(empNum,empName,rate,hours,pay,YTDPay);
            writeEmpData(empNum,empName,rate,YTDPay);
            totPay = totPay + pay;
            totYTDPay = totYTDPay + YTDPay;
        };
        writeSummary(totPay,totYTDPay);
        empData.close();
        newEmpData.close();
        prompt.close();
        report.close();

    };  // constructor


    /** This method computes the gross pay for an employee
      *
      * @param hours  hours worked
      * @param rate   pay rate
      *
      * @return  double  gross pay                                               */

    private double calcPay ( double hours, double rate ) {

        double  pay;  // gross pay
        if ( hours > 40.0 ) {
            pay = 40.0 * rate + ( hours - 40.0 ) * rate * 1.5;
        }
        else {
            pay = hours * rate;
        }
        return pay;

    };  // calcPay


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
      * @param  empNum  employee number
      * @param  rate    pay rate
      * @param  hours   hours worked
      * @param  pay     total pay
      * @param  YTDPay  year-to-dat pay                                          */

    private void writeDetail ( String empNum, String empName, double rate,
                               double hours, double pay, double YTDPay ) {

        report.writeString("empNum",empNum);
        report.writeString("empName",empName);
        report.writeDouble("rate",rate);
        report.writeDouble("hours",hours);
        report.writeDouble("pay",pay);
        report.writeDouble("YTDPay",YTDPay);

    };  // writeDetail

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

    /** This method generates the report summary.
      *
      * @param  totPay     total pay for all employees
      * @param  totYTDPay  total YTD pay for all employees                       */

    private void writeSummary ( double totPay, double totYTDPay ) {

        report.writeString("empNum","Total");
        report.writeDouble("pay",totPay);
        report.writeDouble("YTDPay",totYTDPay);

    };  // writeSummary


    /** This method writes the updated employee data to the new employee file.
      *
      * @param  empNum  the employee number
      * @param  empName  employee name
      * @param  rate     pay rate
      * @param  YTDPay   year-to-date pay                                        */

    private void writeEmpData ( String empNum, String empName, double rate,
                                double YTDPay ) {

            newEmpData.writeString(empNum);
            newEmpData.writeString(empName);
            newEmpData.writeDouble(rate);
            newEmpData.writeDouble(YTDPay);
            newEmpData.newLine();

    };  // writeEmpData


    public static void main ( String[] args ) { Payroll p = new Payroll(); };


}  // Payroll
