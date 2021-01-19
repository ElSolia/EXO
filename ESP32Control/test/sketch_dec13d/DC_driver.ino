
void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
{
  Motor_Pins[motorname][IN1]=IN1_Pinnumber;
  Motor_Pins[motorname][IN2]=IN2_Pinnumber;
  Motor_Pins[motorname][ENA]=ENA_Pinnumber;
  pinMode(Motor_Pins[motorname][IN1],OUTPUT); // define IN1 pin as output
  pinMode(Motor_Pins[motorname][IN2],OUTPUT); // define IN2 pin as output
  ledcSetup(motorname, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA_Pinnumber, motorname);
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
     ledcWrite(motorname, Speed);
}

void Motor_Backward(MOTOR_SPEED Speed ,Motor_ID motorname)
{
     digitalWrite(Motor_Pins[motorname][IN1],LOW);
     digitalWrite(Motor_Pins[motorname][IN2],HIGH);
     ledcWrite(motorname, Speed);
}
void Motor_Brake(Motor_ID motorname)
{
     digitalWrite(Motor_Pins[motorname][IN1],LOW);
     digitalWrite(Motor_Pins[motorname][IN2],LOW);
}



char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed)
{ 
  if(desired_angle==(Motor_Angle[motorname])) {
     Motor_Brake(motorname);
    return 1;
    }
  else if  (desired_angle > (Motor_Angle[motorname]  ) )
  {
   Motor_Forward(Speed, motorname);
   Encoder_Angle_Update (motorname); // encoder name = motor name
   delay(9000);
   Motor_Brake(motorname);
   delay(9000);
   
   return 0 ; 
   
    }
  else //(Motor_Angle[motorname] < desired_angle)
  {
    Motor_Backward(Speed,motorname);
    Encoder_Angle_Update (motorname);
    return 0;
    }
  
}

  
