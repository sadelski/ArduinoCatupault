
// Include Libraries
#include "Arduino.h"
#include "PiezoSpeaker.h"
#include "Button.h"
#include "Servo.h"


// Pin Definitions
#define PIEZOSPEAKER5V_PIN_SIG	5
#define PUSHBUTTON_PIN_2	4
#define SERVOMD_1_PIN_SIG	3
#define SERVOMD_2_PIN_SIG	2
#define SERVOMD_3_PIN_SIG 6

int potpin = 0;
int val;    // variable to read the value from the analog pin

// Global variables and defines
unsigned int piezoSpeaker5vHoorayLength          = 6;                                                      // amount of notes in melody
unsigned int piezoSpeaker5vHoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int piezoSpeaker5vHoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
const int servoMD_1RestPosition   = 0;  //Starting position
const int servoMD_1TargetPosition = 180; //Position when event is detected
const int servoMD_2RestPosition   = 75;  //Starting position
const int servoMD_2TargetPosition = 180; //Position when event is detected

// object initialization
Servo servoMD_1;
Servo servoMD_2;
Servo servoMD_3;



PiezoSpeaker piezoSpeaker5v(PIEZOSPEAKER5V_PIN_SIG);
Button pushButton(PUSHBUTTON_PIN_2);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    pushButton.init();
    servoMD_1.attach(SERVOMD_1_PIN_SIG);
    servoMD_1.write(servoMD_1RestPosition);
    delay(100);
    servoMD_1.detach();
    servoMD_2.attach(SERVOMD_2_PIN_SIG);
    servoMD_2.write(servoMD_2RestPosition);
    delay(100);
    servoMD_2.detach();
    servoMD_3.attach(SERVOMD_3_PIN_SIG);         //attach the servo to correct pin to control it.
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
  
//     Mini Pushbutton Switch - Test Code
//    Read pushbutton state. 
//    if button is pressed function will return HIGH (1). if not function will return LOW (0). 
  
    bool pushButtonVal = pushButton.read();

    if( pushButtonVal == 1) {
    
     servoMD_3.detach();                    //  release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
     
    // Piezo Speaker - Test Code
    // The Speaker will play the Hooray tune
    piezoSpeaker5v.playMelody(piezoSpeaker5vHoorayLength, piezoSpeaker5vHoorayMelody, piezoSpeaker5vHoorayNoteDurations); 
    delay(4000);   
    
    servoMD_1.attach(SERVOMD_1_PIN_SIG);         //attach the servo to correct pin to control it.
    servoMD_1.write(servoMD_1TargetPosition);  //turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(1800);                              //waits 3500 milliseconds (3.5 sec).                  
   
    servoMD_2.attach(SERVOMD_2_PIN_SIG);         //attach the servo to correct pin to control it.
    servoMD_2.write(servoMD_2TargetPosition);  //turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              //waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD_2.detach();                       // release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    delay(1500);

    servoMD_1.write(servoMD_1RestPosition);  //turns servo to target position. Modify target position by modifying the 'ServoTargetPosition' definition above.
    delay(500);                              //waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD_1.detach();                    // release the servo to conserve power. When detached the servo will NOT hold it's position under stress.

    
    servoMD_2.attach(SERVOMD_2_PIN_SIG);         //attach the servo to correct pin to control it.
    servoMD_2.write(servoMD_2RestPosition);    // turns servo back to rest position. Modify initial position by modifying the 'ServoRestPosition' definition above.
    delay(500);                              // waits 500 milliseconds (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    servoMD_2.detach();                    //  release the servo to conserve power. When detached the servo will NOT hold it's position under stress.

    servoMD_3.attach(SERVOMD_3_PIN_SIG);         //attach the servo to correct pin to control it.
    
    }
    
    else
    {
    val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    servoMD_3.write(val);                  // sets the servo position according to the scaled value
    delay(15);                           // waits for the servo to get there
    }

    }
