
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
/* Example: nRF24L01 */
 
   1 - GND 
   2 - VCC 3.3V /* WARNING SHOULD BE 3.3v Not 5V */
   3 - CE - Arduino pin 9
   4 - CSN - Arduino pin 10
   5 - SCK - Arduino pin 13
   6 - MOSI - Arduino pin 11
   7 - MISO - Arduino pin 12
   8 - UNUSED 
 
 /* You can used an Analog Joystick or 2 10K potentiometers */
 
   GND - Arduino GND 
   VCC - Arduino +5V
   X Pot - Arduino A0
   Y Pot - Arduino A1
 
/*----- Import all required Libraries -----*/
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
/*----- Declare all constant pin to be used ----*/
 
#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
 
 
const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module
 
 
/*-----Object Declaration ----*/
 
RF24 radio(CE_PIN, CSN_PIN); // Activate  the Radio
 
/*-----Declaration of Variables -----*/
 
int joystick[2];  // Two element array holding the Joystick readings
 
void setup()   
{
  Serial.begin(9600); /* Opening the Serial Communication */
  radio.begin();
  radio.openWritingPipe(pipe);
}//--(end setup )---
 
 
void loop()   /* Runs Continuously */
{
  joystick[0] = analogRead(JOYSTICK_X); /* Reading Analog X
  joystick[1] = analogRead(JOYSTICK_Y); /* Reading Analog Y
  
  radio.write( joystick, sizeof(joystick) );
 
}//--(end main loop )---
