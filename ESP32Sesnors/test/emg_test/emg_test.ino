
#define EMG_Sensor_pin 33
typedef enum {
  EMG_Sensor_0,
  EMG_Sensor_1,
  EMG_Sensor_2,
  EMG_Sensor_3,
  EMG_Sensor_4,
  EMG_Sensor_5
  }EMG_sensor_ID; 
const uint16_t EMG_sens_SOOR[6]={650,620,1200,3000,2250,2600}; // Start of operating Range
/* 
 * EMG_Sensor_0 tested on pin no. 36 and the normal value = 650; changes from 0 to 325
 * EMG_Sensor_1 tested on pin no. 39 and the normal value = 620; changes from 0 to 325
 * EMG_Sensor_2 tested on pin no. 35 and the normal value = 1200; no big changes 
 * EMG_Sensor_3 tested on pin no. 32 and the normal value = 3000;no big changes
 * EMG_Sensor_4 tested on pin no. 34 and the normal value = 2250; changes from 0 to 1200
 * EMG_Sensor_5 tested on pin no. 33 and the normal value = 2600;changes from 0 to 1000
*/
//const bool EMG_sens_Fn[6]={0,0,0,1,0,1}; // the fuctionality of the sensor (0--> decreasing , 1--> increasing )

 char EMG_sens_PIN[6];  // sensor PIN number with respect to ID

void EMG_init(EMG_sensor_ID sensorname , char EMG_pin );
uint16_t EMG_sens_Read(EMG_sensor_ID sensorname);


void EMG_init(EMG_sensor_ID sensorname , char EMG_pin ) { // Fn to initialize the pin number of the Sensor with respect to it ID
  EMG_sens_PIN[sensorname] = EMG_pin; // asign the PIN number to the specified Sensor ID
}

 uint16_t EMG_sens_Read(EMG_sensor_ID sensorname) { // Fn to read the sensor level ( 5 levels ) according to it's start oprating point and it's funtionality
   uint16_t EMG_reading = analogRead(EMG_sens_PIN[sensorname]);
   
  // check the functionality
  if (EMG_reading<EMG_sens_SOOR[sensorname]) {
    EMG_reading =  EMG_sens_SOOR[sensorname] - EMG_reading;
  }
  else if (EMG_reading>EMG_sens_SOOR[sensorname]) {
    EMG_reading =EMG_reading - EMG_sens_SOOR[sensorname] ;
  }
   //get the reading level
  //int EMG_sens_lev = abs(EMG_reading) / 2;
  return (abs(EMG_reading)/2);

}


void setup() {
Serial.begin(9600);
EMG_init(EMG_Sensor_5 ,EMG_Sensor_pin );
pinMode(EMG_Sensor_pin,INPUT);
}

void loop() {
 uint16_t x = 0;
 x= EMG_sens_Read(EMG_Sensor_5);
 uint16_t y = analogRead(EMG_Sensor_pin);
//Serial.print("the Function Reading = ");
Serial.print(x);
Serial.print("\t");
//Serial.print("the exact Reading = ");
Serial.println(y);
delay(10);
}
