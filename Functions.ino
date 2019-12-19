bool SysTimer(){
  int RetVal = 0;
  //skip CamIdle()
//  if (mDelay == 0){
//    return false;
//  }

    if ( (millis() - timer_sys) >= mDelay ) {
    timer_sys = millis();
    return true;
  }
  return false;
}

void printDebugInfo(){
#ifdef SERDB  
  DPN (F("Yaw in : "));
  DPN ("\t");    
  DPN (CamHeading);
  DPN ("\t");  
     
  DPN (F("Pitch in: "));
  DPN ("\t");    
  DPN (CamTilt);
  DPN ("\t");  
  //   DPL ();  
  DPN (F("PWM 0 (tilt): "));
  DPN ("\t");    
  DPN (pw0 );
  DPN ("\t");  
  
  DPN (F("PWM 1 (cam1): "));
  DPN ("\t");    
  DPN (pw1 );
  DPN ("\t");  
  
  DPN (F("PWM 2 (cam2): "));
  DPN ("\t");    
  DPN (pw2);
  DPN ("\t");  
  DPL ();  
#endif
}


//void CamPWM(){

//RC receiver (CH0=Record/AF/Shoot, CH1=SmoothZoom, CH2=Alt)
//This mode is identical to mode above about Channel 0. Channel1 (CH1) is used to control zoom of the camera. Channel2 (CH2) is used to execute User defined LANC command. Channel0/1/2 are sensible to pulse width coding signal and are controllable by RC receiver. Most RC transmitters/receivers are generating pulse width from 1 milliseconds (0%) to 2 milliseconds (100%) according to position of lever (throttle for example) on control panel of transmitter. Descriptions of lever position and how CR interpret it is shown in following table.
//
//Channel 0 (CH0) 
//Position (Pulse width) Feature 
//0..10% (0.9-1.1ms) Camera Standby/Power Off 
//10..40% (1.1-1.4ms) Toggle Movie Recording * 
//40..60% (1.4-1.6ms) Idle 
//60..70% (1.6-1.7ms) Autofocus (if enabled in Configuration software, 'Focus' selection) 
//70..90% (1.7-1.9ms) Single Shoot * 
//90..120% (1.9-2.1ms) Shoot Continuously 
//Channel 1 (CH1) 
//Position (Pulse width) Feature 
//0..40% (1.0-1.4ms) Zoom Out (Variable speed if camera support it) 
//40..60% (1.4-1.6ms) Idle 
//60..100% (1.6-2.0ms) Zoom In (Variable speed if camera support it) 
//Channel 2 (CH2) 
//Position (Pulse width) Feature 
//0..30% (0.9-1.3ms) User Defined LANC Command (Field 'At 30%' in Configuration software) 
//30..70% (1.3-1.7ms) Idle (Unlock for next command) 
//70..120% (1.7-2.2ms) User Defined LANC Command (Field 'At 70%' in Configuration software) 
//
//}



float CalYaw(float yaw){
//shortest way to new yaw
//shortest way to 0 yaw
//check for overflow at 32000 - TODO
float tLastHeading = ( (LastHeading/360) - int (LastHeading/360) ) * 360;
float h1 = yaw - tLastHeading;
float h2 = yaw - 360 - tLastHeading;
float h = min(h1,h2);
if( h > 0){
  YawDirection = 1;}
  else {
  YawDirection = -1;  
}

LastHeading = LastHeading + h;
return h;
}


void SetPwm() {
timer_sys = millis();

//Servo3.writeMicroseconds(pw3);  // set PWM 3 on/off
Servo2.writeMicroseconds(pw2);  // set PWM 2 zoom 
Servo1.writeMicroseconds(pw1);  // set PWM 1 rec/shutter

digitalWrite(LedPin,!digitalRead(LedPin));
       

}


void StillCaptureStart(int TimeStep, int TotalPics){
int ts = 0; //TimeStep
int tp = 1; //TotalPics 
#ifdef RC_SHUTTER
  if (CamRec){
  return;
  }
#endif

pw1 = CAM_SHOOT_STILL_SINGLE;
mDelay = PWM_DELAY_STILL;
SetPwm();

}

void StillCaptureStop(){
#ifdef RC_SHUTTER
  if (CamRec){
  return;
  }
#endif
pw1 = CAM_IDLE;  
SetPwm();

}

void VideoCaptureStart(){
if (!CamRec){
  pw1 = CAM_REC_ON;
  CamRec = true;
  mDelay = PWM_DELAY_STILL;
  SetPwm();
}

}
 
void VideoCaptureStop(){
if (CamRec){
  pw1 = CAM_REC_OFF;
  CamRec = false;
  mDelay = PWM_DELAY;
  SetPwm();
}

}

void VideoZoomIn(){
pw2 = CAM_ZOOM_IN;
SetPwm();

}

void VideoZoomOut(){
pw2 = CAM_ZOOM_OUT;
SetPwm();
}

void PowerCamOn(){
pw3 = CAM_POWER_ON;
CamOn = true;
mDelay = PWM_DELAY;
SetPwm();

}

void PowerCamOff(){
pw3 = CAM_POWER_OFF;
CamOn = false;
mDelay = PWM_DELAY;
SetPwm();

}

void CamIdle(){

#ifdef RC_SHUTTER
if (!CamRec){
  pw1 = CAM_IDLE; // Shutter/Rec
} 
pw2 = CAM_IDLE; // Zoom
//pw3 = CAM_POWER_ON; // always on
SetPwm();
#endif

#ifdef GENT_WIRE
pw1 = CAM_IDLE;
pw2 = CAM_IDLE;
pw3 = CAM_IDLE;
SetPwm();  
#endif

}
              


