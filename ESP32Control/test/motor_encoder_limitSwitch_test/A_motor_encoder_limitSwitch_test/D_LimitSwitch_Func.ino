
void Limit_Sw_Init ( Motor_ID limitname , char pinnumber) // void setup
{
  Limit_Sw[limitname] = pinnumber;                  // assign the pinnumber in Limit_Sw array
  pinMode(Limit_Sw[limitname], INPUT_PULLUP);       // the pinnumber specified as input_pullUP

  switch (limitname) {

      // in this switch we check the limit switch Id and then attach a specifc ISR Fn to handle it
      // we did not mention any " case " in this switch as the number of cases alread known in Limit_Sw_ID enum

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

//void IRAM_ATTR LIMIT_RD_ISR()
void  LIMIT_RD_ISR() {

  Motor_Angle[Motor_R_Down] = 0;          // Update the angle with the reference angle of the link
  // we need to call a Fn name " buzzer " here
  pulse_counter[Motor_R_Down] = 0;
  interrupt_Flags[Motor_R_Down] = 1;
  Motor_Brake(Motor_R_Down);
}

//void IRAM_ATTR LIMIT_RU_ISR()
void  LIMIT_RU_ISR() {

  Motor_Angle[Motor_R_Up] = 87;          // Update the angle with the reference angle of the link
  // we need to call a Fn name " buzzer " here
  pulse_counter[Motor_R_Up] = 870;
  interrupt_Flags[Motor_R_Up] = 1;

  Motor_Brake(Motor_R_Up);
}

//void IRAM_ATTR LIMIT_LD_ISR()
void  LIMIT_LD_ISR() {

  Motor_Angle[Motor_L_Down] = 0;          // Update the angle with the reference angle of the link
  // we need to call a Fn name " buzzer " here
  pulse_counter[Motor_L_Down] = 0;
  interrupt_Flags[Motor_L_Down] = 1;

  Motor_Brake(Motor_L_Down);
}

//void IRAM_ATTR LIMIT_LU_ISR()
void  LIMIT_LU_ISR() {

  Motor_Angle[Motor_L_Up] = 87;          // Update the angle with the reference angle of the link
  // we need to call a Fn name " buzzer " here
  pulse_counter[Motor_L_Up] = 870;
  interrupt_Flags[Motor_L_Up] = 1;

  Motor_Brake(Motor_L_Up);
}
