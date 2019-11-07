/*
 PROJECT: SensoDuino 0.17 
 PROGRAMMER: Hazim Bitar (techbitar at gmail dot com)
 DATE: Sep 30, 2013
 FILE: sensoduino.ino
 LICENSE: Public domain
 */

// Replace sensor numbers with Names
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int a = 0;
int i = 0;
int pulselength = 0;
const int SERVOMIN_1 = 150; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_1 = 450; // 'maximum' pulse length count (out of 4096) 475
#define START_CMD_CHAR '>'
#define END_CMD_CHAR '\n'
#define DIV_CMD_CHAR ','

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data
// Center servos
int tiltVal = 90; 
int panVal =90; 
String inText;
float value0, value1, value2;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(19, INPUT_PULLUP);
  Serial.println("\nSensoDuino 0.13 by TechBitar.com (2013).\n");
  Serial.println("Android Sensor Type No: ");
  Serial.println("1- ACCELEROMETER  (m/s^2 - X,Y,Z)");
  Serial.println("3- ORIENTATION (Yaw, Pitch, Roll)");
  Serial.println("4- GYROSCOPE (rad/sec - X,Y,Z)");
  pwm.setPWMFreq(60);
  for (i=0; i<1; i++) {  
          pwm.setPWM(i, 0, 0); // added +1 to match PWM port numbering (pins 1..6 used)
    
  a = pwm.getPWM(0);
  Serial.println(a);
  
}
}
void loop()
{
  
  int inCommand = 0;
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' ';  //read serial

  // wait for incoming data
  if (Serial1.available() < 1) Serial.println("hello") ; // if serial empty, return to loop().

  // parse incoming command start flag
  getChar = Serial1.read();
  if (getChar != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming pin# and value 
  sensorType = Serial1.parseInt(); // read sensor typr
  logCount = Serial1.parseInt();  // read total logged sensor readings
  value0 = Serial1.parseFloat();  // 1st sensor value
  value1 = Serial1.parseFloat();  // 2rd sensor value if exists
  value2 = Serial1.parseFloat();  // 3rd sensor value if exists

  // send sensoduino readings to serial monitor/terminal
  if (DEBUG) {
    Serial.print("Sensor type: ");
    Serial.println(sensorType);
    Serial.print("Sensor log#: ");
    Serial.println(logCount);
    Serial.print("Val[0]: ");
    Serial.println(value0);
    Serial.print("Val[1]: ");
    Serial.println(value1);
    Serial.print("Val[2]: ");
    Serial.println(value2);
    Serial.println("-----------------------");
    delay(10);
  }

// Check sensor type. If not for  Accelerometer (#1) then ignore readings
// sensorType 1 is the Accelerometer sensor

  if (sensorType !=1) return;   

  panVal = value0; // value0 = X sensor reading
  tiltVal = value1;  // value1 = Y sensor reading

  tiltVal = map(tiltVal, 10, -10, 0, 179);   // Map Accelerometer Y value to tilt servo angle. 
  for (i = 0;i<1;i++){
    pulselength = map(tiltVal,0,179,SERVOMIN_1,SERVOMAX_1);
    pwm.setPWM(i, 0, pulselength);
  }
}
/*
  panVal = map(panVal, -10, 10, 0, 179);  // Map Accelerometer X value to pan servo angle.
  panServo.write(panVal);     
  delay(10); 
}

*/
