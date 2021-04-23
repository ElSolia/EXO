void Encoder_Init (Motor_ID encodername, char pinnumber1, char pinnumber2) // should be initialized for each encoder , void setup
{
  Encoder_Pins[encodername][Encoder_CLK] = pinnumber1; // save the pins in the encoder global variable
  Encoder_Pins[encodername][Encoder_DT] = pinnumber2; // save the pins in the encoder global variable

  pinMode(Encoder_Pins[encodername][0], INPUT_PULLUP); // assign the first pin
  switch (encodername) {
    case Motor_L_Up : attachInterrupt(pinnumber1, ENCODER_LU_ISR1, RISING);
      break;
    case Motor_R_Down : attachInterrupt(pinnumber1, ENCODER_RD_ISR1, RISING);
      break;
  }

}

void ENCODER_RD_ISR1(void) {

  if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
    pulse_counter[Motor_R_Down]++;
  }
  //subtract 1 from count for CCW
  else if (digitalRead(Encoder_Pins[Motor_R_Down][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_R_Down][Encoder_DT])) {
    pulse_counter[Motor_R_Down]--;
  }
  Motor_Angle[Motor_R_Down] = pulse_counter[Motor_R_Down] / 10;

}

//void IRAM_ATTR ENCODER_LU_ISR1(void)
void  ENCODER_LU_ISR1(void) {

  if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && !digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
    pulse_counter[Motor_L_Up]++;
  }
  else if (digitalRead(Encoder_Pins[Motor_L_Up][Encoder_CLK]) && digitalRead(Encoder_Pins[Motor_L_Up][Encoder_DT])) {
    pulse_counter[Motor_L_Up]--;
  }
  Motor_Angle[Motor_L_Up] = pulse_counter[Motor_L_Up] / 10;

}
