/********************************************* Pins Configuration **************************************************/

/************ motor configuration **********/
#define Motor_R_Down_ENA 12
#define Motor_R_Down_IN1 11 
#define Motor_R_Down_IN2 10 

#define Motor_R_Up_ENA 9 
#define Motor_R_Up_IN1 8 
#define Motor_R_Up_IN2 7 

#define Motor_L_Down_ENA 3
#define Motor_L_Down_IN1 23
#define Motor_L_Down_IN2 25

#define Motor_L_Up_ENA 4 
#define Motor_L_Up_IN1 27 
#define Motor_L_Up_IN2 29


/***************** Limit Switch configuration ******************/

#define Motor_R_Down_LIMITSWITCH 33 // was 33
#define Motor_R_Up_LIMITSWITCH 37 //was 37
#define Motor_L_Down_LIMITSWITCH 41
#define Motor_L_Up_LIMITSWITCH 49




/************************ Encoder Configuration ************************/

#define Motor_R_Down_CLK A0
#define Motor_R_Down_DT A1 

#define Motor_R_Up_CLK A2
#define Motor_R_Up_DT A3

#define Motor_L_Down_CLK A4
#define Motor_L_Down_DT A5

#define Motor_L_Up_CLK A6
#define Motor_L_Up_DT A7



/************************************************************************************************************************************
 ***********************************************************************************************************************************/


/************************* Motor Driver Constants *************************/
#define IN1 0 // First pin for motor driver
#define IN2 1 // Second pin for motor driver
#define ENA 2 // Enable pin for motor driver
#define Backlash_angle 5


/************************** Encoder Constants  ***************************/
#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder









/********************************  Motor  ***********************************/

unsigned char Motor_Pins[5][4];       // every motor  have 3 pins " IN1 , IN2 , ENA " // was 4 , 3 indexes
int Motor_Angle[5]={0,0,0,0}; // TO hold the Current angle of the motor // was 4 indexes  


typedef enum            // enum to give every motor an ID
{
  Motor_R_Down=0,       // Right Down motor ID = 0 
  Motor_R_Up=1,         // Right UP motor ID = 1 
  Motor_L_Down=2,       // Left Down motor ID = 2
  Motor_L_Up=3          // Left UP motor ID = 3
}Motor_ID;


typedef enum {
  Same = 0,
  BackWard = 1,
  Forward = 2

} Motor_Direction;


typedef enum              // enum to levelization the speed  // the analogWrite() Fn take the speed as a Char " max 255"
{ LOW_SPEED = 128,        // Low speed indicate the quarter of the max speed
  MEDIUM_SPEED = 192,     // MEDIUM speed indicate  3/4 of the max speed
  HIGH_SPEED = 255        // HIGH speed indicate the max speed
} MOTOR_SPEED;


Motor_Direction motor_Des_Dir[5];  // was 4 indexes
Motor_Direction motor_last_Dir[5] = {Same, Same, Same, Same}; //was 4 indexes

// Basic movement Functions 
void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber);
void Motor_Forward(MOTOR_SPEED Speed , Motor_ID motorname);
void Motor_Backward(MOTOR_SPEED Speed , Motor_ID motorname);
void Motor_Brake(Motor_ID motorname);

// intemidiate Movement Function
void move_motor_to_Indiv(Motor_ID motorname, int desired_angle, MOTOR_SPEED Speed );  //
char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);       //
//void Calibiration();
void Motor_R_Down_Calibiration();
void Motor_L_Down_Calibiration();
void Motor_L_Up_Calibiration();
void Motor_R_Up_Calibiration();

void Direction_Detect(int desired_angle, Motor_ID motorname );
int Backlash_eliminator(int desired_angle , Motor_ID motorname);
void move_motors_to_F( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed);
void move_motors_to_B( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed);                     
char check_limits(Motor_ID motorname , int desired_angle);

                     
// Advance movement functions 
void Stand_Position (MOTOR_SPEED Speed);
void Step_Forward (MOTOR_SPEED Speed);
void Step_Backward (MOTOR_SPEED Speed);
void Sit_Position (MOTOR_SPEED Speed);
void Step_Test (MOTOR_SPEED Speed);




