
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);

const int AOUTpin = 0;//the AOUT pin of the gas sensor goes into analog pin A0 of the arduino
const int DOUTpin = 13;//the DOUT pin of the gas sensor goes into digital pin D8 of the arduino


int gasLimit;
int gasValue;


const int lm35Pin = A1;  // LM35 O/P pin (temperature sensor)


Servo servo;  
Servo servoLeft;
Servo servoRight;
int servoAngle = 0;
char btData = ' ';
int countCycles = 0;


void setup() {
  Serial.begin(9600);
  hc06.begin(9600);
  servo.attach(4);
  servoLeft.attach(8);
  servoRight.attach(7);
  int speed = 0;
  pinMode(12, OUTPUT);     // laserPin
}


void loop() {
  
btData = ' ';
countCycles = countCycles + 1;

if(hc06.available())
{
  btData = hc06.read();
  
  switch (btData)
  {
   case 'f':                      // FORWARD
          servoLeft.write(180); // the servos are turned in opposite directions so they have to spin in mirrored directions
          servoRight.write(0);
          delay(100);
          servoLeft.write(90);
          servoRight.write(90);
      break;
   case 'b':                    // BACK
          servoLeft.write(0); 
          servoRight.write(180);
          delay(100);
          servoLeft.write(90);
          servoRight.write(90);
      break;
   case 'l':                    // LEFT
          servoLeft.write(0); 
          servoRight.write(0);
          delay(100);
          servoLeft.write(90);
          servoRight.write(90);
      break;
    case 'r':                   // RIGHT
          servoLeft.write(180); 
          servoRight.write(180);
          delay(100);
          servoLeft.write(90);
          servoRight.write(90);
      break;
    case 'n':
      digitalWrite(11, HIGH);    // laser ON
      break;
    case 'm':
      digitalWrite(11, LOW);     // laser OFF
      break;
    case 'c':
      servo.write(90);           // center position - CLOSED
      delay(500);  
      break;
    case 'o':
      servo.write(40);           // OPEN
      delay(500);
      break;
     default: 
      break; 
  }
}


  if(countCycles % 1500 == 0) // This way it prints the sensors' data every 1.5 seconds
  {
    gasValue= analogRead(AOUTpin); //reads the analaog value from the gas sensor's AOUT pin
    gasLimit= digitalRead(DOUTpin); //reads the digital value from the gas sensor's DOUT pin
    Serial.print("Gas value: ");
    Serial.println(gasValue);

    float temperature = (((analogRead(lm35Pin) * 4.88)/10) -390);  //Read Temperature in mv/°C, Convert adc value to equivalent voltage and LM35 gives output of 10mv/°C so /10
    Serial.print("Temperature: ");
    Serial.print(temperature - 5);
    Serial.println("°C ");
  }

delay(1);


}
