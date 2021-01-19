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
char motor_Des_Dir[4];
char motor_last_Dir[4];

 
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
// encoser function prototype
void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2);
void Encoder_Angle_Update (Motor_ID encodername);
// Motor function prototype
void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber);
void Motor_Forward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Backward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Brake(Motor_ID motorname);
char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);
// limit_switch function prototype
void Limit_Sw_Init ( Motor_ID limitname ,char pinnumber);
void LIMIT_RD_ISR();
void LIMIT_RU_ISR();
void LIMIT_LD_ISR();
void LIMIT_LU_ISR();
// Motor function prototype
void Stand_Position (MOTOR_SPEED Speed);
void Step_Forward (MOTOR_SPEED Speed);
void Step_Backward (MOTOR_SPEED Speed);
void Sit_Position (MOTOR_SPEED Speed);
void Step_Test (MOTOR_SPEED Speed);
char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed);

void Direction_Detect(int desired_angle,Motor_ID motorname );                     
int Backlash_eliminator(int desired_angle , Motor_ID motorname);
char move_motor_to_edited( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);
void Main_Init();

void setup() {
  Serial.begin(115200);
  //  Encoders initializations
  Encoder_Init (Motor_R_Up,22,23); // Motor_R_Down
  Encoder_Init (Motor_R_Down,26,27);
  //Encoder_Init (Motor_L_Down,22,23);
  //Encoder_Init (Motor_L_Up,22,23);
  //  Motor initializations
  Motor_Init (Motor_R_Up, 18 , 19, 4); // 18 is IN1 ,, 19 is IN2  Motor_R_Up
  Motor_Init (Motor_R_Down, 32 , 33, 25); // 32 is is IN1 , 33 is IN2 Motor_R_Down
  //Motor_Init (Motor_L_Down, 18 , 19, 4);
  //Motor_Init (Motor_L_Up, 18 , 19, 4);
  //Step_Test(HIGH_SPEED); 
  
}
void loop() {

  //move_motor_to(Motor_R_Up,40,HIGH_SPEED);
 //move_motor_to(Motor_R_Down,0,HIGH_SPEED);

  Encoder_Angle_Update(Motor_R_Up);
   Serial.println(Motor_Angle[Motor_R_Up]);
   
  // Serial.println(pulse_counter[Motor_R_Down]);

}

void Main_Init(){
  /*
      void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
      void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2) Pin1->clk , pin2->Dt
      void Limit_Sw_Init ( Motor_ID limitname ,char pinnumber)
  */
  Motor_Init   (  Motor_R_Down  , 36  , 39 , 19);
  Encoder_Init (  Motor_R_Down  , 23  , 21     );
  Limit_Sw_Init(  Motor_R_Down  ,  26          );

  Motor_Init   (  Motor_R_Up    , 35  , 34 , 12);
  Encoder_Init (  Motor_R_Up    , 22  , 18     );
  Limit_Sw_Init(  Motor_R_Up    , 27           );

  
  Motor_Init   (  Motor_L_Down  , 0   , 4  , 2 );
  Encoder_Init (  Motor_L_Down  , 5   , 13     );
  Limit_Sw_Init(  Motor_L_Down  , 14           );

  Motor_Init   (  Motor_L_Up    , 16  , 17 , 15);
  Encoder_Init (  Motor_L_Up    , 33  , 32     );
  Limit_Sw_Init(  Motor_L_Up    , 25           );
  
  }