/********************** Encoder ***************************/

unsigned char Encoder_Pins[5][3];   // Pins which each encoder use //was 4 , 2 indexes 
float pulse_counter[5]={0,0,0,0};   // counter pulses //was 4 indexes


void Encoder_Init( Motor_ID  encodername , char pinnumber1 , char pinnumber2 );

void  ENCODER_LU_ISR(void);
void  ENCODER_LD_ISR(void);
void  ENCODER_RU_ISR(void);
void  ENCODER_RD_ISR(void);




/************************ Limit Switch **************************/
unsigned char Limit_Sw[5];            //limit switch pins number ,, 1 pin for each // was 4 indexes
char interrupt_Flags[5]={0,0,0,0}; //was 4 indexes

// limit_switch function prototype
void Limit_Sw_Init ( Motor_ID limitname ,char pinnumber);
void  LIMIT_RD_ISR(void);
void  LIMIT_RU_ISR(void);
void  LIMIT_LD_ISR(void);
void  LIMIT_LU_ISR(void);



  
/********* Timer Initialization  ********/
void Timer_Init(){
    pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);    // port B pin 25 
  analogWrite(2,255);   // sets up some other registers I haven't worked out yet
  REG_PIOB_PDR = 1<<25; // disable PIO, enable peripheral
  REG_PIOB_ABSR= 1<<25; // select peripheral B
  REG_TC0_WPMR=0x54494D00; // enable write to registers
  REG_TC0_CMR0=0b00000000000010011100010000000000; // set channel mode register (see datasheet)
  REG_TC0_RC0=1000000; // counter period 0.01 sec
  REG_TC0_RA0=30000000;  // PWM value
  REG_TC0_CCR0=0b101;    // start counter
  REG_TC0_IER0=0b00010000; // enable interrupt on counter=rc
  REG_TC0_IDR0=0b11101111; // disable other interrupts

  NVIC_EnableIRQ(TC0_IRQn); // enable TC0 interrupts  
  }

//int l;



MOTOR_SPEED SPEED_Global=LOW_SPEED; 

bool Stand_Position_Global=false;
bool Set_Position_Global=false;
bool Step_Forward_Global=false;
bool Step_Backward_Global=false;

bool Move_Separate_Global=true;

int Upper_Left_Link_Gloabal;
int Lower_Left_Link_Global;

int Upper_Right_Link_Global=0;
int Lower_Right_Link_Global=0;

/*************************************/
                                                  /**********     CHILD_EX = [0.0,1.0]
                                                                  SPEED=[2.0,3.0,4.0] 
                                                                  STAND_P = [5.0,6.0]
                                                                  SET_P = [7.0,8.0 ]
                                                                  STEP_BACKWORD= [9.0,10.0]
                                                                  STEP_fORWORD = [11.0,12.0]
                                                                  MOVE_SEPERATE = [13.0,14.0]
                                                                  
                                                  
                                                  *********/
      /*LOWER_LEFT =[ -1.0 : 91.0 ]  STEP=20 { -1.0 , 19.0 , 39.0 , 59.0 , 79.0 , 91.0 } L_L --> -1 --> 199
        LOWER_RIGHT =[ -2.0 : 92.0 ] STEP=20 { -2.0 , 18.0 , 38.0 , 58.0 , 78.0 , 92.0 } // L_R --> -2 -->198
        UPPER_LEFT =[ -35.0 : 85.0 ] STEP=25 { -35.0 , -10.0 , 15.0 , 40.0 , 65.0 , 85.0 } //U_L --> [-35,-10]-->[165,190]
        Upper_Right=[ -34.0 : 86.0 ]  STEP=25 { -34.0 , -9.0 , 16.0 , 41.0 , 66.0 , 86.0 } //U_R --> [-34,-9] -->[166,191]*/
                                                    
