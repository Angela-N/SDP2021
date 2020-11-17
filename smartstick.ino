/*
SDP 2020 Team 32
Emic 2 Text-to-speech Module
Linda Tran

Version 1.0 November 2, 2020  Used Example Code
Version 1.5 November 7, 2020  Added Dates, Introduction
Version 2.0 November 13, 2020 Added comments, Left/right/distance statements
Version 3.0 November 17, 2020 Changed statements into functions, added change voice, added change language
*/

// include the SoftwareSerial library so we can use it to talk to the Emic 2 module
#include <SoftwareSerial.h>

#define rxPin   10  // Serial input (connects to Emic 2's SOUT pin)
#define txPin   11  // Serial output (connects to Emic 2's SIN pin)
#define ledPin  13  // Most Arduino boards have an on-board LED on this pin

// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

void setup()  // Set up code called once on start-up
{
  // define pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);

  digitalWrite(ledPin, LOW);  // turn LED off, LED turns on when speaking
  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    initialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"
  */
  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer
}

void loop()       // Main code, to run repeatedly
{
  
  date();
  delay(500);     // 1/2 second delay

  introduction();
  delay(500);       // 1/2 second delay
  
  leftOfCane();     //There is an obj on the left of the cane
  delay(500);       // 1/2 second delay
  
  rightOfCane();    //There is an obj on the right of the cane
  delay(500);       // 1/2 second delay
  
  distanceOfObj();  //There is an obj ___ ahead -- Currently hardwired
    
  while(1)      // Demonstration complete!
  {
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(500);              
    digitalWrite(ledPin, LOW);
  }
}

void changeVoice(){
  //Change Voice
  emicSerial.print('N');
  emicSerial.print('2');              // change voice [0,8]
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void changeLanguage(){
  //Change Language
  emicSerial.print('P');
  emicSerial.print('0');              // change language/dialect [0,2]
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void date(){
  // Test 1: Say today's date
  changeVoice();
  changeLanguage();
  emicSerial.print('S');
  emicSerial.print("Hello. This is test number 1. Today is November seven teen twenty twenty.");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void introduction(){
  // Introduction
  emicSerial.print('S');
  emicSerial.print("This is Linda's MDR Deliverable.");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void leftOfCane(){
  // Object is on the left
  emicSerial.print('S');
  emicSerial.print("There is an object on the left.");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void rightOfCane(){
  // Object is on the right
  emicSerial.print('S');
  emicSerial.print("There is an object on the right");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}

void distanceOfObj(){
  // Object is 2 feet away
  emicSerial.print('S');
  emicSerial.print("There is an object that is 2 feet away");  // Send the desired string to convert to speech
  emicSerial.print('\n');
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);
}
