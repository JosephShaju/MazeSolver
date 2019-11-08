
// Replace sensor numbers with Names
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int a = 0;
int i = 0;
int pulselength = 0;
const int SERVOMIN_1 = 150; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_1 = 450; // 'maximum' pulse length count (out of 4096) 475

float Pox[6] = {73.7237,81.5677,7.84402,-7.84402,-81.5677,-73.7237};
float Poy[6] = {51.6219,38.0356,-89.6575,-89.6575,38.0356,51.6219};
float Box[6] = {28.501856,113.99164,85.489787,-85.489787,-113.9916,-28.50186};
float Boy[6] = {115.17,-32.90,-82.27,-82.27,-32.90,115.17};
int theta[6] = {180,-120,60,120,-60,0};


float Px = 0.00;
float Py = 0.00;
float tr = 0.00;
float ty = 0.00;
float tp = 0.00;
float sw = 0.00;
float su = 0.00;
float hv = 0.00;
float ht = 90;
float A = 0.00;
float B = 0.00;
float C = 0.00;
int rod = 120;
int servo = 20;

float Px[6] = {};
float Py[6] = {};
float Pz[6] = {};
float Lx[6] = {};
float Ly[6] = {};
float Lz[6] = {};
float L[6] = {};
float alphar[6] = {};
float alphad[6] = {};

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
    pwm.setPWM(i+1, 0, pulselength);
  }
}
/*
  panVal = map(panVal, -10, 10, 0, 179);  // Map Accelerometer X value to pan servo angle.
  panServo.write(panVal);     
  delay(10); 
}

*/
void platpivot()
{
  for (i = 0, i<6 ; i++){ 
    Px[i] = ((Pox[i])*cos(tr)*cos(ty)) + ((Poy[i])*[(sin(tp)*sin(tr)*cos(tr)) - (cos(tp)*sin(ty))]) + sw ;
    Py[i] = ((Pox[i])*cos(tr)*sin(ty)) + ((Poy[i])*[(cos(tp)*cos(ty)) + (sin(tp)*sin(tr)*sin(ty))]) + su ;
    Pz[i] = (-(Pox[i])*sin(tr)) + ((Poy[i])*sin(tp)*cos(tr)) + ht + hv ;
  }   
}
void deltaL()
{
  for (i = 0, i<6 ; i++){ 
    Lx[i] = Box[i] - Px[i] ;
    Ly[i] = Boy[i] - Py[i];
    Lz[i] = -Pz[i];
   }
}

void virtleglen()
{
  for (i = 0, i<6 ; i++){ 
    L[i] = sqrt(((Lx[i])^2) + ((Ly[i])^2) + ((Lz[i])^2));
   }
}

void ABC()
{
  for (i = 0, i<6 ; i++){ 
    A[i] = ((L[i])^2) - (((rod)^2) - ((servo)^2));
    B[i] =  2*(servo)*(Pz[i]);
    C[i] = (2*(servo)*cos((theta[i])*PI*(1/180))*(Px[i] - Box[i])) + (sin((theta[i])*PI*(1/180))*(Py[i] - Boy[i]));
  }
}
void alpharad()
{
  for (i = 0, i<6 ; i++){
    alphar[i] = (asin((A[i])/(sqrt(((B[i])^2) + ((C[i])^2))))) - (atan((C[i])/(B[i]))); 
  }
}
void alphadeg()
{
  for (i = 0, i<6 ; i++){
    alphad[i] = ((alphar[i]) * PI * (1/180)); 
  }
}
