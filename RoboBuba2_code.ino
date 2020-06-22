
#include <Servo.h>


Servo servo;  
Servo servoLeft;
Servo servoRight;
int servoAngle = 0;
char btData = ' ';

void setup() {
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  servo.attach(4);
  servoLeft.attach(8);
  servoRight.attach(7);
  int speed = 0;
  
}


void loop() {
  btData = Serial.read();
switch (btData)
{
 case 'f':                      // FORWARD
        servoLeft.write(180); // the servos are turned in opposite directions 
        servoRight.write(0);
        delay(250);
        servoLeft.write(90);
        servoRight.write(90);
    break;
 case 'b':                    // BACK
        servoLeft.write(0); 
        servoRight.write(180);
        delay(250);
        servoLeft.write(90);
        servoRight.write(90);
    break;
 case 'l':                    // LEFT
        servoLeft.write(0); 
        servoRight.write(0);
        delay(250);
        servoLeft.write(90);
        servoRight.write(90);
    break;
  case 'r':                   // RIGHT
        servoLeft.write(180); 
        servoRight.write(180);
        delay(250);
        servoLeft.write(90);
        servoRight.write(90);
    break;
  case 'n':
    digitalWrite(12, HIGH);    // laser ON
    break;
  case 'm':
    digitalWrite(12, LOW);     // laser OFF
    break;
  case 'c':
    servo.write(90);           // center position - CLOSED
    delay(1000);  
    break;
  case 'o':
    servo.write(40);           // OPEN
    delay(1000);
    break;
   default: 
    break; 
}



}
