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
