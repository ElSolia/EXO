void Stand_Position (MOTOR_SPEED Speed)
{
  
  Direction_Detect( 0, Motor_R_Down );
  Direction_Detect( 0, Motor_R_Up );
  Direction_Detect( 0, Motor_L_Down );
  Direction_Detect( 0, Motor_L_Up );


  int desired_angle1 = Backlash_eliminator( 0 ,  Motor_R_Down);
  int desired_angle2 = Backlash_eliminator( 0 ,  Motor_R_Up);
  int desired_angle3 = Backlash_eliminator( 0 ,  Motor_L_Down);
  int desired_angle4 = Backlash_eliminator( 0 ,  Motor_L_Up);
  
  
  char a=0,b=0,c=0,d=0;
  while((!(a && b && c && d))&& Stand_Position_Global==true) // Stand
  /*//while(!(a)&& Stand_Position_Global==true)*/
  { 
    a=move_motor_to (Motor_L_Up,desired_angle4,Speed) ;
    b=move_motor_to (Motor_L_Down,desired_angle3,Speed) ;
    c=move_motor_to (Motor_R_Up,desired_angle2,Speed);
    d=move_motor_to (Motor_R_Down,desired_angle1,Speed);
  }
if (Stand_Position_Global==true){
Motor_Angle[Motor_L_Up]=0;
Motor_Angle[Motor_L_Down]=0;
Motor_Angle[Motor_R_Up]=0;
Motor_Angle[Motor_R_Down]=0;}
   
         
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Sit_Position (MOTOR_SPEED Speed)
{
 
  Direction_Detect( -90, Motor_R_Down );
  Direction_Detect( 85, Motor_R_Up );
  Direction_Detect( -90, Motor_L_Down );
  Direction_Detect( 85, Motor_L_Up );


  int desired_angle1 = Backlash_eliminator( -90 ,  Motor_R_Down);
  int desired_angle2 = Backlash_eliminator( 85 ,  Motor_R_Up);
  int desired_angle3 = Backlash_eliminator( -90 ,  Motor_L_Down);
  int desired_angle4 = Backlash_eliminator( 85 ,  Motor_L_Up);
  
  
  char a=0,b=0,c=0,d=0;
  while((!(a && b && c && d)) && Stand_Position_Global == false && Set_Position_Global == true) // Stand
  /*while((!(a)) && Stand_Position_Global == false && Set_Position_Global == true)*/
  { 
    a=move_motor_to (Motor_L_Up,desired_angle4,Speed) ;
    b=move_motor_to (Motor_L_Down,desired_angle3,Speed) ;
    c=move_motor_to (Motor_R_Up,desired_angle2,Speed);
    d=move_motor_to (Motor_R_Down,desired_angle1,Speed);
  }
if(Stand_Position_Global == false && Set_Position_Global == true){
Motor_Angle[Motor_L_Up]=85;
Motor_Angle[Motor_L_Down]=-90;
Motor_Angle[Motor_R_Up]=85;
Motor_Angle[Motor_R_Down]=-90;}
  
 }


/////////////////////////////////////////////////////////////////////////////////////////////////////////


void Step_Forward (MOTOR_SPEED Speed)
{  

       move_motors_to_F( Motor_L_Up      , 20,
                       Motor_L_Down    , 0 ,
                       Motor_R_Up      ,-25,
                       Motor_R_Down    ,-10,
                       Speed);


  
  /*char a=0,b=0,c=0,d=0;
  while(!(a && b && c && d)) // 1- + 20 degree 0 degree - 25 degree - 10 degree
  { 
    a=move_motor_to (Motor_L_Up,20,Speed) ;
    b=move_motor_to (Motor_L_Down,0,Speed) ;
    c=move_motor_to (Motor_R_Up,-25,Speed);
    d=move_motor_to (Motor_R_Down,-10,Speed);
  }*/

       move_motors_to_F( Motor_L_Up      , 20,
                       Motor_L_Down    ,-20,
                       Motor_R_Up      ,-15,
                       Motor_R_Down    ,-40,
                       Speed);


  
  /* a=b=c=d=0;
  while(!(a && b && c && d))//2- + 20 degree - 20 degree - 15 degree - 40 degree
  { 
    a=move_motor_to (Motor_L_Up,20,Speed) ;
    b=move_motor_to (Motor_L_Down,-20,Speed) ;
    c=move_motor_to (Motor_R_Up,-15,Speed);
    d=move_motor_to (Motor_R_Down,-40,Speed);
  }*/

       move_motors_to_F( Motor_L_Up      , 0 ,
                       Motor_L_Down    ,-5 ,
                       Motor_R_Up      , 15,
                       Motor_R_Down    ,-60,
                       Speed);

  
  /* a=b=c=d=0;
  while(!(a && b && c && d)) // 3- 0 degree - 5 degree + 15 degree - 60 degree
  { 
    a=move_motor_to (Motor_L_Up,0,Speed) ;
    b=move_motor_to (Motor_L_Down,-5,Speed) ;
    c=move_motor_to (Motor_R_Up,15,Speed);
    d=move_motor_to (Motor_R_Down,-60,Speed);
  }*/

       move_motors_to_F( Motor_L_Up      ,-20,
                       Motor_L_Down    , 0 ,
                       Motor_R_Up      , 25,
                       Motor_R_Down    ,-25,
                       Speed);


  /* a=b=c=d=0;
  while(!(a && b && c && d)) // 4- - 20 degree 0 degree + 25 degree - 25 degree
  { 
    a=move_motor_to (Motor_L_Up,-20,Speed) ;
    b=move_motor_to (Motor_L_Down,0,Speed) ;
    c=move_motor_to (Motor_R_Up,25,Speed);
    d=move_motor_to (Motor_R_Down,-25,Speed);
  }*/


       move_motors_to_F( Motor_L_Up      ,-25,
                       Motor_L_Down    ,-10,
                       Motor_R_Up      , 20,
                       Motor_R_Down    , 0 ,
                       Speed);
  
  /* a=b=c=d=0;
  while(!(a && b && c && d))//5- - 25 degree - 10 degree + 20 degree 0 degree
  { 
    a=move_motor_to (Motor_L_Up,-25,Speed) ;
    b=move_motor_to (Motor_L_Down,-10,Speed) ;
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }*/


       move_motors_to_F( Motor_L_Up      ,-15,
                       Motor_L_Down    ,-40,
                       Motor_R_Up      , 20,
                       Motor_R_Down    ,-20,
                       Speed);

  
   /*a=b=c=d=0;
  while(!(a && b && c && d))//6- - 15 degree - 40 degree + 20 degree - 20 degree
  { 
    a=move_motor_to (Motor_L_Up,-15,Speed) ;
    b=move_motor_to (Motor_L_Down,-40,Speed) ;
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,-20,Speed);
  }*/



       move_motors_to_F( Motor_L_Up      , 15,
                       Motor_L_Down    ,-60,
                       Motor_R_Up      , 0 ,
                       Motor_R_Down    ,-5 ,
                       Speed);


  
     /*a=b=c=d=0;
   while(!(a && b && c && d))//7- + 15 degree - 60 degree 0 degree - 5 degree
  { 
    a=move_motor_to (Motor_L_Up,15,Speed) ;
    b=move_motor_to (Motor_L_Down,-60,Speed) ;
    c=move_motor_to (Motor_R_Up,0,Speed);
    d=move_motor_to (Motor_R_Down,-5,Speed);
  }*/

       move_motors_to_F( Motor_L_Up      , 25,
                       Motor_L_Down    ,-25,
                       Motor_R_Up      ,-20,
                       Motor_R_Down    , 0 ,
                       Speed);

  
   /*  a=b=c=d=0;
   while(!(a && b && c && d))//8- + 25 degree - 25 degree - 20 degree 0 degree
  { 
    a=move_motor_to (Motor_L_Up,25,Speed) ;
    b=move_motor_to (Motor_L_Down,-25,Speed) ;
    c=move_motor_to (Motor_R_Up,-20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////


//backstep
void Step_Backward (MOTOR_SPEED Speed)
{
       move_motors_to_B( Motor_L_Up      , 25,
                       Motor_L_Down    ,-25,
                       Motor_R_Up      ,-20,
                       Motor_R_Down    , 0,
                       Speed);
  /*char a=0,b=0,c=0,d=0;
  //1
   while(!(a && b && c && d))//8- + 25 degree - 25 degree - 20 degree 0 degree
  { 
    a=move_motor_to (Motor_L_Up,25,Speed) ;
    b=move_motor_to (Motor_L_Down,-25,Speed) ;
    c=move_motor_to (Motor_R_Up,-20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }*/

       move_motors_to_B( Motor_L_Up      , 15,
                       Motor_L_Down    ,-60,
                       Motor_R_Up      , 0 ,
                       Motor_R_Down    ,-5 ,
                       Speed);
  
  /* a=b=c=d=0;
   //2
   while(!(a && b && c && d))//7- + 15 degree - 60 degree 0 degree - 5 degree
  { 
    a=move_motor_to (Motor_L_Up,15,Speed) ;
    b=move_motor_to (Motor_L_Down,-60,Speed) ;
    c=move_motor_to (Motor_R_Up,0,Speed);
    d=move_motor_to (Motor_R_Down,-5,Speed);
  }*/
       move_motors_to_B( Motor_L_Up      ,-15,
                       Motor_L_Down    ,-40,
                       Motor_R_Up      , 20,
                       Motor_R_Down    ,-20,
                       Speed);


  
    /* a=b=c=d=0;
     //3
  while(!(a && b && c && d))//6- - 15 degree - 40 degree + 20 degree - 20 degree
  { 
    a=move_motor_to (Motor_L_Up,-15,Speed) ;
    b=move_motor_to (Motor_L_Down,-40,Speed) ;
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,-20,Speed);
  }*/

       move_motors_to_B( Motor_L_Up      ,-25,
                       Motor_L_Down    ,-10,
                       Motor_R_Up      ,20 ,
                       Motor_R_Down    , 0 ,
                       Speed);

  
    /* a=b=c=d=0;
       //4
  while(!(a && b && c && d))//5- - 25 degree - 10 degree + 20 degree 0 degree
  { 
    a=move_motor_to (Motor_L_Up,-25,Speed) ;
    b=move_motor_to (Motor_L_Down,-10,Speed) ;
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }*/
  
       move_motors_to_B( Motor_L_Up      ,-20,
                       Motor_L_Down    , 0 ,
                       Motor_R_Up      , 25,
                       Motor_R_Down    ,-25,
                       Speed);   
   
   
   
   /*a=b=c=d=0;
    //5
  while(!(a && b && c && d)) // 4- - 20 degree 0 degree + 25 degree - 25 degree
  { 
    a=move_motor_to (Motor_L_Up,-20,Speed) ;
    b=move_motor_to (Motor_L_Down,0,Speed) ;
    c=move_motor_to (Motor_R_Up,25,Speed);
    d=move_motor_to (Motor_R_Down,-25,Speed);
  }*/

       move_motors_to_B( Motor_L_Up      , 0 ,
                       Motor_L_Down    ,-5 ,
                       Motor_R_Up      , 15,
                       Motor_R_Down    ,-60,
                       Speed);

  
  /* a=b=c=d=0;
     //6
  while(!(a && b && c && d)) // 3- 0 degree - 5 degree + 15 degree - 60 degree
  { 
    a=move_motor_to (Motor_L_Up,0,Speed) ;
    b=move_motor_to (Motor_L_Down,-5,Speed) ;
    c=move_motor_to (Motor_R_Up,15,Speed);
    d=move_motor_to (Motor_R_Down,-60,Speed);
  }*/

       move_motors_to_B( Motor_L_Up      , 20,
                       Motor_L_Down    ,-20,
                       Motor_R_Up      ,-15,
                       Motor_R_Down    ,-40,
                       Speed);

  
   /*a=b=c=d=0;
   //7
  while(!(a && b && c && d))//2- + 20 degree - 20 degree - 15 degree - 40 degree
  { 
    a=move_motor_to (Motor_L_Up,20,Speed) ;
    b=move_motor_to (Motor_L_Down,-20,Speed) ;
    c=move_motor_to (Motor_R_Up,-15,Speed);
    d=move_motor_to (Motor_R_Down,-40,Speed);
  }*/

       move_motors_to_B( Motor_L_Up      , 20,
                       Motor_L_Down    ,  0,
                       Motor_R_Up      ,-25,
                       Motor_R_Down    ,-10,
                       Speed);


  
   /*a=b=c=d=0;
  //8 
  while(!(a && b && c && d)) // 1- + 20 degree 0 degree - 25 degree - 10 degree
  { 
    a=move_motor_to (Motor_L_Up,20,Speed) ;
    b=move_motor_to (Motor_L_Down,0,Speed) ;
    c=move_motor_to (Motor_R_Up,-25,Speed);
    d=move_motor_to (Motor_R_Down,-10,Speed);
  }a=b=c=d=0;*/
   
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void Step_Test (MOTOR_SPEED Speed)
{  
  char a=0,b=0,c=0,d=0;
  while(!(c && d)) // 1- + 20 degree 0 degree - 25 degree - 10 degree
  {
    c=move_motor_to (Motor_R_Up,-25,Speed);
    d=move_motor_to (Motor_R_Down,-10,Speed);
  }
   a=b=c=d=0;
  while(!(c && d))//2- + 20 degree - 20 degree - 15 degree - 40 degree
  { 
    
    c=move_motor_to (Motor_R_Up,-15,Speed);
    d=move_motor_to (Motor_R_Down,-40,Speed);
  }
   a=b=c=d=0;
  while(!(c && d)) // 3- 0 degree - 5 degree + 15 degree - 60 degree
  { 
  
    c=move_motor_to (Motor_R_Up,15,Speed);
    d=move_motor_to (Motor_R_Down,-60,Speed);
  }
   a=b=c=d=0;
  while(!(c && d)) // 4- - 20 degree 0 degree + 25 degree - 25 degree
  { 
    
    c=move_motor_to (Motor_R_Up,25,Speed);
    d=move_motor_to (Motor_R_Down,-25,Speed);
  }
   a=b=c=d=0;
  while(!(c && d))//5- - 25 degree - 10 degree + 20 degree 0 degree
  { 
   
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }
   a=b=c=d=0;
  while(!(c && d))//6- - 15 degree - 40 degree + 20 degree - 20 degree
  { 
    
    c=move_motor_to (Motor_R_Up,20,Speed);
    d=move_motor_to (Motor_R_Down,-20,Speed);
  }
     a=b=c=d=0;
   while(!(c && d))//7- + 15 degree - 60 degree 0 degree - 5 degree
  { 
 
    c=move_motor_to (Motor_R_Up,0,Speed);
    d=move_motor_to (Motor_R_Down,-5,Speed);
  }
     a=b=c=d=0;
   while(!(c && d))//8- + 25 degree - 25 degree - 20 degree 0 degree
  { 
    c=move_motor_to (Motor_R_Up,-20,Speed);
    d=move_motor_to (Motor_R_Down,0,Speed);
  }
}
