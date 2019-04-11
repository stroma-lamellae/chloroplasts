#incgilude <Ultrasonic.h>
#include "ultrasonic.h"
//#include "StateController.h"

/* Setup  */
const unsigned int L_Enable = 7;
const unsigned int R_Enable = 4;

const unsigned int L_Forward = 5;
const unsigned int L_Back = 3;
const unsigned int R_Forward = 6;
const unsigned int R_Back = 9;

const unsigned int F_L_QRD_PIN = A0;
const unsigned int F_R_QRD_PIN = A1;
const unsigned int B_L_QRD_PIN = A2;
const unsigned int B_R_QRD_PIN = A3;

const unsigned int SONAR_TX = 12;
const unsigned int SONAR_RX = 13;

const unsigned int QRD_THRESHOLD = 700;

int distance;

Ultrasonic ultrasonic(SONAR_TX, SONAR_RX); //Creates an Ultrasonic objects. 

void setup() {
	pinMode(L_Enable, OUTPUT);
	pinMode(R_Enable, OUTPUT);

	pinMode(L_Forward, OUTPUT);
	pinMode(L_Back, OUTPUT);
	pinMode(R_Forward, OUTPUT);
	pinMode(R_Back, OUTPUT);

	pinMode(F_L_QRD_PIN, INPUT);
	pinMode(F_R_QRD_PIN, INPUT);
	pinMode(B_L_QRD_PIN, INPUT);
	pinMode(B_R_QRD_PIN, INPUT);

	pinMode(SONAR_TX, OUTPUT);
	pinMode(SONAR_RX, INPUT);
	Serial.begin(9600);

	delay(5000);


}

/* Check QRD */
void checkQRD() {
	unsigned int F_L = (analogRead(F_L_QRD_PIN) < QRD_THRESHOLD) ? 1:0;
	unsigned int F_R = (analogRead(F_R_QRD_PIN) < QRD_THRESHOLD) ? 2:0;
	unsigned int B_L = (analogRead(B_L_QRD_PIN) < QRD_THRESHOLD) ? 4:0;
	unsigned int B_R = (analogRead(B_R_QRD_PIN) < QRD_THRESHOLD) ? 8:0;

	unsigned int qrd = 	F_L + F_R + B_R + B_L;

	switch(qrd) {
		case 1: //Front left QRD tripped | left forward and right backwards
			digitalWrite(L_Forward, HIGH);
			digitalWrite(L_Back, LOW);
			digitalWrite(R_Forward, LOW);
			digitalWrite(R_Back, HIGH);
			break;
		case 2: //Front right QRD tripped | right forward and left backwards
			digitalWrite(L_Forward, LOW);
			digitalWrite(L_Back, HIGH);
			digitalWrite(R_Forward, HIGH);
			digitalWrite(R_Back, LOW);
			break;
		case 3: //Front QRDs Tripped | reverse
			digitalWrite(L_Forward, LOW);
			digitalWrite(L_Back, HIGH);
			digitalWrite(R_Forward, LOW);
			digitalWrite(R_Back, HIGH);
			break;
		case 4: //Back left QRD tripped | left forward and right forward
			digitalWrite(L_Forward, HIGH);
			digitalWrite(L_Back, LOW);
			digitalWrite(R_Forward, HIGH);
			digitalWrite(R_Back, LOW);
			break;
		case 5: //Left QRDs tripped | left forward and right backwards
			digitalWrite(L_Forward, HIGH);
			digitalWrite(L_Back, LOW);
			digitalWrite(R_Forward, LOW);
			digitalWrite(R_Back, HIGH);
			break;
		case 8: //Back right QRD tripped | right forward and left forward
			digitalWrite(L_Forward, HIGH);
			digitalWrite(L_Back, LOW);
			digitalWrite(R_Forward, HIGH);
			digitalWrite(R_Back, LOW);
			break;
		case 10: //Right QRDs tripped |right forward and left backwards
			digitalWrite(L_Forward, LOW);
			digitalWrite(L_Back, HIGH);
			digitalWrite(R_Forward, HIGH);
			digitalWrite(R_Back, LOW);
			break;
		case 12: //Back QRDs tripped | forward
			digitalWrite(L_Forward, HIGH);
			digitalWrite(L_Back, LOW);
			digitalWrite(R_Forward, HIGH);
			digitalWrite(R_Back, LOW);
			break;
		default:  //Nothing tripped
			break;
	}
}


void UltrasonicDistance() {
	int distance = ultrasonic.Ranging(CM);

	if (distance < 50){
    	digitalWrite(L_Forward, HIGH);
    	digitalWrite(L_Back, LOW);
    	digitalWrite(R_Forward, HIGH);
    	digitalWrite(R_Back, LOW);
	}  
	else{
    	digitalWrite(L_Forward, HIGH);
    	digitalWrite(L_Back, LOW);
	    digitalWrite(R_Forward, LOW);
    	digitalWrite(R_Back, HIGH);
  	}
}

void loop() {
	UltrasonicDistance();
	checkQRD();
	delay(1000);
  

}