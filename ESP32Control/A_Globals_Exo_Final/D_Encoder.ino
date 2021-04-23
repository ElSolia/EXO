
void Encoder_Init ( Motor_ID  encodername , char pinnumber1 , char pinnumber2 ){
  Encoder_Pins[encodername][Encoder_CLK] = pinnumber1;      // save the pins in the encoder global variable
  Encoder_Pins[encodername][Encoder_DT] = pinnumber2;       // save the pins in the encoder global variable

  pinMode(Encoder_Pins[encodername][Encoder_CLK],INPUT_PULLUP);       // assign the first pin
  pinMode(Encoder_Pins[encodername][Encoder_DT], INPUT);
  switch (encodername) {

    // in this switch we check the limit switch Id and then attach a specifc ISR Fn to handle it

    // attach interrupt to the limit switch R_Down and attach LIMIT_RD_ISR Fn to handle it
    case Motor_R_Down : attachInterrupt(pinnumber1, ENCODER_RD_ISR, RISING);
      break;

    // attach interrupt to the limit switch R_Up and attach LIMIT_RU_ISR Fn to handle it
    case Motor_R_Up   : attachInterrupt(pinnumber1, ENCODER_RU_ISR, RISING);
      break;

    // attach interrupt to the limit switch L_Down and attach LIMIT_LD_ISR Fn to handle it
    case Motor_L_Down : attachInterrupt(pinnumber1, ENCODER_LD_ISR, RISING);
      break;

    // attach interrupt to the limit switch L_Up and attach LIMIT_LU_ISR Fn to handle it
    case Motor_L_Up   : attachInterrupt(pinnumber1, ENCODER_LU_ISR, RISING);
      break;
  }

}



//1 Motor_L_Up
void  ENCODER_LU_ISR(void) {

  if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
    pulse_counter[Motor_L_Up]--;
  }
  else if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
    pulse_counter[Motor_L_Up]++;
  }
  Motor_Angle[Motor_L_Up] = pulse_counter[Motor_L_Up] / 10;
}


//2 Motor_L_Down
void  ENCODER_LD_ISR(void) {
  if (digitalRead(Encoder_Pins[Motor_L_Down][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_L_Down][Encoder_DT])) {
    pulse_counter[Motor_L_Down]--;

  }
  else if (digitalRead(Encoder_Pins[Motor_L_Down][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_L_Down][Encoder_DT])) {
    pulse_counter[Motor_L_Down]++;

  }
  Motor_Angle[Motor_L_Down] = pulse_counter[Motor_L_Down] / 10;

}



//3  Motor_R_Up
void  ENCODER_RU_ISR(void) {
  if (digitalRead(Encoder_Pins[Motor_R_Up][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_R_Up][Encoder_DT])) {
    pulse_counter[Motor_R_Up]++;

  }
  else if (digitalRead(Encoder_Pins[Motor_R_Up][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_R_Up][Encoder_DT])) {
    pulse_counter[Motor_R_Up]--;

  }     Motor_Angle[Motor_R_Up] = pulse_counter[Motor_R_Up] / 10;

}

//4
void  ENCODER_RD_ISR(void) {
  if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
    pulse_counter[Motor_R_Down]++;

  }
  else if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
    pulse_counter[Motor_R_Down]--;

  }

  Motor_Angle[Motor_R_Down] = pulse_counter[Motor_R_Down] / 10;

}





/*
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
           Motor_Angle[encodername] = (int)(pulse_counter[encodername] / ((float)1.5*(float)469/(float)36));
          }

   // Remember last CLK state
    lastStateCLK[encodername]=currentStateCLK[encodername];


  }*/
