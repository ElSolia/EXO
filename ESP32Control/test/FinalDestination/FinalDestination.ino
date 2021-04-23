#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder

int Motor_Angle[4]={0,0,0,0}; // TO hold the Current angle of the motor 
unsigned char Encoder_Pins[4][2]; // Pins which each encoder use 
int pulse_counter[4]={0,0,0,0}; // counter pulses
 
//char lastStateCLK[4];  // variable to store the last state of the pin CLK to 
//char currentStateCLK[4]={0,0,0,0};


typedef enum            // enum to give every motor an ID
{
  Motor_R_Down=0,       // Right Down motor ID = 0 
  Motor_R_Up=1,         // Right UP motor ID = 1 
  Motor_L_Down=2,       // Left Down motor ID = 2
  Motor_L_Up=3          // Left UP motor ID = 3
}Motor_ID;


void  ENCODER_RD_ISR1(void);
//void  ENCODER_RD_ISR2(void);
void  ENCODER_LU_ISR1(void);

//void IRAM_ATTR ENCODER_RD_ISR1(void);
//void IRAM_ATTR ENCODER_RD_ISR2(void);
//void IRAM_ATTR ENCODER_LU_ISR1(void);


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




  /*void IRAM_ATTR ENCODER_RD_ISR1(void){
   pulse_counter[Motor_L_Up]++;
   
  Motor_Angle[Motor_L_Up]=pulse_counter[Motor_L_Up]/10;
  }*/
 
  /*void IRAM_ATTR ENCODER_RD_ISR2(void){
  pulse_counter[Motor_L_Up]--; 
  Motor_Angle[Motor_L_Up]=pulse_counter[Motor_L_Up]/10;
  }*/
void setup() {
  Serial.begin(115200);
                                  //*******  Encoders initializations   *******//
  //Encoder_Init (Motor_R_Up,32,9); // Motor_R_Down
 Encoder_Init (Motor_R_Down,A4,A5);
  //digitalWrite(9,LOW);
  
 Encoder_Init (Motor_L_Up,A6,A7);
  //Encoder_Init (Motor_L_Up,22,23);

                                //*******  Motors initializations   *******//
  // Motor_Init (Motor_R_Up, 18 , 19, 4); // 18 is IN1 ,, 19 is IN2  Motor_R_Up
  // Motor_Init (Motor_R_Down, 32 , 33, 25); // 32 is is IN1 , 33 is IN2 Motor_R_Down
  //Motor_Init (Motor_L_Down, 18 , 19, 4);
  //Motor_Init (Motor_L_Up, 18 , 19, 4);
  //Step_Test(HIGH_SPEED); 
  
}
void loop() {

  //move_motor_to(Motor_R_Up,40,HIGH_SPEED);
 //move_motor_to(Motor_R_Down,0,HIGH_SPEED);


    

    Serial.print(" Motor_R_Down = ");
       //Encoder_Angle_Update(Motor_L_Up);
    Serial.print(pulse_counter[Motor_R_Down]);
    Serial.print("\t Motor_L_Up = ");
   Serial.print(pulse_counter[Motor_L_Up]);
    Serial.println("");


}


//void IRAM_ATTR ENCODER_RD_ISR1(void)
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
