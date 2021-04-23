
        /***************************** wifi Functions **************************/

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);

  //added
  //unsigned int x = message.toInt();   // verified
  //Serial2.print(x);

  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(1000);
    }
  }
}



            /***************************************** Main Functions ****************************************/

/************ Void Setup *****************/
            
void setup() {
  
  /*********** analog Mux Setup ***********/
  pinMode(Selection_Pin_No_0, OUTPUT);
  pinMode(Selection_Pin_No_1, OUTPUT);



  /************* EMG Setup ***************/

  EMG_init(EMG_Sensor_0  , emg_Sensor_0_Pin );
  EMG_init(EMG_Sensor_1  , emg_Sensor_1_Pin );
  EMG_init(EMG_Sensor_2  , emg_Sensor_2_Pin );
  EMG_init(EMG_Sensor_3  , emg_Sensor_3_Pin );
  EMG_init(EMG_Sensor_4  , emg_Sensor_4_Pin );
  EMG_init(EMG_Sensor_5  , emg_Sensor_5_Pin );





  /************** Serial Monitor ***************/

  Serial.begin(115200);
  //Serial2.begin(115200, SERIAL_8N1, 16, 17);






  /**********  FSR Setup ****************/

  //pinMode(FSR_LEFT_Pin,INPUT);
  //pinMode(FSR_RIGHT_Pin,INPUT);





  /*********** MPU Setup **************/

  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");





  /******* Wifi setup *******/

  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.print("Wait for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

}







/************ Void Loop *****************/

void loop() {

  if (!client.connected()) {
    reconnect();
  }




  /************* MPU  *************/

  mpu.update();
  float MPU_FB = mpu.getAngleZ();
  float MPU_LR = mpu.getAngleX();
  /*Serial.print("Value of Z is:- ");
  Serial.println(MPU_FB);

  Serial.print("Value of x is:- ");
  Serial.println(MPU_LR);*/




  /************* FSR ***************/

  float FSR_L = 0.0 ;
  float FSR_R = 0.0 ;

  digitalWrite(Selection_Pin_No_0, LOW);
  digitalWrite(Selection_Pin_No_1, LOW); // selecting channel 0
  delay(10);  // wait until the signal is stable
  FSR_L = FSR_Read(FSR_LEFT_Pin);

  digitalWrite(Selection_Pin_No_0, HIGH);
  digitalWrite(Selection_Pin_No_1, LOW); // selecting channel 1
  delay(10); // wait until the signal is stable
  FSR_R = (FSR_Read(FSR_RIGHT_Pin))/2;

  /*Serial.print("Value of FSR_L is:- ");
  Serial.println(FSR_L);

  Serial.print("Value of FSR_R is:- ");
  Serial.println(FSR_R);*/




  /************** EMG  ****************/

  uint16_t L_L_EMG = EMG_sens_Read(EMG_Sensor_0);
  uint16_t L_R_EMG = EMG_sens_Read(EMG_Sensor_1);

  digitalWrite(Selection_Pin_No_0, LOW);
  digitalWrite(Selection_Pin_No_1, HIGH); // selecting channel 2
  delay(25);  // wait until the signal is stable
 
  uint16_t M_L_EMG = (EMG_sens_Read(EMG_Sensor_2)) * 3;

  uint16_t M_R_EMG = (EMG_sens_Read(EMG_Sensor_3)) * 3;
  uint16_t U_L_EMG = (EMG_sens_Read(EMG_Sensor_4)) / 4;
  uint16_t U_R_EMG = (EMG_sens_Read(EMG_Sensor_5)) / 3;

  /*Serial.print("Value of L_L_EMG is:- ");
  Serial.println(L_L_EMG);

  Serial.print("Value of L_/R_EMG is:- ");
  Serial.println(L_R_EMG);

  Serial.print("Value of M_L_EMG is:- ");
  Serial.println(M_L_EMG);

  Serial.print("Value of M_R_EMG is:- ");
  Serial.println(M_R_EMG);

  Serial.print("Value of U_L_EMG is:- ");
  Serial.println(U_L_EMG);

  Serial.print("Value of U_R_EMG is:- ");
  Serial.println(U_R_EMG);*/

  /*
      char str_MPU_FP[10];
      char str_MPU_LR[10];
      char str_L_FSR[10];
      char str_R_FSR[10];
      char str_L_L_EMG[10];
      char str_L_R_EMG[10];
      char str_M_L_EMG[10]; 
      char str_M_R_EMG[10];
      char str_U_L_EMG[10];
      char str_U_R_EMG[10];*/



  /*********** Converting values to float with 2 decimal points  *********/

  dtostrf(MPU_FB, 4, 2, str_MPU_FP);
  dtostrf(MPU_LR, 4, 2, str_MPU_LR);
  dtostrf(FSR_L, 4, 2, str_L_FSR);
  delay(25);
  dtostrf(FSR_R, 4, 2, str_R_FSR);
  dtostrf(L_L_EMG, 4, 2, str_L_L_EMG);
  dtostrf(L_R_EMG, 4, 2, str_L_R_EMG);
  dtostrf(M_L_EMG, 4, 2, str_M_L_EMG);
    delay(25);
  dtostrf(M_R_EMG, 4, 2, str_M_R_EMG);
  dtostrf(U_L_EMG, 4, 2, str_U_L_EMG);
  dtostrf(U_R_EMG, 4, 2, str_U_R_EMG);
  
  Serial.print("Value of Z is:- ");
  Serial.println(str_MPU_FP);

  Serial.print("Value of x is:- ");
  Serial.println(str_MPU_LR);
  
  Serial.print("Value of FSR_L is:- ");
  Serial.println(str_L_FSR);

  Serial.print("Value of FSR_R is:- ");
  Serial.println(str_R_FSR);
  
  Serial.print("Value of L_L_EMG is:- ");
  Serial.println(str_L_L_EMG);

  Serial.print("Value of L_R_EMG is:- ");
  Serial.println(str_L_R_EMG);

  Serial.print("Value of M_L_EMG is:- ");
  Serial.println(str_M_L_EMG);

  Serial.print("Value of M_R_EMG is:- ");
  Serial.println(str_M_R_EMG);

  Serial.print("Value of U_L_EMG is:- ");
  Serial.println(str_U_L_EMG);

  Serial.print("Value of U_R_EMG is:- ");
  Serial.println(str_U_R_EMG);

  /************ publishing Data to ubidots  ****************/

  
    sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_1);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_MPU_FP);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic1, payload);

