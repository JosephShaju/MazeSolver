#include <Adafruit_PWMServoDriver.h>
#include "MPU9250.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const int SERVOMIN = 145; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX = 460; // 'maximum' pulse length count (out of 4096) 475

const int SERVOMID = floor((SERVOMAX+SERVOMIN)/2); // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 2; // 'change' pulse length count
// maximum it can go for 180 degree is 350 steps
//but we cant do that because our range is not 350 steps, aka our max will be 460-145 = 340 so not all the way till 180 degree but somewhat close.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int val[6] = {SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID};
int val1[6] = {265,300,165,295,185,165};
int val2[6] = {265,300,165,215,170,170};
int val3[6] = {185,300,205,215,185,285};
int val4[6] = {225,300,205,215,185,285};
int val5[6] = {165,300,205,215,185,245};
String valInput; // Serial input var.
int i=0; // loop index var.
int j=0;
int serv_max = 0;
//int val[6] = {SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID}; // PWM var
int valm[6] = {270,300,197,235,175,170};
int a = 0;
int tim = 30;
MPU9250 IMU(Wire,0x68);
int status;
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(10); // change default (1000ms) to have faster response time
  Serial.println("Running example: Servo motor actuation using messaging");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  for (i=0; i<6; i++) {  
          pwm.setPWM(i+1, 0, 0); // added +1 to match PWM port numbering (pins 1..6 used)
    }
  a = pwm.getPWM(0);
  Serial.println(a);

  // start communication with IMU 
  status = IMU.begin();\
  status = IMU.calibrateAccel();
  
}
void automation(int list[6]){
          for(i = 0;i<6;i++){
            serv_max = list[i];
            for(j = 0; j<100; j++) {
              list[i]= min(list[i]+SERVOCHG, serv_max);
              pwm.setPWM(i, 0, list[i]);
              delay(tim);
            }
        }
  
  
  
  }
void accelprint(){
  // read the sensor
  IMU.readSensor();
  // display the data
  Serial.print("AccelX: ");
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("  ");
  Serial.print("AccelY: ");  
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("  ");
  Serial.print("AccelZ: ");  
  Serial.println(IMU.getAccelZ_mss(),6);
  
  /*Serial.print("GyroX: ");
  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("  ");
  Serial.print("GyroY: ");  
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("  ");
  Serial.print("GyroZ: ");  
  Serial.println(IMU.getGyroZ_rads(),6);

  Serial.print("MagX: ");  
  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("  ");  
  Serial.print("MagY: ");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("  ");
  Serial.print("MagZ: ");  
  Serial.println(IMU.getMagZ_uT(),6);
  */
} 
void loop() {
    if (Serial.available() > 0) {

    
    valInput = Serial.readString();
    Serial.print("I received: ");
    Serial.print(valInput);
 
    switch (valInput[0]) {
      // Input of "1" to "6" -> increase respective (1..6) values
      // Input of [q,w,e,r,t,y] -> decrease respective (1..6) values
      case '1': 
          automation(val1);
          accelprint();
        
        break;
      case 'q': 
        automation(valm);
        break;
      
      case '2': 
          automation(val2);
          accelprint();
        break;
      case 'w': 
        
          automation(val1);
          accelprint(); 
        break;
      
      case '3': 
              
        automation(val3);
        accelprint();          
        break;
      case 'e': 

        automation(val2);
        accelprint();    
        break;

      case '4':
        
        automation(val4);
        accelprint();           
        break;
      case 'r':
        
        automation(val3);
        accelprint();      
        break;

      case '5':
        
        automation(val5);
        accelprint();  
        break;
      case 't':
        
        automation(val4);
        accelprint();            
        break;

      case '<':
        for (i=0; i<6; i++) {
          val[i] = SERVOMIN;
        }
        break;
      case '>':
        for (i=0; i<6; i++) {
          val[i] = SERVOMAX;
        }
        break;
      case 'm':
        for (i=0; i<6; i++) {
            pwm.setPWM(i+1, 0, valm[i]); // added +1 to match PWM port numbering (pins 1..6 used)
            Serial.print(valm[i]);
            delay(10);
                      
         }  
          
        break;
        
        case '-':
        for (i=0; i<6; i++) {
          val[i] = max( val[i]-5, SERVOMIN );
        }
        break;
                
        case '+':
        for (i=0; i<6; i++) {
          val[i] = min( val[i]+5, SERVOMAX );
        }
        break;
        
      default: Serial.print(" No action taken");
    } // end switch statement
    


    // Update servo commands:\
    

  }
}

/*
 *     //if(a == 0){
      //  for (i=0; i<6; i++) {
            pwm.setPWM(i+1, 0, list[i]); // added +1 to match PWM port numbering (pins 1..6 used)
         }  
        } 

        
*/
