#define IN1 0 // First pin for motor driver
#define IN2 1 // Second pin for motor driver
#define ENA 2 // Enable pin for motor driver

#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder

//#define freq 5000 // 200 micro second
//#define resolution  2 // resolution of the duty cycle 

#define Forward 0 
#define backward 1
#define Same 2 
#define Backlash_angle 

char motor_Des_Dir[4];
char motor_last_Dir[4];

char interrupt_Flags[4]={0,0,0,0};

unsigned char Motor_Pins[4][3];       // every motor  have 3 pins " IN1 , IN2 , ENA "

int Motor_Angle[4]={0,0,0,0}; // TO hold the Current angle of the motor 
unsigned char Encoder_Pins[4][2]; // Pins which each encoder use 
int pulse_counter[4]={0,0,0,0}; // counter pulses

typedef enum            // enum to give every motor an ID
{
  Motor_R_Down=0,       // Right Down motor ID = 0 
  Motor_R_Up=1,         // Right UP motor ID = 1 
  Motor_L_Down=2,       // Left Down motor ID = 2
  Motor_L_Up=3          // Left UP motor ID = 3
}Motor_ID;

typedef enum              // enum to levelization the speed  // the analogWrite() Fn take the speed as a Char " max 255" 
{ LOW_SPEED=128,          // Low speed indicate the quarter of the max speed 
  MEDIUM_SPEED=192,       // MEDIUM speed indicate the half of the max speed
  HIGH_SPEED=255          // HIGH speed indicate the max speed
  }MOTOR_SPEED;

void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber);
void Motor_Forward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Backward(MOTOR_SPEED Speed ,Motor_ID motorname);
void Motor_Brake(Motor_ID motorname);

void  ENCODER_RD_ISR1(void);
void  ENCODER_LU_ISR1(void);
void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2);

void setup() {
  Serial.begin(115200);
  Motor_Init   (  Motor_R_Up    , 24  , 26 , 3);
// Encoder_Init (Motor_R_Down,A4,A5);
// Encoder_Init (Motor_L_Up,A6,A7);

}

void loop() {
  // testing Forward , backward & brake functions 
 Motor_Forward(MEDIUM_SPEED,Motor_R_Up);
 delay(5000);
 Motor_Brake(Motor_R_Up);
 delay(2000);
 Motor_Backward(MEDIUM_SPEED,Motor_R_Up);
 delay(5000);


 /*    
  *     
  *     Serial.print(" Motor_R_Down = ");
       //Encoder_Angle_Update(Motor_L_Up);
    Serial.print(pulse_counter[Motor_R_Down]);
    Serial.print("\t Motor_L_Up = ");
   Serial.print(pulse_counter[Motor_L_Up]);
    Serial.println("");
    */ 

 

}



void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
{
  Motor_Pins[motorname][IN1]=IN1_Pinnumber;
  Motor_Pins[motorname][IN2]=IN2_Pinnumber;
  Motor_Pins[motorname][ENA]=ENA_Pinnumber;
  pinMode(Motor_Pins[motorname][IN1],OUTPUT); // define IN1 pin as output
  pinMode(Motor_Pins[motorname][IN2],OUTPUT); // define IN2 pin as output
  pinMode(Motor_Pins[motorname][ENA],OUTPUT); // define ENA pin as output

  //ledcSetup(0, freq, resolution);
  // attach the channel to the GPIO to be controlled
  //ledcAttachPin(ENA_Pinnumber, motorname);
 }



                                                              // movements function table
                                                                 
                                                              /*
                                                                
                                                              IN1     IN2     ENA       function 
                                                              0        0       x        Brake 
                                                              1        0       1        Forward ( 100% )
                                                              1        0      PWM       Forward ( PWM  )
                                                              0        1       1        Reverse ( 100% )
                                                              0        1      PWM       Reverse ( PWM  ) 
                                                              
                                                               */
                                                              


                                                            // movements functions 
void Motor_Forward(MOTOR_SPEED Speed ,Motor_ID motorname)
{
     digitalWrite(Motor_Pins[motorname][IN1],HIGH);
     digitalWrite(Motor_Pins[motorname][IN2],LOW);
     analogWrite(Motor_Pins[motorname][ENA],Speed);
     //ledcWrite(motorname, Speed);
}

void Motor_Backward(MOTOR_SPEED Speed ,Motor_ID motorname)
{
     digitalWrite(Motor_Pins[motorname][IN1],LOW);
     digitalWrite(Motor_Pins[motorname][IN2],HIGH);
     analogWrite(Motor_Pins[motorname][ENA],Speed);

     //ledcWrite(motorname, Speed);
}
void Motor_Brake(Motor_ID motorname)
{
     digitalWrite(Motor_Pins[motorname][IN1],LOW);
     digitalWrite(Motor_Pins[motorname][IN2],LOW);
}



                              ////////////// motor advance Functions /////////////////////

char motor_Des_Dir[4];
char motor_last_Dir[4];

char move_motor_to_edited( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);


char move_motor_to_edited( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed)
{ 
  if (motor_Des_Dir[motorname] == Forward )
  {
   Motor_Forward(Speed, motorname);
   return 0 ; 
   
    }
   
  else if( motor_Des_Dir[motorname] == backward)
  {
    Motor_Backward(Speed,motorname);
    return 0;
    }
    else  {
     Motor_Brake(motorname);
    return 1;
    }
  
}   

 void Calibiration(){
  while(interrupt_Flags[Motor_R_Down]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }      
  while(interrupt_Flags[Motor_L_Up]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }  
  }


  void move_motor_To_Test(Motor_ID motorname,int desired_angle, MOTOR_SPEED Speed ){
    char a=0 ;
    while(a!=1){
      a= move_motor_to(  motorname ,  desired_angle,  Speed);
      }
    
    }*/


    

              ////////////////// encoder Functions 


void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2) // should be initialized for each encoder , void setup 
{
  Encoder_Pins[encodername][Encoder_CLK]= pinnumber1; // save the pins in the encoder global variable
  Encoder_Pins[encodername][Encoder_DT]= pinnumber2; // save the pins in the encoder global variable
  
  pinMode(Encoder_Pins[encodername][0],INPUT_PULLUP); // assign the first pin
    switch(encodername){
  case Motor_L_Up :attachInterrupt(pinnumber1, ENCODER_LU_ISR1, RISING);
  break;
  case Motor_R_Down : attachInterrupt(pinnumber1, ENCODER_RD_ISR1, RISING);
  break;
    }
  
}

void ENCODER_RD_ISR1(void){

if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
    pulse_counter[Motor_R_Down]++;
  }
   //subtract 1 from count for CCW
  else if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
   pulse_counter[Motor_R_Down]--; 
  } 
   Motor_Angle[Motor_R_Down]=pulse_counter[Motor_R_Down]/10;
  
  }

//void IRAM_ATTR ENCODER_LU_ISR1(void)
void  ENCODER_LU_ISR1(void){

if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
    pulse_counter[Motor_L_Up]++;
  }
  else if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
   pulse_counter[Motor_L_Up]--; 
  } 
   Motor_Angle[Motor_L_Up]=pulse_counter[Motor_L_Up]/10;
  
  }  
