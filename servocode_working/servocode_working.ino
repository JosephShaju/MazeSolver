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
const int SERVOCHG = 2; // 'change' pulse length count
// maximum it can go for 180 degree is 350 steps
//but we cant do that because our range is not 350 steps, aka our max will be 460-145 = 340 so not all the way till 180 degree but somewhat close.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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
