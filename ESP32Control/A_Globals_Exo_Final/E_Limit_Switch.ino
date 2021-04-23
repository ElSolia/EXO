
void Limit_Sw_Init ( Motor_ID limitname ,char pinnumber){  
  Limit_Sw[limitname]= pinnumber;                   // assign the pinnumber in Limit_Sw array
  pinMode(Limit_Sw[limitname],INPUT_PULLUP);        // the pinnumber specified as input_pullUP 

        switch (limitname){ 
                              
                            // in this switch we check the limit switch Id and then attach a specifc ISR Fn to handle it 
      
                       // attach interrupt to the limit switch R_Down and attach LIMIT_RD_ISR Fn to handle it
          case Motor_R_Down : attachInterrupt(pinnumber, LIMIT_RD_ISR, FALLING);
            break;
      
                       // attach interrupt to the limit switch R_Up and attach LIMIT_RU_ISR Fn to handle it
          case Motor_R_Up   : attachInterrupt(pinnumber, LIMIT_RU_ISR, FALLING);  
            break;
      
                       // attach interrupt to the limit switch L_Down and attach LIMIT_LD_ISR Fn to handle it  
          case Motor_L_Down : attachInterrupt(pinnumber, LIMIT_LD_ISR, FALLING); 
            break;
      
                       // attach interrupt to the limit switch L_Up and attach LIMIT_LU_ISR Fn to handle it
          case Motor_L_Up   : attachInterrupt(pinnumber, LIMIT_LU_ISR, FALLING);   
            break;  
              }
      
  }


  
// ISR Functions


void  LIMIT_RD_ISR() {

  Motor_Angle[Motor_R_Down] = 0;          // Update the angle with the reference angle of the link
  
  // we need to call a Fn name " buzzer " here
  pulse_counter[Motor_R_Down] = 0;
  interrupt_Flags[Motor_R_Down] = 1;
  //move_motor_to_Indiv(Motor_R_Down, -5 , HIGH_SPEED);
  //an instruction must be added move the link away from the limit switch 
  Motor_Brake(Motor_R_Down);
  Motor_Brake(Motor_L_Down);
  Motor_Brake(Motor_L_Up);
  Motor_Brake(Motor_R_Up);

}



void  LIMIT_RU_ISR() {

  Motor_Angle[Motor_R_Up] = 75;          // Update the angle with the reference angle of the link
  
  // we need to call a Fn name " buzzer " here
  
  pulse_counter[Motor_R_Up] = 750;
  interrupt_Flags[Motor_R_Up] = 1;
 // move_motor_to_Indiv(Motor_R_Up, 75 , HIGH_SPEED);

  //an instruction must be added move the link away from the limit switch 

  Motor_Brake(Motor_R_Down);
  Motor_Brake(Motor_L_Down);
  Motor_Brake(Motor_L_Up);
  Motor_Brake(Motor_R_Up);
  }



void  LIMIT_LD_ISR() {

  Motor_Angle[Motor_L_Down] = 0;          // Update the angle with the reference angle of the link
  
  // we need to call a Fn name " buzzer " here
  
  pulse_counter[Motor_L_Down] = 0;
  interrupt_Flags[Motor_L_Down] = 1;
  //move_motor_to_Indiv(Motor_L_Down, -5 , HIGH_SPEED);

  //an instruction must be added move the link away from the limit switch 

  Motor_Brake(Motor_R_Down);
  Motor_Brake(Motor_L_Down);
  Motor_Brake(Motor_L_Up);
  Motor_Brake(Motor_R_Up);
  }




void  LIMIT_LU_ISR() {

  Motor_Angle[Motor_L_Up] =75 ;          // Update the angle with the reference angle of the link
  
  // we need to call a Fn name " buzzer " here
  
  pulse_counter[Motor_L_Up] = 750;
  interrupt_Flags[Motor_L_Up] = 1;
    //move_motor_to_Indiv(Motor_L_Up, 75 , HIGH_SPEED);

  //an instruction must be added move the link away from the limit switch 

  Motor_Brake(Motor_R_Down);
  Motor_Brake(Motor_L_Down);
  Motor_Brake(Motor_L_Up);
  Motor_Brake(Motor_R_Up);
  }
