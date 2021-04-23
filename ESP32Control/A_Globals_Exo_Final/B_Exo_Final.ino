void TC0_Handler()
{
  char dummy = REG_TC0_SR0; // vital - reading this clears some flag
  // otherwise you get infinite interrupts

  if (Serial1.available() > 0) {
    int rec_Byte = Serial1.read(); //can't read the negative number
    //Serial.print("the value recieved = ");
    //Serial.println(rec_Byte);

    switch (rec_Byte) {

      case 2: SPEED_Global = LOW_SPEED; break;  //SPEED=[2,3,4]
      case 3: SPEED_Global = MEDIUM_SPEED; break;
      case 4: SPEED_Global = HIGH_SPEED; break;

      case 5: Stand_Position_Global = false; break; //STAND_P = [5,6]
      case 6: Stand_Position_Global = true; break;


      case 7: Set_Position_Global = false; break; //SET_P = [7,8]
      case 8: Set_Position_Global = true; break;


      case 9: Step_Backward_Global = false; break; //STEP_BACKWORD= [9,10]
      case 10: Step_Backward_Global = true; break;


      case 11: Step_Forward_Global = false; break; //STEP_fORWORD = [11,12]
      case 12: Step_Forward_Global = true; break;


      case 13: Move_Separate_Global = false; break; //MOVE_SEPERATE = [13,14]
      case 14: Move_Separate_Global = true; break;



      // Lower Left
      case 19: case 39: case 59: case 79: case 91:
        Lower_Left_Link_Global =  rec_Byte;
        Lower_Left_Link_Global *= -1;
        break;
      case 199 : Lower_Left_Link_Global = 0; break;

      // Lower Right
      case 18: case 38: case 58: case 78: case 92:
        Lower_Right_Link_Global =  rec_Byte;
        Lower_Right_Link_Global *= -1;
        break;
      case 198: Lower_Right_Link_Global = 0; break;


      // Upper Left
      case 15: case 40: case 65: case 85: //case -35: case -10:
        Upper_Left_Link_Gloabal = rec_Byte; break;
      case 165: case 190:
        Upper_Left_Link_Gloabal = rec_Byte - 200; break;


      // Upper Right
      case 16: case 41: case 66: case 86: //case -34: case -9:
        Upper_Right_Link_Global = rec_Byte; break;
      case 166: case 191:
        Upper_Right_Link_Global = rec_Byte - 200; break;

    }


  }
  //l= !l;
}

void setup() {

  /*************** Timer init ******************/
  Timer_Init();

  /********* Serial Monitor **********/
  Serial1.begin(115200);
  Serial.begin(115200);
  Serial1.setTimeout(10); // set the time that the function called paraseInt will wait to the end of the int




  /*
      void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
      void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2) Pin1->clk , pin2->Dt
      void Limit_Sw_Init ( Motor_ID limitname ,char pinnumber)
  */
    noInterrupts();
  Motor_Init   (  Motor_R_Down  , Motor_R_Down_IN1  , Motor_R_Down_IN2 , Motor_R_Down_ENA);
  Encoder_Init (  Motor_R_Down  , Motor_R_Down_CLK  , Motor_R_Down_DT   );
  Limit_Sw_Init(  Motor_R_Down  ,  Motor_R_Down_LIMITSWITCH    );


  Motor_Init   (  Motor_R_Up    , Motor_R_Up_IN1  , Motor_R_Up_IN2 , Motor_R_Up_ENA);
  Encoder_Init (  Motor_R_Up    , Motor_R_Up_CLK  , Motor_R_Up_DT );
  Limit_Sw_Init(  Motor_R_Up    , Motor_R_Up_LIMITSWITCH );



  Motor_Init   (  Motor_L_Down  , Motor_L_Down_IN1   , Motor_L_Down_IN2  , Motor_L_Down_ENA );
  Encoder_Init (  Motor_L_Down  , Motor_L_Down_CLK   , Motor_L_Down_DT);
  Limit_Sw_Init(  Motor_L_Down  , Motor_L_Down_LIMITSWITCH  );


  Motor_Init   (  Motor_L_Up    , Motor_L_Up_IN1  , Motor_L_Up_IN2 , Motor_L_Up_ENA);
  Encoder_Init (  Motor_L_Up    , Motor_L_Up_CLK  , Motor_L_Up_DT);
  Limit_Sw_Init(  Motor_L_Up    , Motor_L_Up_LIMITSWITCH );





}


