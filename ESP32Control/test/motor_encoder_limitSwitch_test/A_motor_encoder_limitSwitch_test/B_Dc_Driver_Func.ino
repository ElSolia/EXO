void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
{
  Motor_Pins[motorname][IN1] = IN1_Pinnumber;
  Motor_Pins[motorname][IN2] = IN2_Pinnumber;
  Motor_Pins[motorname][ENA] = ENA_Pinnumber;
  pinMode(Motor_Pins[motorname][IN1], OUTPUT); // define IN1 pin as output
  pinMode(Motor_Pins[motorname][IN2], OUTPUT); // define IN2 pin as output
  pinMode(Motor_Pins[motorname][ENA], OUTPUT); // define ENA pin as output

}



// movements functions

void Motor_Forward(MOTOR_SPEED Speed , Motor_ID motorname)
{
  digitalWrite(Motor_Pins[motorname][IN1], HIGH);
  digitalWrite(Motor_Pins[motorname][IN2], LOW);
  analogWrite(Motor_Pins[motorname][ENA], Speed);
}

void Motor_Backward(MOTOR_SPEED Speed , Motor_ID motorname)
{
  digitalWrite(Motor_Pins[motorname][IN1], LOW);
  digitalWrite(Motor_Pins[motorname][IN2], HIGH);
  analogWrite(Motor_Pins[motorname][ENA], Speed);

}
void Motor_Brake(Motor_ID motorname)
{
  digitalWrite(Motor_Pins[motorname][IN1], LOW);
  digitalWrite(Motor_Pins[motorname][IN2], LOW);
}



////////////// motor advance Functions /////////////////////



void move_motor_to_Indiv(Motor_ID motorname, int desired_angle, MOTOR_SPEED Speed );
char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);
void Calibiration();
void Direction_Detect(int desired_angle, Motor_ID motorname );
int Backlash_eliminator(int desired_angle , Motor_ID motorname);
char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     MOTOR_SPEED Speed);
char check_limits(Motor_ID motorname , int desired_angle);



void Direction_Detect(int desired_angle, Motor_ID motorname ) {
  if (desired_angle > Motor_Angle[motorname])
  {
    motor_Des_Dir[motorname] = Forward;
  }
  else if ( desired_angle < Motor_Angle[motorname])
  {
    motor_Des_Dir[motorname] = BackWard;
  }
  else  {
    motor_Des_Dir[motorname] = Same;
  }
}

// for the first time elimination is executed as Desired dirc. = Forward or backward , and the last direction is equal Same
//BackWard direction always to the -ve
// Forward direction always  to the +ve

int Backlash_eliminator(int desired_angle , Motor_ID motorname) {
  if (motor_Des_Dir[motorname] != motor_last_Dir[motorname] && motor_Des_Dir[motorname] != Same ) {
    if (motor_Des_Dir[motorname] == Forward) {
      motor_last_Dir[motorname] = motor_Des_Dir[motorname];       // last directon will be " Forward or Backward " only
      return (desired_angle + Backlash_angle);
    }
    else {
      motor_last_Dir[motorname] = motor_Des_Dir[motorname];             // last directon will be " Forward or Backward " only
      return (desired_angle - Backlash_angle);
    }
  }
  else {
    return (desired_angle);
  }
}



char move_motor_to( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed)
{
  if (desired_angle == (Motor_Angle[motorname])) {
    Motor_Brake(motorname);
    return 1;
  }
  else if  (desired_angle > (Motor_Angle[motorname]  ) )
  {
    Motor_Forward(Speed, motorname);
    return 0 ;

  }
  else //(Motor_Angle[motorname] < desired_angle)
  {
    Motor_Backward(Speed, motorname);
    return 0;
  }
}



void move_motor_to_Indiv(Motor_ID motorname, int desired_angle, MOTOR_SPEED Speed ) {
  Direction_Detect( desired_angle, motorname );
  desired_angle = Backlash_eliminator( desired_angle ,  motorname);
  char a = 0 ;
  while (a != 1) {
    a = move_motor_to(  motorname ,  desired_angle,  Speed);
  }
}




char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     MOTOR_SPEED Speed)
{
  Direction_Detect( desired_angle1, motorname1 );
  Direction_Detect( desired_angle2, motorname2 );



  desired_angle1 = Backlash_eliminator( desired_angle1 ,  motorname1);
  desired_angle2 = Backlash_eliminator( desired_angle2 ,  motorname2);

  char a = 0, b = 0;
  while (!(a && b ))
  {
    a = move_motor_to (motorname1, desired_angle1, Speed) ;
    b = move_motor_to (motorname2, desired_angle2, Speed) ;
  }
}


char check_limits(Motor_ID motorname , int desired_angle) {
  char a;
  switch (motorname) {
    case Motor_L_Down :
    case Motor_R_Down : {
                      if( desired_angle<=0 &&  desired_angle>-100  ) { a=0;  }   // valid angle
                      else{ a=1;  }                                             // out of range angle " NOT VALID "
      }

    case Motor_L_Up   :
    case Motor_R_Up   : {
                      if( desired_angle<80 &&  desired_angle>-50  ) { a=0;  }   // valid angle
                      else{ a=1;  }                                             // out of range angle " NOT VALID "
      }
  }
  return a ;
}




void Calibiration() {
  while (interrupt_Flags[Motor_R_Down] != 1) {
    Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
  }  Motor_Brake(Motor_R_Down);

  while (interrupt_Flags[Motor_L_Up] != 1) {
    Motor_Forward(MEDIUM_SPEED, Motor_L_Up);
  }  Motor_Brake(Motor_L_Up);

}
