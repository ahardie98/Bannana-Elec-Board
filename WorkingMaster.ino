#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
// Connect the HC-05 TX to Arduino pin 10 RX. 
// Connect the HC-05 RX to Arduino pin 11 TX through a voltage divider.

char c ; // = ''
int val1; //= 0

void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(9600);
    pinMode(10, INPUT); //
    pinMode(11, OUTPUT); //
    Serial.println("Arduino with HC-05 is ready");
 
    // start communication with the HC-05 using 9600
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");
    Serial.flush(); //
    BTserial.flush(); //
}

void loop()// will continue to loop
{
    //int flag = 0; 
    while(1){
  // Keep reading from HC-05 and send to Arduino Serial Monitor
   /* if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }*/
 
      
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available() > 0) //added >0
    {
        val1 = Serial.read();
        //BTserial.write(val1);
        //  c =  Serial.read();
        // BTserial.write(c);  
    }
      if (val1)
      {
      BTserial.write(val1);
      //  flag=1;
      }
    

//       val1 = Serial.read();
  //     Serial.write(val1);
 //      BTserial.write(val1);
  }
}