char x = 0 ; 
void loop() {
   while (x==0){

    interrupts();
    
    Motor_R_Down_Calibiration();
    delay(1000);
    detachInterrupt(digitalPinToInterrupt(Motor_R_Down_LIMITSWITCH));
    Motor_L_Down_Calibiration();
    delay(1000);
    detachInterrupt(digitalPinToInterrupt(Motor_L_Down_LIMITSWITCH));
    Motor_L_Up_Calibiration();
    delay(1000);
    detachInterrupt(digitalPinToInterrupt(Motor_L_Up_LIMITSWITCH));    
    Motor_R_Up_Calibiration();
    delay(1000);
    detachInterrupt(digitalPinToInterrupt(Motor_R_Up_LIMITSWITCH));    
    Move_Separate_Global = false;
       ++x;
     }


  /* Serial.print("the speed = ");
    Serial.println(SPEED_Global);

    Serial.print("the stand postition = ");
    Serial.println(Stand_Position_Global);

    Serial.print("the set postition = ");
    Serial.println(Set_Position_Global);

    Serial.print("step Forward  = ");
    Serial.println(Step_Forward_Global);

    Serial.print("step Backward  = ");
    Serial.println(Step_Backward_Global);

    Serial.print("move Separate  = ");
    Serial.println(Move_Separate_Global);

    Serial.println("\tLeft\tRight");
    Serial.print("Up\t");
    Serial.print(Upper_Left_Link_Gloabal);
    Serial.print("\t");
    Serial.println(Upper_Right_Link_Global);

    Serial.print("Down\t");
    Serial.print(Lower_Left_Link_Global);
    Serial.print("\t");
    Serial.println(Lower_Right_Link_Global);
    Serial.println("----------------------------------------");

    delay(500);*/

  if (Stand_Position_Global == true) {
    Stand_Position (SPEED_Global);
  }



  else if ((Stand_Position_Global == false) &&
           (Set_Position_Global == true) ) {
    Sit_Position (SPEED_Global);
    //Serial.println(" hello set position is on ");
  }



  else if ((Stand_Position_Global == false) &&
           (Set_Position_Global == false) &&
           (Step_Backward_Global == true)) {
    Step_Backward (SPEED_Global);
    // Serial.println("step Backward from main");
  }


  else if ((Stand_Position_Global == false) &&
           (Set_Position_Global == false) &&
           (Step_Backward_Global == false) &&
           (Step_Forward_Global == true)) {
    Step_Forward (SPEED_Global);
    // Serial.println("step forward from main");
  }




  else if ((Stand_Position_Global == false) &&
           (Set_Position_Global == false) &&
           (Step_Backward_Global == false) &&
           (Step_Forward_Global == false) &&
           (Move_Separate_Global == true)) {

    if (Motor_Angle[Motor_R_Down] != Lower_Right_Link_Global) {
      move_motor_to_Indiv(Motor_R_Down, Lower_Right_Link_Global, SPEED_Global);
    }

    if (Motor_Angle[Motor_R_Up] != Upper_Right_Link_Global) {
      move_motor_to_Indiv(Motor_R_Up, Upper_Right_Link_Global, SPEED_Global);
    }

    if (Motor_Angle[Motor_L_Down] != Lower_Left_Link_Global) {
      move_motor_to_Indiv(Motor_L_Down, Lower_Left_Link_Global, SPEED_Global);
    }

    if (Motor_Angle[Motor_L_Up] != Upper_Left_Link_Gloabal) {
      move_motor_to_Indiv(Motor_L_Up, Upper_Left_Link_Gloabal, SPEED_Global);
    }
  }
  else {}
  /* Serial.print(" the value of Lower_Right_Link_Global =  ");
    Serial.println(Lower_Right_Link_Global);*/
  /*Serial.print("Motor_L_Up angle = ");
    Serial.print(Motor_Angle[Motor_L_Up]);
      Serial.print("\tMotor_R_Up angle = ");
    Serial.println(Motor_Angle[Motor_R_Up]);*/
}
