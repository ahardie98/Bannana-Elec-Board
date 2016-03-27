  /* 1 - GND 
   2 - VCC 3.3V 
   WARNING SHOULD BE 3.3v Not 5V 
   3 - CE - Arduino pin 9
   4 - CSN - Arduino pin 10
   5 - SCK - Arduino pin 13
   6 - MOSI - Arduino pin 11
   7 - MISO - Arduino pin 12
   8 - UNUSED */
 
/*----- Import all required Libraries -----*/
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
/*----- Declare all constant pin to be used ----*/
 
#define CE_PIN   9
#define CSN_PIN 10
 
const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module
 
 
/*-----Object Declaration ----*/
 
RF24 radio(CE_PIN, CSN_PIN); // Activate the Radio
 
/*-----Declaration of Variables -----*/
 
int joystick[2];  //  Two element array holding the Joystick readings
int servoPin = 8; //
int pulseWidth = 0;
long lastPulse = 0;    // the time in millisecs of the last pulse
int refreshTime = 20;  // the time in millisecs needed in between pulses
int minPulse = 700;   // minimum pulse width

void setup()  
{
  pinMode(servoPin, OUTPUT);
  pulseWidth = minPulse;
  digitalWrite(servoPin, HIGH);
  
  Serial.begin(9600); /* Opening the Serial Communication */
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();;
}//--(end setup )---
 
 
void loop()   
{
  if ( radio.available() )
  {
    // Reading the data payload until the RX received everything
    bool done = false;
    while (!done)
    {
      // Fetching the data payload
      done = radio.read( joystick, sizeof(joystick) );
     // if(joystic[1]
     // Serial.print("X = ");
     // Serial.print(joystick[0]);
     pulseWidth = joystick[1] + minPulse;
      
     Serial.print(" Moving servo to: ");      
     // Serial.println(joystick[1]);
     Serial.println(pulseWidth, DEC);
     updateServo(); //update servo position
    } 
  } //updateServo() here; might need to make this an if statement instead of while loop
  
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
