
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
