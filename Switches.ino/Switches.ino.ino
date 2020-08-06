
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// Use single on-off-on toggle to control servo position.
// First position moves from X to Y degrees
// Second position moves from Y to X degrees

int pos = 35;    // variable to store the servo position and starting position
int buttonApin = 38;
int buttonBpin = 39;

bool buttonAstatus; // stores button state
bool buttonBstatus;

void setup()
{
  Serial.begin(9600);
  Serial.print("Running v2.0 of Servo controlled by toggle and Nano.");
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
 
  buttonAstatus = digitalRead(buttonApin);
  buttonBstatus = digitalRead(buttonBpin);
  Serial.println(buttonAstatus);
  Serial.println(buttonBstatus);
 
  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
}

void loop()
{
  buttonAstatus = digitalRead(buttonApin);
  buttonBstatus = digitalRead(buttonBpin);
  Serial.println(buttonAstatus);
  Serial.println(buttonBstatus);
 
  if (buttonAstatus == LOW)
  {
      Serial.print('A');
  }

  if (buttonBstatus == LOW)
  {
      Serial.print('B');
  }
  if (buttonBstatus == HIGH && buttonAstatus == HIGH)
  { 
    
      Serial.print('C');
  }
  
}
