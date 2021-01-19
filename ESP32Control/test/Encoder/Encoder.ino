
void Encoder_Init (Motor_ID encodername,char pinnumber1,char pinnumber2) // should be initialized for each encoder , void setup 
{
  Encoder_Pins[encodername][Encoder_CLK]= pinnumber1; // save the pins in the encoder global variable
  Encoder_Pins[encodername][Encoder_DT]= pinnumber2; // save the pins in the encoder global variable
  
  pinMode(Encoder_Pins[encodername][0],INPUT); // assign the first pin
  pinMode(Encoder_Pins[encodername][1],INPUT);
  
}

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
    
    
  }
