/**
 * This arduino program reads input values from a potentiometer and converts
 * the value to the corresponding Spark pwm value (Between 1000μs - 2000μs).
 * Pressing button 1 writes the pwm value to the spark, releasing the button 
 * sets the PWM value to neutral.
 */
#include <Servo.h> 

// Declare Sparks.
Servo Spark;

// Spark PWM Ranges
int sparkFullReverse = 1000; // Units in microseconds.
int sparkNeutral     = 1500; // Spark datasheet: http://www.revrobotics.com/content/docs/REV-11-1200-UM.pdf
int sparkFullForward = 2000;

// Potentiometer input range.
int potMin = 0;
int potMax = 1023;

// Pin Assignment
unsigned char potPin = A2; 
int sparkPin   = 9;
int buttonPin1 = 2;
int buttonPin2 = 3;

// Global States.
int potState = 0;
int sparkVal = 1500;
int buttonState1 = 0;
int buttonState2 = 0;

void setup() 
{ 
  pinMode(buttonPin1, INPUT); 
  pinMode(buttonPin2, INPUT);   
  Spark.attach(sparkPin);

  //Serial.begin(9600);
} 

void loop() {
   // Read input values.
   buttonState1 = digitalRead(buttonPin1);
   buttonState2 = digitalRead(buttonPin2);
   potState = analogRead(potPin);    // Read Pot value.  
   sparkVal = map(potState, potMin, potMax, sparkFullReverse, sparkFullForward); // Map input range to output values.
  
   // Check if the buttons are pressed and drive spark using value read from pot.
   if ( buttonState1 == HIGH ) {
     Spark.writeMicroseconds(sparkVal);
   } else {
     Spark.writeMicroseconds(sparkNeutral);
   }

    //Serial.println(val);
} 
