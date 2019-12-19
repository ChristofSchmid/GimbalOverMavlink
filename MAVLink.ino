#define MAVLINK_COMM_NUM_BUFFERS 1
//#define MAVLINK_USE_CONVENIENCE_FUNCTIONS
//#define MAVLINK_MAX_DIALECT_PAYLOAD_SIZE 101    // reduced from 254, defined in version.h


//BetterStream	*mavlink_comm_0_port;
//BetterStream	*mavlink_comm_1_port;
//mavlink_system_t mavlink_system = {MAV_AUTOPILOT_AUTOQUAD,MAV_TYPE_QUADROTOR,0,0};

#include <mavlink.h>


uint8_t sysid = 200;
uint8_t compid = 100;
 


static int packet_drops = 0;
static int parse_error = 0;

void read_mavlink(){
  
  mavlink_message_t msg; 
  mavlink_status_t status;
  boolean LedState; 
  
  while(Serial.available() > 0) { 
    uint16_t c = Serial.read();
    /* grab msgID and msg */
      if(mavlink_parse_char(MAVCOM, c, &msg, &status)) {
       messageCounter = 0; 
       mavlink_active = 1;
       
       switch(msg.msgid)           /* Handle msg */
       {
        case MAVLINK_MSG_ID_HEARTBEAT:
//           LedState = digitalRead(LedPin);
//           digitalWrite(LedPin,!LedState);
//           break;
//          
          case MAVLINK_MSG_ID_COMMAND_LONG:
              //DPL("Command Long"); 
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_DO_SET_SERVO){
              
              }
              
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_DO_CONTROL_VIDEO){
                float ZoomIn = mavlink_msg_command_long_get_param5(&msg);
                float ZoomOut = mavlink_msg_command_long_get_param6(&msg);
                if (ZoomIn > 0) {VideoZoomIn();}
                if (ZoomOut > 0) {VideoZoomOut();}
                mDelay = 200; // allow 2/10 sec to zoom
                
              }
                                        
              /* Start image capture sequence |Duration between two consecutive pictures (in seconds)| Number of images to capture total - 0 for unlimited capture| Resolution in megapixels (0.3 for 640x480, 1.3 for 1280x720, etc)|  */
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_IMAGE_START_CAPTURE){
                int TimeStep = 0;
                int TotalPics = 1;
                #ifdef SERDB
                  DPL (F("IMAGE_START_CAPTURE"));
                #endif  
                StillCaptureStart(TimeStep, TotalPics);
              }
              
              /* Stop image capture sequence |Reserved| Reserved|  */
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_IMAGE_STOP_CAPTURE){
                #ifdef SERDB
                  DPL (F("IMAGE_STOP_CAPTURE"));
                #endif
                StillCaptureStop();
              }

              /* Starts video capture |Camera ID (0 for all cameras), 1 for first, 2 for second, etc.| Frames per second| Resolution in megapixels (0.3 for 640x480, 1.3 for 1280x720, etc)|  */
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_VIDEO_START_CAPTURE){
                #ifdef SERDB
                  DPL (F("VIDEO_START_CAPTURE"));
                #endif
                VideoCaptureStart();
              } 
              
              /* Stop the current video capture |Reserved| Reserved|  */
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_VIDEO_STOP_CAPTURE){
              #ifdef SERDB
                DPL (F("VIDEO_STOP_CAPTURE"));
              #endif
                VideoCaptureStop();
              }
              
              /* Create a panorama at the current position |Viewing angle horizontal of the panorama (in degrees, +- 0.5 the total angle)| Viewing angle vertical of panorama (in degrees)| Speed of the horizontal rotation (in degrees per second)| Speed of the vertical rotation (in degrees per second)|  */
              if ( mavlink_msg_command_long_get_command(&msg) == MAV_CMD_PANORAMA_CREATE){
              
              }
           

              #ifdef SERDB
                printDebugInfo();
              #endif  
              
              break;
          
         
          case MAVLINK_MSG_ID_SET_GIMBAL:
              #ifdef SERDB
                DPL("Set Gimbal"); 
              #endif
              GimbalStatus = mavlink_msg_set_gimbal_get_status(&msg);
              CamHeading = mavlink_msg_set_gimbal_get_cam_heading(&msg);
              CamTilt = mavlink_msg_set_gimbal_get_cam_tilt(&msg);
          
//              if ( (GimbalStatus == 1) && (GimbalState == false) ){
//                 #ifdef SERDB
//                  DPL (F("GIMBAL ON"));
//                 #endif
//                 //GimbalMotorsOn();
//                 GimbalCenter();
//                 GimbalState = true;
//                 //PowerCamOn();
//              }         
//              
//              if ( (GimbalStatus == 0) && (GimbalState == true) ){
//                 GimbalCenter();
//                 //delay(2000);
//                 #ifdef SERDB
//                  DPL (F("GIMBAL OFF"));
//                 #endif
//                 //GimbalMotorsOff();
//                 GimbalState = false;
//                 //PowerCamOff();
//              }
              CamHeading = CalYaw(CamHeading); //shortest way for new heading. 
              GimbalControl(CamTilt, CamHeading);
              #ifdef SERDB
                 printDebugInfo();
              #endif  

         
//              #ifdef SERDB
//                printDebugInfo();
//              #endif  
                            
              break;

          case MAVLINK_MSG_ID_ATTITUDE:
  
              break;
            
       default:
           //Do nothing
//           #ifdef SERDB
//             DPN (F("Mavlink Message Nr. :  "));
//             DPN ("\t");    
//             DPN (msg.msgid);
//             DPN ("\t");  
//             DPL ();  
//           #endif
           break;
           
              }      
       }
       
  } //end while Serial
  // Update global packet drops counter
  packet_drops += status.packet_rx_drop_count;
  parse_error += status.parse_error;
  
} /* end read_mavlink */


