//Channel 1:
// CH1 used for Camera ON-OFF function. 
//
// UP    -  Camera ON
// DOWN    -   Camera OFF
//
//Channel 2:
// This channel use for RECStart Stop/Take Picture.
//
// UP   -  Take Picture
// CENTER   -  IDLE (stop recording)
// DOWN   -   (start recording)
//
//Channel 3:
// CH3 use for Zoom function. Zoom function support 2 zoom speed.
// We recommended stick (like as throttle)
//
//Output:
// Out channel is use for LED indicator on following status. 
//
//Led:
// Continuous Flash while recording.
// Single Flash when take picture

//note connections
//
//pw1 to CH2 
//pw2 to CH3
//pw3 to CH1


//allow PWM to be up or down for PWM_DELAY > 0 millis
//after this, PWM is reset to center. 0 -> no reset to center
#define RC_SHUTTER
#define PWM_DELAY 200
#define PWM_DELAY_DEFAULT 1000
#define PWM_DELAY_STILL 200

//pw1
#define CAM_IDLE 1500
#define CAM_SHOOT_STILL_SINGLE 1350
#define CAM_SHOOT_STILL_CONT 2000
#define CAM_REC_ON 1900
#define CAM_REC_OFF 1500

//pw2
#define CAM_ZOOM_OUT 1900
#define CAM_ZOOM_IN 1100

//pw3
#define CAM_POWER_ON 1900
#define CAM_POWER_OFF 1100
