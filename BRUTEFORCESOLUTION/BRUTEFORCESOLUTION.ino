#include <Adafruit_PWMServoDriver.h>


/* =================================================================================================== 
 *  This code has been provided as an example to help you get started on your project. The objective 
 *  is to provide user input to the Arduino board and have the servo motors actuate. Several lines of 
 *  code are accredited to the Adafruit PWM Servo Driver Library example code. To use the Adafruit 
 *  PWM Servo Shield, be sure to add the Adafruit library to your Arduino IDE. 
 *  (Adafruit example: File menu > Examples > Adafruit PWM Servo Drivers Library > servo)
 *  
 *  Add Adafruit Library: In the Arduino IDE application select: Sketch menu > Include Libraries > 
 *  Manage Libraries. In the Library Manager window, search and install the "Adafruit PWM Servo 
 *  Driver Library".
 *  
 *  NOTE: Depending on your servo motor, the pulse width min/max may be different. Adjust to match 
 *  your servo motor.
 =================================================================================================== */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MPU9250.h"


const int SERVOMIN = 145; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX = 460; // 'maximum' pulse length count (out of 4096) 475
/*
const int SERVOMIN_1 = 129; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_1 = 507; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMIN_2 = 158; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_2 = 596; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMIN_3 = 143; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_3 = 565; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMIN_4 = 123; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_4 = 469; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMIN_5 = 154; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_5 = 615; // 'maximum' pulse length count (out of 4096) 475
const int SERVOMIN_6 = 142; // 'minimum' pulse length count (out of 4096) 175
const int SERVOMAX_6 = 544; // 'maximum' pulse length count (out of 4096) 475
*/
const int SERVOMID = floor((SERVOMAX+SERVOMIN)/2); // 'mid' pulse length count (out of 4096)
const int SERVOCHG = 20; // 'change' pulse length count
// maximum it can go for 180 degree is 350 steps
//but we cant do that because our range is not 350 steps, aka our max will be 460-145 = 340 so not all the way till 180 degree but somewhat close.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

String valInput; // Serial input var.
int i=0; // loop index var.
int val[6] = {SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID, SERVOMID};
int val1[6] = {265,300,165,295,185,165};
int val2[6] = {265,300,165,215,185,185};
int val3[6] = {185,300,205,215,185,285};
int val4[6] = {225,300,205,215,185,285};
int val5[6] = {165,300,205,215,185,245};
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
  status = IMU.begin();
  status = IMU.calibrateAccel();

}
/*
void draw() {

    if (mySerial.available() > 0 ) {
         
         if ( value != null ) {
              output.println(val);
         }
    }
}
*/
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

  //void draw(val)
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
        //val[0]= min( val[0]+SERVOCHG, SERVOMAX );
         //for (int j = 0; j<8; j++){
          //Serial.print(j);
          for (i=0; i<6; i++) {
             
             pwm.setPWM(i+1, 0, val1[i]); // added +1 to match PWM port numbering (pins 1..6 used)
             }
            
            accelprint();
            delay(3000);
          for (i=0; i<6; i++) {
             pwm.setPWM(i+1, 0, val2[i]); // added +1 to match PWM port numbering (pins 1..6 used)

            }
            
            accelprint();
            delay(200);
            
          for (i=0; i<6; i++) {
             pwm.setPWM(i+1, 0, val3[i]); // added +1 to match PWM port numbering (pins 1..6 used)
             
            }
            
            accelprint();
            delay(2000);
          for (i=0; i<6; i++) {
             pwm.setPWM(i+1, 0, val4[i]); // added +1 to match PWM port numbering (pins 1..6 used)
             
            }
            
            accelprint();
            delay(2000);
          for (i=0; i<6; i++) {
             pwm.setPWM(i+1, 0, val5[i]); // added +1 to match PWM port numbering (pins 1..6 used)
             
            }
            accelprint();
        //for(i =0;i<5;i++) {
          //val[0]= min(val[0]+SERVOCHG, SERVOMAX );
          //delay(1000);
        //}
        //delay
          
        break;
      case '2':
          for (i=0; i<6; i++) {
             pwm.setPWM(i+1, 0, val2[i]); // added +1 to match PWM port numbering (pins 1..6 used)
            }
        break;
      case 'm':
        for (i=0; i<6; i++) {
          if (i == 0){
            val[i] = 270;}
          if (i == 1){
            val[i] = 300;}
          if (i == 2){
            val[i] = 197;}
          if (i == 3){
            val[i] = 235;}
          if (i == 4){
            val[i] = 175;}
          if (i == 5){
            val[i] = 170;}
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

    // Update servo commands:
    for (i=0; i<6; i++) {
      pwm.setPWM(i+1, 0, val[i]); // added +1 to match PWM port numbering (pins 1..6 used)
    }
  }
}
