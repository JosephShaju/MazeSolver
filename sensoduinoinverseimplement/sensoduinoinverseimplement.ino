
// Replace sensor numbers with Names
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int a = 0;
int i = 0;
int steps = 0;

const int SERVOMIN[6] = {129,158,143,123,154,142}; // 'minimum' pulse length 
const int SERVOMAX[6] = {507,596,565,469,615,544}; // 'maximum' pulse length 


float Pox[6] = {73.7237,81.5677,7.84402,-7.84402,-81.5677,-73.7237};
float Poy[6] = {51.6219,38.0356,-89.6575,-89.6575,38.0356,51.6219};
float Box[6] = {28.501856,113.99164,85.489787,-85.489787,-113.9916,-28.50186};
float Boy[6] = {115.17,-32.90,-82.27,-82.27,-32.90,115.17};
int theta[6] = {180,-120,60,120,-60,0};
int angle[6] = {200,180,190,195,200,220};


float tr = 0.00;
float ty = 0.00;
float tp = 0.00;
float sw = 0.00;
float su = 0.00;
float hv = 0.00;
float ht = 90;
int rod = 120;
int servo = 20;

float Px[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float Py[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float Pz[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float Lx[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float Ly[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float Lz[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float L[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float A[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float B[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float C[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float alphar[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float alphad[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float pulselength[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float motorang[6] = {0.0,0.0,0.0,0.0,0.0,0.0};

#define START_CMD_CHAR '>'
#define END_CMD_CHAR '\n'
#define DIV_CMD_CHAR ','

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data
// Center servos
int tiltVal = 90; 
int panVal =90; 
int accel = 0;
float valaccel[3] = {0.0,0.0,0.0};
float valgyro[3] = {0.0,0.0,0.0};
float valorien[3] = {0.0,0.0,0.0};
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
  if (sensorType == 1){ // accelerator
    valaccel[0] = value0;
    valaccel[1] = value1;
    valaccel[2] = value2;
  }
  if (sensorType == 4){ // gyroscope
    valgyro[0] = value0;
    valgyro[1] = value1;
    valgyro[2] = value2;
  }
  if (sensorType == 3){ // orientation
    valorien[0] = value0;
    valorien[1] = value1;
    valorien[2] = value2;
  }
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
    delay(30);
  }

// Check sensor type. If not for  Accelerometer (#1) then ignore readings
// sensorType 1 is the Accelerometer sensor

  platpivot(valorien[0],valorien[1],valorien[2]);
  deltaL();
  virtleglen();
  ABC();
  alpharad();
  alphadeg();
  degreesteps();
  finalval();
  for (i = 0; i<6; i++){
    Serial.println(motorang[i]);
  
  }
}
/*
  panVal = map(panVal, -10, 10, 0, 179);  // Map Accelerometer X value to pan servo angle.
  panServo.write(panVal);     
  delay(10); 
}

*/
float platpivot(float ty,float tp,float tr)
{
  for (i = 0; i<6 ; i++){ 
    Px[i] = ((Pox[i])*cos(tr)*cos(ty)) + ((Poy[i])*((sin(tp)*sin(tr)*cos(tr)) - (cos(tp)*sin(ty)))) + sw ;
    Py[i] = ((Pox[i])*cos(tr)*sin(ty)) + ((Poy[i])*((cos(tp)*cos(ty)) + (sin(tp)*sin(tr)*sin(ty)))) + su ;
    Pz[i] = (-(Pox[i])*sin(tr)) + ((Poy[i])*sin(tp)*cos(tr)) + ht + hv ;
  }   
}
void deltaL()
{
  for (i = 0; i<6 ; i++){ 
    Lx[i] = Box[i] - Px[i] ;
    Ly[i] = Boy[i] - Py[i];
    Lz[i] = -Pz[i];
   }
}

void virtleglen()
{
  for (i = 0; i<6 ; i++){ 
    L[i] = sqrt((pow((Lx[i]),2.0)) + (pow((Ly[i]),2.0)) + (pow((Lz[i]),2.0)));
   }
}

void ABC()
{
  for (i = 0; i<6 ; i++){ 
    A[i] = (pow((L[i]),2.0)) - ((pow((rod),2.0)) - (pow((servo),2.0)));
    B[i] =  2*(servo)*(Pz[i]);
    C[i] = (2*(servo)*cos((theta[i])*PI*(1/180))*(Px[i] - Box[i])) + (sin((theta[i])*PI*(1/180))*(Py[i] - Boy[i]));
  }
}
void alpharad()
{
  for (i = 0; i<6 ; i++){
    alphar[i] = (asin((A[i])/(sqrt((pow((B[i]),2)) + (pow((B[i]),2)))))) - (atan((C[i])/(B[i]))); 
  }
}
void alphadeg()
{
  for (i = 0; i<6 ; i++){
    alphad[i] = ((alphar[i]) * PI * (1/180)); 
  }
}
void degreesteps()
{
  for (i = 0; i<6 ; i++){
      steps = SERVOMAX[i] - SERVOMIN[i];
      pulselength[i] = ((steps)/(angle[i]));
  }
}
void finalval()
{
  for (i = 0; i<6;i++){
    motorang[i] = (alphad[i])*(pulselength[i]);
  }
}
