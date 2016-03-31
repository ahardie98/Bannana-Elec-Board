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
int prev;

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
  //int prev; // previous value
  if ( radio.available() )
  {
    // Reading the data payload until the RX received everything
    bool done = false;
    while (!done)
    {
      // Fetching the data payload
      prev = pulseWidth;    // Starts at 700
      done = radio.read( joystick, sizeof(joystick) );

      if(joystick[1] >=330)
      {  
        // If joystick is greater than center
        pulseWidth = joystick[1] + minPulse;
        //prev = pulseWidth; 
           
          if(pulseWidth < prev)        // 1200(pulseWidth) < 1300(prev)
          {  
             if(prev != pulseWidth)    // 1300(prev) != 1200(new value)
             {       
                prev--;   // decrement previous, until it equals the new value
                Serial.println("Deccelerating."); // For testing
                // Deccelerate
              }
           }
        
          else if(pulseWidth > prev)      // 1000 > 800
          {  
              if(prev != pulseWidth)      //800 != 1000
              {  
                  prev++; // increment previous until it equals the new value
                  Serial.println("Accelerating."); 
                 // updateServo();
                  // Accelerate
              }
          }

           else 
           {
                Serial.println("Values not changing");
                // For when you are at a steady rate
           }
                         
             
          //updateServo();
      } // End if()

     else if (joystick[1] < 328){  //328
        pulseWidth = joystick[1] + minPulse;
      } //to make sure it stops at center and below, works but stops suddenly, also missing else
    //  else
    //  {
       
     //  }
//Serial.println(prev); //
      updateServo(); //update servo position, works here 
    //  Serial.println(prev); doesnt stop!
    } //End while ()
  } // End if()
} // End loop()

void updateServo() {
  // pulse the servo again if rhe refresh time (20 ms) have passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    delayMicroseconds(pulseWidth);        // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    lastPulse = millis();           // save the time of the last pulse
  }
}
