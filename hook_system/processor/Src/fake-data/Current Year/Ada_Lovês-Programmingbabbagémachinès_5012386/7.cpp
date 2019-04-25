// This is the source file for the Morse library.

#include "Morse.h"
#include <Wire.h>

// Constructor creation
MorseCode::MorseCode(int buttonPin, int ledPinInput, int ledPinOutput, int eepromPin) {
  // Set pins to either an input or an output
  pinMode(eepromPin, OUTPUT);
  pinMode(ledPinOutput, OUTPUT);
  pinMode(ledPinInput, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Turn on EEPROM's write protect
  digitalWrite(eepromPin, HIGH);

  // Create variables to ensure that the user does not accidentally change their value at another location
  _buttonPin = buttonPin;
  _ledPinInput = ledPinInput;
  _ledPinOutput = ledPinOutput;
  _eepromPin = eepromPin;
  _EEPROMI2Caddress = 0x50;

}//Close constructor


///////////////////////////////////////////////////////////////////////////////////////
// buttonPress()	      							     // 
///////////////////////////////////////////////////////////////////////////////////////
// Check if the user is pressing the button or not, and determine the appropriate symbol based on the elapsed time

char MorseCode::buttonPress() {
  //Initialize variables
  int buttonDownTime = 0;
  int buttonReleaseTime = 0;
  int holdTime = 0;
  int initialTime = 0;
  int buttonUpTime = 0;
  int releasedTime = 0;
  int buttonState = 0;
  char DatByte_in = "";

  //Check button state
  buttonState = digitalRead(_buttonPin);
  initialTime = millis(); // Take current time

  // While button is not pressed remain in this loop
  while (buttonState == LOW) {
    buttonUpTime = millis(); // Record next time
    buttonState = digitalRead(_buttonPin); // Check state of button to check loop condition

    releasedTime = buttonUpTime - initialTime; // Determine elapsed time
    if ((releasedTime) >= 2000) {
      DatByte_in = '/';  // If user hasn’t pressed the button in 2 seconds, add a space character
      break;
    }
  }

  // Button is pressed
  if (buttonState == HIGH)
  {
    buttonDownTime = millis();// Record current time

    digitalWrite(_ledPinInput, HIGH); // Turn LED on
    while (buttonState == HIGH) {
      buttonState = digitalRead(_buttonPin);
      buttonReleaseTime = millis(); // Record second time
      holdTime = buttonReleaseTime - buttonDownTime; // Determine elapsed time

      // If button is held for more than 2 seconds, terminate the current message
      if (holdTime >= 2000) {
        Serial.println("");
        Serial.println("End Transmission");
        break;
      }
    }
  }
  // Turn input light off
  digitalWrite(_ledPinInput, LOW); // Turn LED off

  // Check duration of button hold
  if ((holdTime) > 0 && (holdTime) <= 200) {   // A hold time of <200 ms inputs a ‘dot’
    DatByte_in = '.';
  }
  else if ((holdTime) > 200 && (holdTime) < 2000) {    // A hold time of >200ms but less than <2000ms inputs a ‘dash’
    DatByte_in = '-';
  }
  else if (holdTime >= 2000) {   // A hold time >2000ms inputs a ‘!’ which will be used to terminate the transmission
    return '!';
  }
  return DatByte_in; //Return value based on how long the button was pressed (holdTime)
}

///////////////////////////////////////////////////////////////////////////////////////
// writeEEPROM()								     // 
///////////////////////////////////////////////////////////////////////////////////////
// Write the character obtained from buttonPressed to the EEPROM. 
// Each character is stored to a different address.

void MorseCode::writeEEPROM(int MEMLOCATIONaddr, char DatByte_in) {
  char DatByte_out;
  int test = 0;

  digitalWrite(_eepromPin, LOW); // Enable the EEPROM by setting WP pin low
  delay(10);

  Wire.beginTransmission(_EEPROMI2Caddress); // Call the EEPROM

  // Send the address in the eeprom we want to write too (its 16 bits or two bytes long)
  Wire.write((int)(MEMLOCATIONaddr >> 8)); // MSB
  Wire.write((int)(MEMLOCATIONaddr & 0xFF)); // LSB

  Wire.write(DatByte_in); // Write the byte we want to write to

  Wire.endTransmission(); // Stop the call to the EEPROM

  //Turn back on the EEPROM's WP by setting D3 High
  digitalWrite(_eepromPin, HIGH);
  delay(5);

  Wire.beginTransmission(_EEPROMI2Caddress); // Call the EEPROM

  // Send it the address we want to read from
  Wire.write((int)(MEMLOCATIONaddr >> 8)); // MSB
  Wire.write((int)(MEMLOCATIONaddr & 0xFF)); // LSB
  
  Wire.endTransmission(); // Hang up and let the EEPROM prepare a response

  Wire.requestFrom(_EEPROMI2Caddress, 1); // Ask for a byte back and wait here for a response
  test = Wire.available();
  if (test) {
    DatByte_out = Wire.read();
  }

  // Print input and location on EEPROM
  Serial.print("Wrote '" );
  Serial.print(DatByte_in);
  Serial.print("' to address '0x");
  Serial.print(MEMLOCATIONaddr, HEX);
  Serial.print("' of an I2C EEPROM with an address of '0x");
  Serial.print(_EEPROMI2Caddress, HEX);
  Serial.print("' Read back '");
  Serial.print(DatByte_out);
  Serial.println("'");
}

///////////////////////////////////////////////////////////////////////////////////////
// letEndTransmission() 							     //
///////////////////////////////////////////////////////////////////////////////////////
// Turn led lights on and off to signal end of transmission

void MorseCode::ledEndTransmission() {
  delay(500);
  digitalWrite(_ledPinOutput, HIGH); // Turn LED on
  digitalWrite(_ledPinInput, HIGH); // Turn LED on
  delay(100);

  delay(100);
  digitalWrite(_ledPinOutput, LOW); // Turn LED off
  digitalWrite(_ledPinInput, LOW); // Turn LED off
  delay(100);

  delay(100);
  digitalWrite(_ledPinOutput, HIGH); // Turn LED on
  digitalWrite(_ledPinInput, HIGH); // Turn LED on
  delay(100);

  delay(100);
  digitalWrite(_ledPinOutput, LOW); // Turn LED off
  digitalWrite(_ledPinInput, LOW); // Turn LED off
  delay(100);
}

///////////////////////////////////////////////////////////////////////////////////////
// printMessage() 								     //
///////////////////////////////////////////////////////////////////////////////////////
// Print message to the serial monitor and translate the Morse Code to english letters or numbers

void MorseCode::printMessage(int MEMLOCATIONaddr, char DatByte_out) {
  int counter = MEMLOCATIONaddr;
  MEMLOCATIONaddr = 0;
  String translationString = "";
  int test = 0;

  Serial.print("The message is: ");
  //  Reprint Message
  while (MEMLOCATIONaddr <= counter - 1) {
  
    Wire.beginTransmission(_EEPROMI2Caddress); // Start transmission with EEPROM

    // send it the address we want to read from
    Wire.write((int)(MEMLOCATIONaddr >> 8)); // MSB
    Wire.write((int)(MEMLOCATIONaddr & 0xFF)); // LSB

    Wire.endTransmission(); // Hang up and let the EEPROM prepare a response

    Wire.requestFrom(_EEPROMI2Caddress, 1); // Ask for a byte back and wait here for a response
    test = Wire.available();
    if (test) {
      DatByte_out = Wire.read();
    }

    Serial.print(DatByte_out); // Print character stored at EEPROM address

    digitalWrite(_ledPinOutput, HIGH); // Turn LED on
    if (DatByte_out == '.') {
      delay(300); // Delay 300 ms if the character is a dot
    }
    else if (DatByte_out == '-') {
      delay(1100); // Delay 1100 ms if the character is a dash
    }
    digitalWrite(_ledPinOutput, LOW); //Turn LED off
    delay(200);
    MEMLOCATIONaddr++; // Move to next address

    if (DatByte_out == '.')
      DatByte_out == " ";
    
    translationString = translationString + DatByte_out; // Add current character to existing string
  }

  // Format serial monitor
  Serial.println("");
  translate(translationString, counter); // Send the current string to the translate function
  Serial.println("");
  Serial.println("");

  delay(1000);
  MEMLOCATIONaddr = 0; // Reset location to zero
}

///////////////////////////////////////////////////////////////////////////////////////
// translate()									     //
///////////////////////////////////////////////////////////////////////////////////////
// Translate morse code message into smaller morse code sequences that represent individual letters

void MorseCode::translate(String morseString, int counter) {
  int i = 0;
  String letter = "";

  Serial.print("This translates to: ");
  while (1) {
    while (1) {

      if (morseString[i] == '-') {
        letter = letter + morseString[i];
        i++;
      }
      else if (morseString[i] == '.') {
        letter = letter + morseString[i];
        i++;
      }
      else {
        break;
      }
    }
    letterMorse(letter); // Send Morse Code to letterMorse to obtain the equivalent English character
    //    Serial.println(letter);
    letter = "";
    i++;

    if (i >= counter) {
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////
// letterMorse() 							             //
///////////////////////////////////////////////////////////////////////////////////////
// Convert series of dot/dash to english characters

void MorseCode::letterMorse(String morse)
{
  // Letters

  if (morse == ".-")
    Serial.print("A");
  else if (morse == "-...")
    Serial.print("B");
  else if (morse == "-.-.")
    Serial.print("C");
  else if (morse == "-..")
    Serial.print("D");
  else if (morse == ".")
    Serial.print("E");
  else if (morse == "..-.")
    Serial.print("F");
  else if (morse == "--.")
    Serial.print("G");
  else if (morse == "....")
    Serial.print("H");
  else if (morse == "..")
    Serial.print("I");
  else if (morse == ".---")
    Serial.print("J");
  else if (morse == "-.-")
    Serial.print("K");
  else if (morse == ".-..")
    Serial.print("L");
  else if (morse == "--")
    Serial.print("M");
  else if (morse == "-.")
    Serial.print("N");
  else if (morse == "---")
    Serial.print("O");
  else if (morse == ".--.")
    Serial.print("P");
  else if (morse == "--.-")
    Serial.print("Q");
  else if (morse == ".-.")
    Serial.print("R");
  else if (morse == "...")
    Serial.print("S");
  else if (morse == "-")
    Serial.print("T");
  else if (morse == "..-")
    Serial.print("U");
  else if (morse == "...-")
    Serial.print("V");
  else if (morse == ".--")
    Serial.print("W");
  else if (morse == "-..-")
    Serial.print("X");
  else if (morse == "-.--")
    Serial.print("Y");
  else if (morse == "--..")
    Serial.print("Z");

  // Numbers

  else if (morse == ".----")
    Serial.print("1");
  else if (morse == "..---")
    Serial.print("2");
  else if (morse == "...--")
    Serial.print("3");
  else if (morse == "....-")
    Serial.print("4");
  else if (morse == ".....")
    Serial.print("5");
  else if (morse == "-....")
    Serial.print("6");
  else if (morse == "--...")
    Serial.print("7");
  else if (morse == "---..")
    Serial.print("8");
  else if (morse == "----.")
    Serial.print("9");
  else if (morse == "-----")
    Serial.print("0");
  else
    Serial.print(" ");

  Serial.print("");
  morse = ""; // Reset variable to null
}
