#define Forward 1 
#define backword 0
#define Same 11
#define backlash_angle 5

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
  if (desired_angle >Motor_Angle[motorname])
  {
   Motor_Forward(Speed, motorname);
   Encoder_Angle_Update (motorname); // encoder name = motor name
   return 0 ; 
   
    }
   
  else if( desired_angle<Motor_Angle[motorname])
  {
    Motor_Backward(Speed,motorname);
    Encoder_Angle_Update (motorname);
    return 0;
    }
    else  {
     Motor_Brake(motorname);
    return 1;
    }
  
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*char motor_Des_Dir[4];
char motor_last_Dir[4];
char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed);

void Direction_Detect(int desired_angle,Motor_ID motorname );                     
int Backlash_eliminator(int desired_angle , Motor_ID motorname);
char move_motor_to_edited( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed);*/



char move_motors_to( Motor_ID motorname1 , int desired_angle1,
                     Motor_ID motorname2 , int desired_angle2,
                     Motor_ID motorname3 , int desired_angle3,
                     Motor_ID motorname4 , int desired_angle4,
                     MOTOR_SPEED Speed)
                                          { 
                                          Direction_Detect( desired_angle1, motorname1 );
                                          Direction_Detect( desired_angle2, motorname2 );
                                          Direction_Detect( desired_angle3, motorname3 );
                                          Direction_Detect( desired_angle4, motorname4 );
                                          
                                          
                                          desired_angle1 = Backlash_eliminator( desired_angle1 ,  motorname1);
                                          desired_angle2 = Backlash_eliminator( desired_angle2 ,  motorname2);
                                          desired_angle3 = Backlash_eliminator( desired_angle3 ,  motorname3);
                                          desired_angle4 = Backlash_eliminator( desired_angle4 ,  motorname4);
                                          
                                          
                                            char a=0,b=0,c=0,d=0;
                                            while(!(a && b && c && d)) 
                                            { 
                                              a=move_motor_to (motorname1,desired_angle1,Speed) ;
                                              b=move_motor_to (motorname2,desired_angle2,Speed) ;
                                              c=move_motor_to (motorname3,desired_angle3,Speed);
                                              d=move_motor_to (motorname4,desired_angle4,Speed);
                                            }
                                            
                                          }

void Direction_Detect(int desired_angle,Motor_ID motorname ){
                                                  if (desired_angle >Motor_Angle[motorname])
                                                {
                                                 motor_Des_Dir[motorname] = Forward;
                                                 
                                                  }
                                                 
                                                else if( desired_angle<Motor_Angle[motorname])
                                                {
                                                 motor_Des_Dir[motorname] = backword;
                                              
                                                  }
                                                  else  {
                                                motor_Des_Dir[motorname] = Same;    }
                                                }


  
int Backlash_eliminator(int desired_angle , Motor_ID motorname){
                                                if(motor_Des_Dir[motorname]!= motor_last_Dir[motorname] && motor_Des_Dir[motorname]!= Same ){
                                                  motor_last_Dir[motorname]=motor_Des_Dir[motorname];
                                                  return (desired_angle+Backlash_angle);
                                                  }
                                                 else {
                                                      return (desired_angle);
                                                  } 
                                                }

/*
char move_motor_to_edited( Motor_ID motorname , int desired_angle, MOTOR_SPEED Speed)
{ 
  if (motor_Des_Dir[motorname] == Forward )
  {
   Motor_Forward(Speed, motorname);
   Encoder_Angle_Update (motorname); // encoder name = motor name
   return 0 ; 
   
    }
   
  else if( motor_Des_Dir[motorname] == backward)
  {
    Motor_Backward(Speed,motorname);
    Encoder_Angle_Update (motorname);
    return 0;
    }
    else  {
     Motor_Brake(motorname);
    return 1;
    }
  
}   */

 void Calibiration(){
  while(interrupt_Flags[Motor_R_Down]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }
  while(interrupt_Flags[Motor_R_Up]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }
  while(interrupt_Flags[Motor_L_Down]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }      
  while(interrupt_Flags[Motor_L_Up]!=1){
       Motor_Forward(MEDIUM_SPEED, Motor_R_Down);
    }  
  }


  void move_motor_To_Test(Motor_ID motorname,int desired_angle, MOTOR_SPEED Speed ){
    char a=0 ;
    while(a!=1){
      a= move_motor_to(  motorname ,  desired_angle,  Speed);
      }
    
    }
