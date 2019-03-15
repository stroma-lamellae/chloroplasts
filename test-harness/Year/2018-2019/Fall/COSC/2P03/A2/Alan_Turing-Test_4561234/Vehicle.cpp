/**
    * @author  Alan Turing-Test
    * @studentNum 4561234
    */

class Vehicle {
private:
std::string bumperSticker;
protected:
void becomeSentient(){std::cout<<"Why was this added?"<<std::endl;}
public:
int wheels; //Unicycle? Tricycle? Dodecacycle?
double clearance; //Distance between chassis and ground
Vehicle(int wheels=4, double clearance=18) : wheels(wheels), clearance(clearance) {}
int getWheels() {return wheels;}
double getClearance() {return clearance;}
void rollOut() {std::cout<<"Brockobots! Roll out!"<<std::endl;}
void recycle() {std::cout<<"You owe $45 for disposal."<<std::endl;}
void setBumper(std::string b) {bumperSticker=b;}
std::string getBumper() {return bumperSticker;}
};
