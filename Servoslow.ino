#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MPU9250.h"
const int SERVOMIN = 145; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX = 460; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMID = floor((SERVOMAX+SERVOMIN)/2); // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 2; // 'change' pulse length count
// maximum it can go for 180 degree is 350 steps
//but we cant do that because our range is not 350 steps, aka our max will be 460-145 = 340 so not all the way till 180 degree but somewhat close.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
MPU9250 IMU(Wire,0x68);
int status;
String valInput; // Serial input var.
int i=0; // loop index var.
//int val[6] = {SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID}; // PWM var
int val[6] = {270,300,197,235,175,170};
int a = 0;
int tim = 15;
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
  status = IMU.begin();
  status = IMU.calibrateAccel();

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
        for(i=0; i<20; i++){
          val[0]= min( val[0]+SERVOCHG, SERVOMAX );
          pwm.setPWM(1, 0, val[0]);
          Serial.print(val[0]);
          delay(tim);
        }
        accelprint();

        break;
      case 'q': 
       for(i=0; i<20; i++){
          val[0]= min( val[0]-SERVOCHG, SERVOMAX );
          pwm.setPWM(1, 0, val[0]);
          Serial.print(val[0]);
          delay(tim);
        }
        break;

      case '2': 
        for(i=0; i<20; i++){
          val[1]= min( val[1]+SERVOCHG, SERVOMAX );
          pwm.setPWM(2, 0, val[1]);
          Serial.print(val[1]);
          delay(tim);
        }        
        break;
      case 'w': 

        for(i=0; i<20; i++){
          val[1]= max( val[1]-SERVOCHG, SERVOMIN );
          pwm.setPWM(2, 0, val[1]);
          Serial.print(val[1]);
          delay(tim);
        }       
        break;

      case '3': 

        for(i=0; i<20; i++){
          val[2]= min( val[2]+SERVOCHG, SERVOMAX );  
          pwm.setPWM(3, 0, val[2]);
          Serial.print(val[2]);
          delay(tim);
        }              
        break;
      case 'e': 

        for(i=0; i<20; i++){
          val[2]= max( val[2]-SERVOCHG, SERVOMIN );
          pwm.setPWM(3, 0, val[2]);
          Serial.print(val[2]);
          delay(tim);
        }               
        break;

      case '4':

        for(i=0; i<20; i++){
          val[3]= min( val[3]+SERVOCHG, SERVOMAX );
          pwm.setPWM(4, 0, val[3]);
          Serial.print(val[3]);
          delay(tim);
        }                  
        break;
      case 'r':

        for(i=0; i<20; i++){
          val[3]= max( val[3]-SERVOCHG, SERVOMIN );
          pwm.setPWM(4, 0, val[3]);
          Serial.print(val[3]);
          delay(tim);
        }          
        break;

      case '5':

        for(i=0; i<20; i++){
          val[4]= min( val[4]+SERVOCHG, SERVOMAX );
          pwm.setPWM(5, 0, val[4]);
          Serial.print(val[4]);
          delay(tim);
        }          
        break;
      case 't':

        for(i=0; i<20; i++){
          val[4]= max( val[4]-SERVOCHG, SERVOMIN );
          pwm.setPWM(5, 0, val[4]);
          Serial.print(val[4]);
          delay(tim);
        }              
        break;

      case '6':

        for(i=0; i<20; i++){
          val[5]= min( val[5]+SERVOCHG, SERVOMAX );
          pwm.setPWM(6, 0, val[5]);
          Serial.print(val[5]);
          delay(tim);
        }                
        break;
      case 'y':

        for(i=0; i<20; i++){
          val[5]= max( val[5]-SERVOCHG, SERVOMIN );
          pwm.setPWM(6, 0, val[5]);
          Serial.print(val[5]);
          delay(tim);
        }            
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
            pwm.setPWM(i+1, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
            Serial.print(val[i]);
            delay(300);                     
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

    Serial.print(" Servo values = [");
    for (i=0; i<6; i++) {
      Serial.print(val[i]);
      Serial.print(" ");
    }
    Serial.println("]");

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
