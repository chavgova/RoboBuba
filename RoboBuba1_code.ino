#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 512;
Stepper myStepperLeft(stepsPerRevolution, 8,10, 9, 11); // 1-3-2-4
Stepper myStepperRight(stepsPerRevolution, 4,6,5,7); // 1-3-2-4
int laserPin = 12;
int servoPin = 3;
Servo servo;  
int servoAngle = 0;

void setup() {
  myStepperLeft.setSpeed(70);
  myStepperRight.setSpeed(70);
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
}


void loop() {

char btData = Serial.read();

switch (btData)
{
  case 'f':                      // НАПРЕД
    for(int i=0;i<=300; i++)
    {
      myStepperLeft.step(-1); //моторите са обърнати един срещу друг => за да се движи роботът напред (и двата мотора се движат напред), трябва посоката на оста на единия мотор да е противоположна на другия (те са огледални)
      myStepperRight.step(1);
      delay(1);
    }
    break;
   case 'b':                    // НАЗАД
    for(int i=0;i<=300; i++)
    {
      myStepperLeft.step(1);
      myStepperRight.step(-1);
      delay(1);
    }
    break;
   case 'l':                    // ЛЯВО
    for(int i=0;i<=300; i++)
    {
      myStepperLeft.step(1);
      myStepperRight.step(1);
      delay(1);
    }
    break;
   case 'r':                   // ДЯСНО
    for(int i=0;i<=300; i++)
    {
      myStepperLeft.step(-1);
      myStepperRight.step(-1);
      delay(1);
    }
    break;
   case 'n':
    digitalWrite(12, HIGH);    // laser ON
    break;
   case 'm':
    digitalWrite(12, LOW);     // laser OFF
    break;
   case 'c':
    servo.write(90);           // center position - closed
    delay(1000);  
    break;
   case 'o':
    servo.write(40);           // open
    delay(1000);
    break;
   default: 
    break; 
}



}
