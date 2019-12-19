//CH1 is used for video REC and SHUTTER, idle is in the centre. Moving the stick to one extreme triggers REC. Move again to stop recording. Moving the stick the other way half-presses the shutter then full presses the shutter as the stick reaches the end of the travel. This allows simultaneous video and still capture if your camera supports this feature. 
//CH2 is used for ZOOM, idle is in the centre. Moving the stick zooms in and out. The unit supports multiple zoom speeds however most cameras only support 2 speed zoom-in and 2 speed zoom-out. 
//CH3 is used to switch the camera on and off, this can be useful to save power. Momentarily moving the stick switches the camera off, repeat to switch on again. Note: The camera must be switched on for this to work. 
//With the MULTI system, only one signal can be sent to the camera at a time, so return all servo inputs to "idle" when not in use

//allow PWM to be up or down for PWM_DELAY > 0 millis
//after this, PWM is reset to center
#define GENT_WIRE
#define PWM_DELAY 500
#define PWM_DELAY_DEFAULT 1000
#define PWM_DELAY_STILL 200

//pw1
#define CAM_IDLE 1500
#define CAM_SHOOT_STILL_SINGLE 1900
#define CAM_SHOOT_STILL_CONT 2000
#define CAM_REC_ON 1100
#define CAM_REC_OFF 1500

//pw2
#define CAM_ZOOM_OUT 1100
#define CAM_ZOOM_IN 1900

//pw3
#define CAM_POWER_ON 1900
#define CAM_POWER_OFF 1100
