const unsigned int EMG_sens_SOOR[6]={1000,1000,2700,2800,1800,2350}; // Start of operating Range

const bool EMG_sens_Fn[6]={0,0,0,0,0,1}; // the fuctionality of the sensor (0--> decreasing , 1--> increasing )

unsigned char EMG_sens_PIN[6];  // sensor PIN number with respect to ID

typedef enum {
  EMG_Sensor_1,
  EMG_Sensor_2,
  EMG_Sensor_3,
  EMG_Sensor_4,
  EMG_Sensor_5,
  EMG_Sensor_6
  }EMG_sensor_ID; 
  
void EMG_init(EMG_sensor_ID sensorname , char EMG_pin ){ // Fn to initialize the pin number of the Sensor with respect to it ID
  
    EMG_sens_PIN[sensorname]=EMG_pin; // asign the PIN number to the specified Sensor ID 
    
  }

char EMG_sens_Read(EMG_sensor_ID sensorname){ // Fn to read the sensor level ( 5 levels ) according to it's start oprating point and it's funtionality
  
  unsigned int EMG_reading=0;



                                  // check the functionality 
  if(EMG_sens_Fn[sensorname]==0){ 
    EMG_reading =  EMG_sens_SOOR[sensorname] - analogRead(EMG_sens_PIN[sensorname]);
    }
  
  
   else if(EMG_sens_Fn[sensorname]==1){
    EMG_reading = analogRead(EMG_sens_PIN[sensorname]) -EMG_sens_SOOR[sensorname] ;
    }


                                    // get the reading level
   char EMG_sens_lev = EMG_reading /100; 
  
  return (EMG_sens_lev); 
  
  }
