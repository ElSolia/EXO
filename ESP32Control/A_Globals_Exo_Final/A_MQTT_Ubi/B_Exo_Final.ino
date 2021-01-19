
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
