
// Replace sensor numbers with Names
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int a = 0;
int i = 0;
int steps = 0;

const int SERVOMIN[6] = {129,158,143,123,154,142}; // 'minimum' pulse length 
const int SERVOMAX[6] = {507,596,565,469,615,544}; // 'maximum' pulse length 


double Pox[6] = {73.7237,81.5677,7.84402,-7.84402,-81.5677,-73.7237};
double Poy[6] = {51.6219,38.0356,-89.6575,-89.6575,38.0356,51.6219};
double Box[6] = {28.501856,113.99164,85.489787,-85.489787,-113.9916,-28.50186};
double Boy[6] = {115.17,-32.90,-82.27,-82.27,-32.90,115.17};
int theta[6] = {180,-120,60,120,-60,0};
int angle[6] = {200,180,190,195,200,220};
double pulselength[6] = {1.89,2.433333333333333,2.221052631578947,1.7743589743589743,2.305,1.8272727272727274};


double tr = 0.00;
double ty = 0.00;
double tp = 0.00;
double sw = 0.00;
double su = 0.00;
double hv = 0.00;
double ht = 90;
int rod = 120;
int servo = 20;

double Px[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double Py[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double Pz[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double Lx[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double Ly[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double Lz[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double L[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double A[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double B[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double C[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double alphar[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double alphad[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
double motorang[6] = {0.0,0.0,0.0,0.0,0.0,0.0};

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
int val[6] = {170,410,180,440,150,390};
int min_val[6] = {170,410,180,440,150,390};
int max_val[6] = {370,210,380,280,320,195};
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
  for (i=0; i<6; i++) {  
          pwm.setPWM(i, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
    
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
  if (Serial1.available() < 1) ; // if serial empty, return to loop().

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
    sw = value0;
    su = value1;
    hv = value2;
  }
  if (sensorType == 3){ // orientation
    valorien[0] = value0*(PI/180);
    valorien[1] = value1*(PI/180);
    valorien[2] = value2*(PI/180);
  }
  logCount = Serial1.parseInt();  // read total logged sensor readings
  value0 = Serial1.parseFloat();  // 1st sensor value
  value1 = Serial1.parseFloat();  // 2rd sensor value if exists
  value2 = Serial1.parseFloat();  // 3rd sensor value if exists

  // send sensoduino readings to serial monitor/terminal
  if (DEBUG) {
    /*Serial.print("Sensor type: ");
    Serial.println(sensorType);
    Serial.print("Sensor log#: ");
    Serial.println(logCount);
    Serial.print("Val[0]: ");
    Serial.println(value0);
    Serial.print("Val[1]: ");
    Serial.println(value1);
    Serial.print("Val[2]: ");
    Serial.println(value2);
    */
    //Serial.println("-----------------------");
    //delay(30);
  }

// Check sensor type. If not for  Accelerometer (#1) then ignore readings
// sensorType 1 is the Accelerometer sensor
  Serial.println("-----------------------");
  Serial.println("-----------------------");
  
  platpivot(valorien[1],valorien[2]);
  
  deltaL();
  
  virtleglen();
  
  ABC();
  
  alpharad();
  
  alphadeg();
 
  finalval();
  Serial.print(motorang[0]);
  Serial.print("##");
  //for (i = 0; i<6; i++){
    //Serial.println(motorang[i]);
  
 // }
}
/*
  panVal = map(panVal, -10, 10, 0, 179);  // Map Accelerometer X value to pan servo angle.
  panServo.write(panVal);     
  delay(10); 
}

*/
float platpivot(float tp,float tr)
{
  for (i = 0; i<6 ; i++){ 
    Px[i] = ((Pox[i])*cos(tr)) + ((Poy[i])*((sin(tp)*sin(tr)*cos(tr)))) + sw;
    Py[i] = ((Poy[i])*((cos(tp)))) + su;
    Pz[i] = (-(Pox[i])*sin(tr)) + ((Poy[i])*sin(tp)*cos(tr)) + ht + hv;
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
    A[i] = (pow((L[i]),2)) - ((pow((rod),2)) - (pow((servo),2)));
    
    B[i] =  2*(servo)*(Pz[i]);//CHECK THIS
  
    C[i] = (2*(servo)*cos((theta[i])*PI*(1/180))*(Px[i] - Box[i])) + (sin((theta[i])*PI*(1/180))*(Py[i] - Boy[i]));
  }
}
void alpharad()
{
  for (i = 0; i<6 ; i++){\
    double val = (A[i])/(sqrt(pow(B[i],2)+ pow(C[i],2)));
    double val2 = C[i]/B[i];
    alphar[i] = sinin(val) - tanin(val2); 
  }
}
void alphadeg()
{
  for (i = 0; i<6 ; i++){
    alphad[i] = ((alphar[i]) * (1/PI) * (180)); 
  }
}
void finalval()
{
  for (i = 0; i<6;i++){
    motorang[i] = (map(alphad[i],0,90,min_val[i],max_val[i]));
  }
}







float sinin(float c){

  float out;
  out= ((c+(c*c*c)/6+(3*c*c*c*c*c)/40+(5*c*c*c*c*c*c*c)/112+
  (35*c*c*c*c*c*c*c*c*c)/1152 +(c*c*c*c*c*c*c*c*c*c*c*0.022)+
  (c*c*c*c*c*c*c*c*c*c*c*c*c*.0173)+(c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*.0139)+
  (c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*0.0115)+(c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*0.01)
  ));

  if(c>=.96 && c<.97){out=1.287+(3.82*(c-.96)); }
  
  if(c>=.97 && c<.98){out=(1.325+4.5*(c-.97));} // arcsin
  
  if(c>=.98 && c<.99){out=(1.37+6*(c-.98));}
  
  if(c>=.99 && c<=1){out=(1.43+14*(c-.99));}
  
  return out;
  }

float cosin(float c){

  float out;

  out=sinin(sqrt(1-c*c));

  return out;
  }

float tanin(float c){

  float out;
  out=sinin(c/(sqrt(1+c*c)));
  return out;
}
