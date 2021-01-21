#define Encoder_CLK 0 // the first pin of the encoder  
#define Encoder_DT  1 // second pin of the encoder

int Motor_Angle[4]={0,0,0,0}; // TO hold the Current angle of the motor 
unsigned char Encoder_Pins[4][2]; // Pins which each encoder use 
float pulse_counter[4]={0,0,0,0}; // counter pulses 
char lastStateCLK[4];  // variable to store the last state of the pin CLK to 
char currentStateCLK[4]={0,0,0,0};
typedef enum            // enum to give every motor an ID
{
  Motor_R_Down=0,       // Right Down motor ID = 0 
  Motor_R_Up=1,         // Right UP motor ID = 1 
  Motor_L_Down=2,       // Left Down motor ID = 2
  Motor_L_Up=3          // Left UP motor ID = 3
}Motor_ID;

  //void ENCODER_RD_ISR2();
void IRAM_ATTR ENCODER_RD_ISR1(void){
  pulse_counter[Motor_L_Up]++;
  
  }
void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2) // should be initialized for each encoder , void setup 
{
  Encoder_Pins[encodername][Encoder_CLK]= pinnumber1; // save the pins in the encoder global variable
  Encoder_Pins[encodername][Encoder_DT]= pinnumber2; // save the pins in the encoder global variable
  
  pinMode(Encoder_Pins[encodername][0],INPUT_PULLUP); // assign the first pin
  pinMode(Encoder_Pins[encodername][1],INPUT_PULLUP);

  attachInterrupt(pinnumber1, ENCODER_RD_ISR1, FALLING);
   // attachInterrupt(digitalPinToInterrupt(pinnumber2), ENCODER_RD_ISR2, FALLING);

  
}


void Encoder_Angle_Update (Motor_ID encodername) // void loop
{ 
  // Read the current state of CLK
  
  currentStateCLK[encodername] = digitalRead(Encoder_Pins[encodername][Encoder_CLK]);

            // If last and current state of CLK are different, then pulse occurred
            // React to only 1 state change to avoid double count
  
          if (currentStateCLK[encodername] != lastStateCLK[encodername]){
        
                          // If the DT state is different than the CLK state then
                          // the encoder is rotating CCW so decrement
                          // Direction detection
                    if (digitalRead(Encoder_Pins[encodername][Encoder_DT]) != currentStateCLK[encodername]) {
                      pulse_counter[encodername] ++;       // counterclockwise
                    } 
                    
                    else {
                      pulse_counter[encodername] --;      // Encoder is rotating CW so increment
                    }
           Motor_Angle[encodername] = ((int)(pulse_counter[encodername] / ((float)1.5*(float)469/(float)36)));
         // Motor_Angle[encodername] = ((int)(pulse_counter[encodername] / ((float)(1.3))));

          }
          
   // Remember last CLK state
    lastStateCLK[encodername]=currentStateCLK[encodername];
    
    
  }

 
  /*void ENCODER_RD_ISR2(){
  pulse_counter[Motor_L_Up]--;
  
  }*/
void setup() {
  Serial.begin(115200);
  //  Encoders initializations
  //Encoder_Init (Motor_R_Up,22,23); // Motor_R_Down
  Encoder_Init (Motor_L_Up,22,23);
  //digitalWrite(9,LOW);
  
  //Encoder_Init (Motor_L_Down,22,23);
  //Encoder_Init (Motor_L_Up,22,23);
  //  Motor initializations
 // Motor_Init (Motor_R_Up, 18 , 19, 4); // 18 is IN1 ,, 19 is IN2  Motor_R_Up
  // Motor_Init (Motor_R_Down, 32 , 33, 25); // 32 is is IN1 , 33 is IN2 Motor_R_Down
  //Motor_Init (Motor_L_Down, 18 , 19, 4);
  //Motor_Init (Motor_L_Up, 18 , 19, 4);
  //Step_Test(HIGH_SPEED); 
  
}
void loop() {

  //move_motor_to(Motor_R_Up,40,HIGH_SPEED);
 //move_motor_to(Motor_R_Down,0,HIGH_SPEED);

  //Encoder_Angle_Update(Motor_L_Up);

  // Serial.print(" Motor_Angle = ");
     //Encoder_Angle_Update(Motor_L_Up);

   //Serial.println(Motor_Angle[Motor_L_Up]);
     //Encoder_Angle_Update(Motor_L_Up);

    Serial.print(" pulse counter = ");
       //Encoder_Angle_Update(Motor_L_Up);

  Serial.println(pulse_counter[Motor_L_Up]);

}
