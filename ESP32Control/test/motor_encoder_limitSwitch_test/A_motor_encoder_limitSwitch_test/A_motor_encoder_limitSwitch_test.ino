#define IN1 0 // First pin for motor driver
#define IN2 1 // Second pin for motor driver
#define ENA 2 // Enable pin for motor driver

#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder

//#define freq 5000 // 200 micro second
//#define resolution  2 // resolution of the duty cycle

//#define Forward 0
//#define backward 1
//#define Same 2
#define Backlash_angle 5

typedef enum            // enum to give every motor an ID
{
  Motor_R_Down = 0,     // Right Down motor ID = 0
  Motor_R_Up = 1,       // Right UP motor ID = 1
  Motor_L_Down = 2,     // Left Down motor ID = 2
  Motor_L_Up = 3        // Left UP motor ID = 3
} Motor_ID;

typedef enum              // enum to levelization the speed  // the analogWrite() Fn take the speed as a Char " max 255"
{ LOW_SPEED = 128,        // Low speed indicate the quarter of the max speed
  MEDIUM_SPEED = 192,     // MEDIUM speed indicate  3/4 of the max speed
  HIGH_SPEED = 255        // HIGH speed indicate the max speed
} MOTOR_SPEED;

typedef enum {
  Same = 0,
  BackWard = 1,
  Forward = 2
            //Null=3          // used only in the begining of the motion

} Motor_Direction;

Motor_Direction motor_Des_Dir[4];
Motor_Direction motor_last_Dir[4] = {Same, Same, Same, Same};

int interrupt_Flags[4] = {0, 0, 0, 0};

unsigned char Motor_Pins[4][3];       // every motor  have 3 pins " IN1 , IN2 , ENA "
unsigned char Limit_Sw[4];            //limit switch pins number ,, 1 pin for each

int Motor_Angle[4] = {0, 0, 0, 0}; // TO hold the Current angle of the motor
unsigned char Encoder_Pins[4][2]; // Pins which each encoder use
int pulse_counter[4] = {0, 0, 0, 0}; // counter pulses




void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber);
void Motor_Forward(MOTOR_SPEED Speed , Motor_ID motorname);
void Motor_Backward(MOTOR_SPEED Speed , Motor_ID motorname);
void Motor_Brake(Motor_ID motorname);


void move_motor_to_Indiv(Motor_ID motorname, int desired_angle, MOTOR_SPEED Speed );
char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);
void Calibiration();
void Direction_Detect(int desired_angle, Motor_ID motorname );
int Backlash_eliminator(int desired_angle , Motor_ID motorname);
char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     MOTOR_SPEED Speed);

                     

void  ENCODER_RD_ISR1(void);
void  ENCODER_LU_ISR1(void);
void  Encoder_Init (Motor_ID encodername, char pinnumber1, char pinnumber2);

void  Limit_Sw_Init ( Motor_ID limitname , char pinnumber);
void  LIMIT_RD_ISR(void);
void  LIMIT_RU_ISR(void);
void  LIMIT_LD_ISR(void);
void  LIMIT_LU_ISR(void);

void setup() {
  Serial.begin(115200);
  Motor_Init   (  Motor_R_Down    , 24  , 26 , 3);
  Encoder_Init (Motor_R_Down, A4, A5);
  // Encoder_Init (Motor_L_Up,A6,A7);
   //Limit_Sw_Init ( Motor_R_Down , A0) ;

}

void loop() {
  // testing Forward , backward & brake functions with encoder      result : verified 
  /*Motor_Forward(LOW_SPEED, Motor_R_Down);
  delay(5000);
  Serial.print(" Motor_R_Down = ");
  Serial.println(Motor_Angle[Motor_R_Down]);
  Motor_Brake(Motor_R_Down);
  delay(5000);
  Motor_Backward(LOW_SPEED, Motor_R_Down);
  delay(5000);
  Motor_Brake(Motor_R_Down);
  delay(5000);
  Serial.print(" Motor_R_Down = ");
  Serial.println(Motor_Angle[Motor_R_Down]);*/

           // testing the limit switch with motor                 result : verified 
    /*while (interrupt_Flags[Motor_R_Down] != 1) {
      Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
      Serial.println(interrupt_Flags[Motor_R_Down]);
    }  Motor_Brake(Motor_R_Down);

      Serial.println(interrupt_Flags[Motor_R_Down]);*/



        /*    // testing move motor to Function                   result : verified 

    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
    //Serial.print("\t Motor_L_Up = ");
    //Serial.print(pulse_counter[Motor_L_Up]);
    //Serial.println("");
    move_motor_to( Motor_R_Down , 100 , MEDIUM_SPEED);
    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);*/


  

       // testing  move_motor_to_Indiv , Detect motor direction & backlash eliminatpr  Functions        result : need some modification
    move_motor_to_Indiv(Motor_R_Down, 100, MEDIUM_SPEED );
    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
    delay(5000);
    move_motor_to_Indiv(Motor_R_Down, 0, MEDIUM_SPEED );
    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
    delay(5000);
    move_motor_to_Indiv(Motor_R_Down, 360, MEDIUM_SPEED );
    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
    delay(5000);
    move_motor_to_Indiv(Motor_R_Down, 1, MEDIUM_SPEED );
    Serial.print(" Motor_R_Down = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
    delay(5000);
  



}
