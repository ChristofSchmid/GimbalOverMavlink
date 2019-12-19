// SBGC routines to feed the basecam controller over serial for tilt and pan.

#define SBGC_CMD_GYRO_CORRECTION 75
void GimbalCenter(){

  //reset BaseCam

  SerialCommand cmd;
  cmd.init(SBGC_CMD_GYRO_CORRECTION);
  cmd.writeByte(0); // 0 - main, 1 - frame IMU
  cmd.writeWord(0); // offset X
  cmd.writeWord(0); // offset Y
  cmd.writeWord(0); // offset Z
  cmd.writeWord(0); // heading offset, 0.001 degrees
  sbgc_parser.send_cmd(cmd);
  cmd.writeByte(1); // 0 - main, 1 - frame IMU
  sbgc_parser.send_cmd(cmd);
  
  //Pitch PW
  pw0 = PW_MID; 
  Servo0.writeMicroseconds(pw0);  // set PWM 0 
 	
 	// Move camera to initial position (all angles are zero)
	// Set speed 30 degree/sec
  SBGC_cmd_control_t c = { 0, 0, 0, 0, 0, 0, 0 };
  c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.speedROLL = c.speedPITCH = c.speedYAW = 30 * SBGC_SPEED_SCALE;
	SBGC_cmd_control_send(c, sbgc_parser);
	blink_led(1); 
}


void GimbalControl(float Pitch, float Yaw) {
  
  if (!GimbalState){
    return;
  }
//  Walkera PWM Werte
//  pw0 = PW_MID;
//  if( Pitch < 0){
//    pw0 = PW_MID + (PitchRatioDn * (-Pitch) );
//  }
//  if( Pitch > 0){
//    pw0 = PW_MID - (PitchRatioUp * Pitch );
//  }
// 
//  Servo0.writeMicroseconds(pw0);  // set PW0

 	SBGC_cmd_control_t c = { 0, 0, 0, 0, 0, 0, 0 };
	c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.anglePITCH = SBGC_DEGREE_TO_ANGLE(-Pitch);
	c.angleYAW = SBGC_DEGREE_TO_ANGLE(Yaw);
	SBGC_cmd_control_send(c, sbgc_parser);
}

void GimbalMotorsOn(){
  sbgc_parser.send_command(SBGC_CMD_MOTORS_ON, NULL, 0, 0);
  //delay(1000);
  GimbalControl(0.0,0.0);
}

void GimbalMotorsOff(){
  sbgc_parser.send_command(SBGC_CMD_MOTORS_OFF, NULL, 0, 0);
  //delay(500);
 
} 

void TestGimbal(){

	SBGC_cmd_control_t c = { 0, 0, 0, 0, 0, 0, 0 };

	// Move camera to initial position (all angles are zero)
	// Set speed 30 degree/sec
	c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.speedROLL = c.speedPITCH = c.speedYAW = 30 * SBGC_SPEED_SCALE;
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(3000);
  
	blink_led(1);
	/////////////////// Demo 1. PITCH and YAW gimbal by 40 and 30 degrees both sides and return back.
	// Actual speed depends on PID setting.
	// Whait 5 sec to finish
	c.mode = SBGC_CONTROL_MODE_ANGLE;
	c.anglePITCH = SBGC_DEGREE_TO_ANGLE(40);
	c.angleYAW = SBGC_DEGREE_TO_ANGLE(30);
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(4000);

	c.anglePITCH = SBGC_DEGREE_TO_ANGLE(-40);
	c.angleYAW = SBGC_DEGREE_TO_ANGLE(-30);
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(8000);

	// .. and back
	c.anglePITCH = 0;
	c.angleYAW = 0;
	SBGC_cmd_control_send(c, sbgc_parser);
	delay(4000);
}
