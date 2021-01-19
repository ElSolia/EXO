#define IN1 0 // First pin for motor driver
#define IN2 1 // Second pin for motor driver
#define ENA 2 // Enable pin for motor driver
#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder
#define freq 5000 // 200 micro second
#define resolution  2 // resolution of the duty cycle 
unsigned char Motor_Pins[4][3];       // every motor  have 3 pins " IN1 , IN2 , ENA "
int Motor_Angle[4]={0,0,0,0}; // TO hold the Current angle of the motor 
unsigned char Encoder_Pins[4][2]; // Pins which each encoder use 
float pulse_counter[4]={0,0,0,0}; // counter pulses 
char lastStateCLK[4];  // variable to store the last state of the pin CLK to 
char currentStateCLK[4];
unsigned char Limit_Sw[4];            //limit switch pins number ,, 1 pin for each

typedef enum            // enum to give every motor an ID
{
  Motor_R_Down=0,       // Right Down motor ID = 0 
  Motor_R_Up=1,         // Right UP motor ID = 1 
  Motor_L_Down=2,       // Left Down motor ID = 2
  Motor_L_Up=3          // Left UP motor ID = 3
}Motor_ID;

typedef enum            //enum to determine the Direction 
{
  Brake,
  Forward,
  Backward,
}Direction_Mode;

typedef enum              // enum to levelization the speed  // the analogWrite() Fn take the speed as a Char " max 255" 
{ LOW_SPEED=1,        // Low speed indicate the quarter of the max speed 
  MEDIUM_SPEED=2,     // MEDIUM speed indicate the half of the max speed
  HIGH_SPEED=3          // HIGH speed indicate the max speed
  }MOTOR_SPEED;

void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2);
void Encoder_Angle_Update (Motor_ID encodername);
void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber);
void Motor_Forward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Backward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Brake(Motor_ID motorname);
char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);
char a ,  b ;

void setup() {
  Serial.begin(115200);
  Encoder_Init (Motor_L_Up,22,23);
  Motor_Init (Motor_L_Up, 18 , 19, 4);

  
}
void loop() {


   move_motor_to(Motor_L_Up,360,HIGH_SPEED);
   Serial.println(Motor_Angle[Motor_L_Up]);  
   

}
