//activate debug, uncomment
//#define SERDB

//what Hardware to use
//#include "GentWire.h"
#include "RcShutter.h"


#define potPin 0
#define LedPin 13

#undef PROGMEM 
#define PROGMEM __attribute__(( section(".progmem.data") )) 

//#undef PSTR 
//#define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];})) 

#define CONFIG  1       // Support for different configurations for your different frames. The configuration defines the LED type, LED order and the Current Sensor values
#define EXTRAMAVMSG       // Option: Set when using a special message in aq_mavlink to transmitt AQ's extra messages, comment (//) to disable
#include "Arduino.h"
#include <math.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include "GimbalOverMavlink.h"            /* Definitions */

#include <SBGC.h> 
#include <SBGC_Arduino.h> 
#include <Servo.h>

Servo Servo0;
Servo Servo1;
Servo Servo2;
Servo Servo3;

#ifdef SERDB
    SoftwareSerial dbSerial(hRX,hTX);    /* Debug serial port (rx port,tx port) */
    #define DPL dbSerial.println 
    #define DPN dbSerial.print
#endif

SoftwareSerial bcSerial(bRX,bTX);    /* Baeacm over serial (rx port,tx port) */

void setup() 
{

Serial.begin(TELEMETRY_SPEED);        /* Initialize Mavlink Serial port, speed */
pinMode(LedPin, OUTPUT);        // Set LED as an output

#ifdef SERDB
  dbSerial.begin(115200);
  DPL("mavlink monitor");    
#endif  


  /* initialize interupt timer for events */  
//MsTimer2::set(100, timerEvent);  /* set timer on 100ms (10Hz) interval */
//MsTimer2::start();

bcSerial.begin(115200);
SBGC_setup(&bcSerial); 

Servo0.attach(SERVOPIN_0);
Servo1.attach(SERVOPIN_1);
Servo2.attach(SERVOPIN_2);
Servo3.attach(SERVOPIN_3);

//Init CGO3 tilt port with pw 500
Servo0.writeMicroseconds(PW_INIT);  // INIT pw port
delay(10);

//Center PWM Gimbal
Servo0.writeMicroseconds(PW_MID);  // set PW0
//Zoom in
Servo3.writeMicroseconds(CAM_POWER_ON);
Servo0.writeMicroseconds(CAM_IDLE);  // Zoom in 
delay(2000);
Servo2.writeMicroseconds(CAM_ZOOM_IN);  // Zoom in 
delay(3000);
CamIdle();
StillCaptureStart(1, 1);
SetPwm();

GimbalCenter();
GimbalState = true;
//Turn Gimbal Motors off at boot for easy liftoff with 3Axis Gimbal
//Send serial command to BasCam 10 times to make sure Bascam receive the command after boot.

//for (int i =0; i<10; i++) { 
//  GimbalMotorsOff();
//delay(500);
//}

timer_sys = millis();

} /* end */




void loop() 
{ 
  
  read_mavlink(); 
  if (SysTimer()) {
    CamIdle();
    mDelay = PWM_DELAY_DEFAULT; //default
   }
 
}


