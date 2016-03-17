
/* Turn an LED on/off based on a command send via BlueTooth
**
** Credit: The following example was used as a reference
** Rui Santos: http://randomnerdtutorials.wordpress.com
*/


int ledPin = 13;  // use the built in LED on pin 13 of the Uno
int state = 0;
int flag = 0;        // make sure that you return the state only once

int val;
int servoPin = 9;
int pulseWidth = 0;
long lastPulse = 0;    // the time in millisecs of the last pulse
int refreshTime = 20;  // the time in millisecs needed in between pulses
int minPulse = 700;   // minimum pulse width



#include <SoftwareSerial.h> //Software Serial Port
#define RxD 0
#define TxD 1

SoftwareSerial btSerial(RxD,TxD);


void setup() {
 
    // sets the pins as outputs:
   // pinMode(ledPin, OUTPUT);
    pinMode(servoPin, OUTPUT);
    pulseWidth = minPulse;
    digitalWrite(servoPin, HIGH);
    digitalWrite(ledPin, LOW);

    Serial.begin(9600); // Default connection rate for my BT module
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
    btSerial.begin(9600);

}




void loop() {
 /* 
    //if some data is sent, read it and save it in the state variable
    if(Serial.available() > 0){
      state = Serial.read();
      flag=0;
    }
    // if the state is 0 the led will turn off
    if (state == '0') {
        digitalWrite(ledPin, LOW);
        if(flag == 0){
          Serial.println("LED: off");
          flag = 1;
        }
    }
    // if the state is 1 the led will turn on
    else if (state == '1') {
        digitalWrite(ledPin, HIGH);
        if(flag == 0){
          Serial.println("LED: on");
          flag = 1;
        }
    }
    else if (state == '8') {
            
        if(flag == 0){
          Serial.println("took in 8");
          flag = 1;
        }
}
*/



 
  val = btSerial.read();
  // if the stored value is a single-digit number, blink the LED that number
 if (val >= '0' && val <= '9' ) {
    val = val - '0';       // convert from character to number
    val = val * (180/9);   // convert from number to degrees
    pulseWidth = (val * 9) + minPulse;  // convert angle to microseconds
    Serial.print("moving servo to ");
    Serial.print(pulseWidth,DEC);
    Serial.println();
 
  }
  updateServo();   // update servo position


}

void updateServo() {
  // pulse the servo again if rhe refresh time (20 ms) have passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    delayMicroseconds(pulseWidth);  // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    lastPulse = millis();           // save the time of the last pulse
  }
}