delay(50);
    sprintf(topic2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_2);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_MPU_LR);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic2, payload);
delay(50);

    sprintf(topic3, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_3);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_L_FSR);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic3, payload);
delay(50);

    sprintf(topic4, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_4);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_R_FSR);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic4, payload);
delay(50);

    sprintf(topic5, "%s%s", "/v1.6/devices/", DEVICE_LABEL); 
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_5);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_L_L_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic5, payload);
delay(50);

    sprintf(topic6, "%s%s", "/v1.6/devices/", DEVICE_LABEL); 
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_6);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_L_R_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic6, payload);
delay(50);

    sprintf(topic7, "%s%s", "/v1.6/devices/", DEVICE_LABEL); 
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_7);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_M_L_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic7, payload);
delay(50);

    sprintf(topic8, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_8);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_M_R_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic8, payload);
delay(50);

    sprintf(topic9, "%s%s", "/v1.6/devices/", DEVICE_LABEL); 
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_9);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_U_L_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic9, payload);
delay(50);

    sprintf(topic10, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload, "%s", "");
    sprintf(payload, "{\"%s\":", VARIABLE_LABEL_10);
    sprintf(payload, "%s {\"value\": %s}}", payload, str_U_R_EMG);
    //Serial.println("Publishing temperature to Ubidots Cloud");
    client.publish(topic10, payload);
    
delay(50);



Serial.println("---------------------------------------");
  // client.publish(topic, payload);
  client.loop();
  delay(1000); // 4000 dots per day
}
