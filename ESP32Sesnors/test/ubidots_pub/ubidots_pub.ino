#include <WiFi.h>
#include <PubSubClient.h>
#include "Wire.h"
#include <MPU6050_light.h>


#define WIFISSID "elsolia" // Put your WifiSSID here
#define PASSWORD "b4m1sh13abdo" // Put your wifi password here
#define TOKEN "BBFF-8sN3wAxEEY9LMvJjr6yyp6llQm2Lxu" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "AaSs5987Dwcv" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL_SUBSCRIBE "childex" // Assing the variable label
const char * VARIABLE_LABEL_1 =  "inclination-forward-backward"; // Assing the variable label
const char * VARIABLE_LABEL_2 =  "inclination-right-left";       // Assign the variable label
/*const char * VARIABLE_LABEL_3 =  "left-foot-force-sensor";
const char * VARIABLE_LABEL_4 =  "right-foot-force-sensor";
const char * VARIABLE_LABEL_5 =  "lower-left-emg";
const char * VARIABLE_LABEL_6 =  "lower-right-emg";
const char * VARIABLE_LABEL_7 =  "mid-left-emg";
const char * VARIABLE_LABEL_8 =  "mid-right-emg";
const char * VARIABLE_LABEL_9 =  "upper-left-emg";
//const char * VARIABLE_LABEL_10 = "upper-right-emg";
*/

const char * DEVICE_LABEL = "super-exo"; // Assig the device label

 // Set the GPIO12 as SENSOR

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[300];
char topic[150];
char topicSubscribe[100];

// Space to store values to send
char str_MPU_FP[10];
char str_MPU_LR[10];
/*char str_L_FSR[10];
char str_R_FSR[10];
char str_L_L_EMG[10];
char str_L_R_EMG[10];
char str_M_L_EMG[10];
char str_M_R_EMG[10];
char str_U_L_EMG[10];
char str_U_R_EMG[10];*/



/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);


MPU6050 mpu(Wire);


void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  unsigned int x = message.toInt();   // verified                                            
  Serial.println(x);
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
      delay(2000);
    }
  }
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ }
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); 
  
  WiFi.begin(WIFISSID, PASSWORD);
  
  // Assign the pin as INPUT 
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(32,INPUT);
  pinMode(12,INPUT);
  pinMode(35,INPUT);
  pinMode(34,INPUT);
  pinMode(25,INPUT);
  pinMode(26,INPUT);

  

  
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
  

  
  sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  client.subscribe(topicSubscribe);
}

void loop() {
  if (!client.connected()) {
    reconnect();
    client.subscribe(topicSubscribe);   

  }
 mpu.update();

 float MPU_FB=mpu.getAngleX(); 
 float MPU_LR=mpu.getAngleZ();
/* float FSR_L=analogRead(25); 
 float FSR_R=analogRead(26); 
 
 int L_L_EMG=analogRead(35);
 int L_R_EMG=analogRead(4);
 int M_L_EMG=analogRead(12);
 int M_R_EMG=analogRead(32);
 int U_L_EMG=analogRead(34);*/
 //int U_R_EMG=1;
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
  dtostrf(MPU_FB, 4, 2, str_MPU_FP);
  dtostrf(MPU_LR, 4, 2, str_MPU_LR);
 /* dtostrf(FSR_L, 4, 2, str_L_FSR);
  dtostrf(FSR_R, 4, 2, str_R_FSR);
  dtostrf(L_L_EMG, 4, 2, str_L_L_EMG);
  dtostrf(L_R_EMG, 4, 2, str_L_R_EMG);
  dtostrf(M_L_EMG, 4, 2, str_M_L_EMG);
  dtostrf(M_R_EMG, 4, 2, str_M_R_EMG);
  dtostrf(U_L_EMG, 4, 2, str_U_L_EMG);*/
  //dtostrf(U_R_EMG, 4, 2, str_U_R_EMG);

  
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\": %s,", VARIABLE_LABEL_1, str_MPU_FP); // Adds the variable label
  sprintf(payload, "%s\"%s\": %s,", payload, VARIABLE_LABEL_2, str_MPU_LR); // Adds the variable label
  /*sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_3, str_L_FSR); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_4, str_R_FSR); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_5, str_L_L_EMG); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_6, str_L_R_EMG); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_7, str_M_L_EMG); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_8, str_M_R_EMG); 
  sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_9, str_U_L_EMG); 
  //sprintf(payload, "%s\"%s\": %s}", payload, VARIABLE_LABEL_10, str_U_R_EMG); */


 
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
 
  
  /*sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  Serial.print("Distance = ");
  Serial.println(distance);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.println("payload");
  Serial.println(payload);*/

  
  client.publish(topic, payload);
  client.loop();
  delay(100);
}
