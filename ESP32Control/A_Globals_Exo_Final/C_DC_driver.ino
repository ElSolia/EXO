
void Motor_Init (Motor_ID motorname, char IN1_Pinnumber , char IN2_Pinnumber , char ENA_Pinnumber)
{
  Motor_Pins[motorname][IN1] = IN1_Pinnumber;
  Motor_Pins[motorname][IN2] = IN2_Pinnumber;
  Motor_Pins[motorname][ENA] = ENA_Pinnumber;
  pinMode(Motor_Pins[motorname][IN1], OUTPUT); // define IN1 pin as output
  pinMode(Motor_Pins[motorname][IN2], OUTPUT); // define IN2 pin as output
  pinMode(Motor_Pins[motorname][ENA], OUTPUT); // define ENA pin as output

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







/******************************************* Intermidiate Fn's *******************************************/




/******* Detect Direction ********/

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






/************** Backlash Eliminator  ****************/

// for the first time elimination is executed as Desired dirc. = Forward or backward , and the last direction is equal Same
// BackWard direction always to the -ve
// Forward direction always  to the +ve
// Fn Detect direction must be called before calling Backlash eliminator Fn

int Backlash_eliminator(int desired_angle , Motor_ID motorname) {

  if (motor_Des_Dir[motorname] != motor_last_Dir[motorname] && motor_Des_Dir[motorname] != Same ) {
    if (motor_Des_Dir[motorname] == Forward) {
      motor_last_Dir[motorname] = motor_Des_Dir[motorname];             // last directon will be " Forward or Backward " only
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





/*****************  Move motor to    *****************/
// this Fn must be in a loop

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




/*****************  Move motor to idivadule   *****************/

void move_motor_to_Indiv(Motor_ID motorname, int desired_angle, MOTOR_SPEED Speed ) {
  Direction_Detect( desired_angle, motorname );
  int desired_angle1 = Backlash_eliminator( desired_angle ,  motorname); //eliminate backlash
  char a = 0 ;
  while ((a != 1) &&
         (Stand_Position_Global == false) &&
         (Set_Position_Global == false) &&
         (Step_Backward_Global == false) &&
         (Step_Forward_Global == false) &&
         (Move_Separate_Global == true)) {
    a = move_motor_to(  motorname ,  desired_angle1,  Speed);
  }
  if ((Stand_Position_Global == false) &&
      (Set_Position_Global == false) &&
      (Step_Backward_Global == false) &&
      (Step_Forward_Global == false) &&
      (Move_Separate_Global == true))
  { 
      pulse_counter[motorname]  =  desired_angle * 10;
    Motor_Angle[motorname] = desired_angle;   //compensate the error in angle
  }
}




/*****************  Move motors to    *****************/

void move_motors_to_F( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed){
  Direction_Detect( desired_angle1, motorname1 );
  Direction_Detect( desired_angle2, motorname2 );
  Direction_Detect( desired_angle3, motorname3 );
  Direction_Detect( desired_angle4, motorname4 );

// backlash elimination
  int desired_angle11 = Backlash_eliminator( desired_angle1 ,  motorname1);
  int desired_angle22 = Backlash_eliminator( desired_angle2 ,  motorname2);
  int desired_angle33 = Backlash_eliminator( desired_angle3 ,  motorname3);
  int desired_angle44 = Backlash_eliminator( desired_angle4 ,  motorname4);

  char a = 0, b = 0, c = 0 , d = 0 ;
  while ((!(a && b && c && d )) && 
         (Stand_Position_Global==false) &&
         (Set_Position_Global==false)   &&
         (Step_Backward_Global==false)  &&
         (Step_Forward_Global==true))
  {
    a = move_motor_to (motorname1, desired_angle11, Speed) ;
    b = move_motor_to (motorname2, desired_angle22, Speed) ;
    c = move_motor_to (motorname3, desired_angle33, Speed) ;
    d = move_motor_to (motorname4, desired_angle44, Speed) ;
  }

  // backlash compensation 
  if(   (Stand_Position_Global==false) &&
        (Set_Position_Global==false)   &&
        (Step_Backward_Global==false)  &&
        (Step_Forward_Global==true)   ){
  pulse_counter[motorname1]  =  desired_angle1 * 10;
  pulse_counter[motorname2]  =  desired_angle2 * 10;
  pulse_counter[motorname3]  =  desired_angle3 * 10;
  pulse_counter[motorname4]  =  desired_angle4 * 10;  
        
  Motor_Angle[motorname1] = desired_angle1;
  Motor_Angle[motorname2] = desired_angle2;
  Motor_Angle[motorname3] = desired_angle3;
  Motor_Angle[motorname4] = desired_angle4;}
}



void move_motors_to_B( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed)
{
  Direction_Detect( desired_angle1, motorname1 );
  Direction_Detect( desired_angle2, motorname2 );
  Direction_Detect( desired_angle3, motorname3 );
  Direction_Detect( desired_angle4, motorname4 );


  int desired_angle11 = Backlash_eliminator( desired_angle1 ,  motorname1);
  int desired_angle22 = Backlash_eliminator( desired_angle2 ,  motorname2);
  int desired_angle33 = Backlash_eliminator( desired_angle3 ,  motorname3);
  int desired_angle44 = Backlash_eliminator( desired_angle4 ,  motorname4);

  char a = 0, b = 0, c = 0 , d = 0 ;
  while ((!(a && b && c && d ))        &&
        (Stand_Position_Global==false) &&
        (Set_Position_Global==false)   &&
        (Step_Backward_Global==true))
  {
    a = move_motor_to (motorname1, desired_angle11, Speed) ;
    b = move_motor_to (motorname2, desired_angle22, Speed) ;
    c = move_motor_to (motorname3, desired_angle33, Speed) ;
    d = move_motor_to (motorname4, desired_angle44, Speed) ;
  }


  if(   (Stand_Position_Global==false) &&
        (Set_Position_Global==false)   &&
        (Step_Backward_Global==true)    ){
  pulse_counter[motorname1]  =  desired_angle1 * 10;
  pulse_counter[motorname2]  =  desired_angle2 * 10;
  pulse_counter[motorname3]  =  desired_angle3 * 10;
  pulse_counter[motorname4]  =  desired_angle4 * 10;
    
  Motor_Angle[motorname1] = desired_angle1;
  Motor_Angle[motorname2] = desired_angle2;
  Motor_Angle[motorname3] = desired_angle3;
  Motor_Angle[motorname4] = desired_angle4;}
}




/*****************  Check the Motor Angle Limits    *****************/

char check_limits(Motor_ID motorname , int desired_angle) {
  char a;
  switch (motorname) {
    case Motor_L_Down :
    case Motor_R_Down :
      if ( desired_angle <= 0 &&  desired_angle > -100  ) {
        a = 0;   // valid angle
      }
      else {
        a = 1;   // out of range angle " NOT VALID "
      }

      break;

    case Motor_L_Up   :
    case Motor_R_Up   :
      if ( desired_angle < 85 &&  desired_angle > -50  ) {
        a = 0;   // valid angle
      }
      else {
        a = 1;   // out of range angle " NOT VALID "
      }

      break;
  }
  return a ;
}





/*****************  Calibiration Fn   *****************/
//called one time at wake up only

void Motor_R_Down_Calibiration() {
  interrupt_Flags[Motor_R_Down]=0;
  
  while (interrupt_Flags[Motor_R_Down] != 1) { //Motor_R_Down
    Motor_Backward(MEDIUM_SPEED, Motor_R_Down);
    Serial.print("Motor_R_Down angle = ");
    Serial.println(Motor_Angle[Motor_R_Down]);
  }
  //Motor_Backward(LOW_SPEED, Motor_R_Down);  
          Move_Separate_Global = true;
  move_motor_to_Indiv(Motor_R_Down, -5 , MEDIUM_SPEED);
  Motor_Brake(Motor_R_Down);
} 


void Motor_L_Down_Calibiration(){
     interrupt_Flags[Motor_L_Down]=0;
    while (interrupt_Flags[Motor_L_Down] != 1) { // Motor_L_Down
    //interrupt_Flags[Motor_L_Down]=0;  
    Motor_Forward(MEDIUM_SPEED, Motor_L_Down);
    Serial.print("Motor_L_Down angle = ");
    Serial.println(Motor_Angle[Motor_L_Down]);
  }
    //Motor_Backward(HIGH_SPEED, Motor_L_Down);
        Move_Separate_Global = true;
  move_motor_to_Indiv(Motor_L_Down, -5 , MEDIUM_SPEED);
  Motor_Brake(Motor_L_Down);
  }

  
void Motor_L_Up_Calibiration(){
      interrupt_Flags[Motor_L_Up]=0;
  while (interrupt_Flags[Motor_L_Up] != 1) {  //Motor_L_Up
        //interrupt_Flags[Motor_L_Up]=0;
    Motor_Forward(MEDIUM_SPEED, Motor_L_Up);
    Serial.print("Motor_L_Up angle = ");
    Serial.println(Motor_Angle[Motor_L_Up]);
  }
      //Motor_Backward(HIGH_SPEED, Motor_L_Up);
              Move_Separate_Global = true;
  move_motor_to_Indiv(Motor_L_Up, 0 , MEDIUM_SPEED);
  Motor_Brake(Motor_L_Up);
  //delay(5000); 
  }


void Motor_R_Up_Calibiration(){
    interrupt_Flags[Motor_R_Up]=0;
 while (interrupt_Flags[Motor_R_Up] != 1) { //Motor_R_Up
    //interrupt_Flags[Motor_R_Up]=0;
    Motor_Backward(MEDIUM_SPEED, Motor_R_Up);
    Serial.print("Motor_R_Up angle = ");
    Serial.println(Motor_Angle[Motor_R_Up]);
  }
          //Motor_Backward(HIGH_SPEED, Motor_R_Up);
                  Move_Separate_Global = true;
  move_motor_to_Indiv(Motor_R_Up, 0 , MEDIUM_SPEED);
  Motor_Brake(Motor_R_Up);  
  }
  
