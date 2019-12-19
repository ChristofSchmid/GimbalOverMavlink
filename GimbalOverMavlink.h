/* This file contains defines and declarations for the Mavlink protocol and the mavlink decoder*/

#define TELEMETRY_SPEED  115200          /* MAVLink telemetry speed. Use AutoQuad settings to match */
#define MAVCOM MAVLINK_COMM_0

#define SERVOPIN_0 9 //Tilt output PWM for CGO3 3axis gimbal
#define SERVOPIN_1 10 //Shutter
#define SERVOPIN_2 11 //Zoom
#define SERVOPIN_3 12 //on/off RX100


#define PW_INIT 500 //Yuneec specific PWM to init external CGO3 tilt port
#define PW_LOW 1100
#define PW_HI  1900
#define PW_MID 1500

//pw0
#define TILT_ANGLE_MIN -85
#define TILT_ANGLE_MAX 135

//pw1 - pw3 defines moved to cam/hw specific .h file


#define M_PI      3.14159265f
#define DEG_TO_RAD    (M_PI / 180.0f)
#define RAD_TO_DEG    (180.0f/ M_PI)
#define NAV_EQUATORIAL_RADIUS (6378.137 * 1000.0)

unsigned long timer_sys = 0;
unsigned long timer_1 = 0;
static uint8_t hRX=6;                    /* software serial port for debug */
static uint8_t hTX=5;                    

static uint8_t bRX=7;                    /* software serial port for com to BaseCam */
static uint8_t bTX=8;    

float TotalHeading = 0;
float LastHeading = 0;
float CamHeading =0;
float CamTilt =0;

static uint8_t YawDirection = 0;
static uint8_t YawTurnCount = 0;

int potVal;
boolean GimbalState = false;
boolean CamOn = false;
boolean CamRec = false; 
boolean HearBeatLedOn = false;

int PitchRatioUp = (PW_MID - PW_LOW) / (-TILT_ANGLE_MIN); // 1° = 10 micro S
int dZeroPitchUp = 0 - TILT_ANGLE_MIN;
int PitchRatioDn = (PW_HI - PW_MID) / (TILT_ANGLE_MAX); // 1° = 10 micro S
int dZeroPitchDn = 0 + TILT_ANGLE_MAX;

float pw0 = PW_INIT;
float pw1 = PW_MID;
float pw2 = PW_MID;
float pw3 = CAM_POWER_ON;

static uint8_t Cam_Unit = 0;

static uint8_t GimbalStatus;
static uint8_t VideoOn =0;
static uint8_t PicShoot =0;
unsigned long mDelay = PWM_DELAY;

/* Global variables */
static uint8_t counter = 0;                        /* General counter */

static bool     mavbeat = 0;
static uint8_t  aq_mav_type;
static uint8_t  aq_mav_system; 
static uint8_t  aq_mav_component;
static bool     mavlink_request = 0;
static uint16_t messageCounter;
static bool     mavlink_active;
int ioCounter = 0;


