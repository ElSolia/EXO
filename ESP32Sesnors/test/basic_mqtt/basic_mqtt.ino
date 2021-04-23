//This code is edited by Sachin Soni(techiesms) for a project tutorital on
//Controlling Appliances and monitoring sensor's data over Internet using Ubidots MQTT server
//The video is uploaded on youtube whose link is :- https://youtu.be/LvzCeBce2mU

/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <PubSubClient.h>

#include "Wire.h"
#include <MPU6050_light.h>

#define WIFISSID "eslam" // Put your WifiSSID here
#define PASSWORD "Eh123456789" // Put your wifi password here
#define TOKEN "BBFF-3EtINY1smPeyHUg6SMmgKAC4rfGGuX" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "a7sd35w69cvb" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL1 "mpu_forward_backward" // Assing the variable label
#define VARIABLE_LABEL2 "mpu_left_right" // Assing the variable label
//#define VARIABLE_LABEL_SUBSCRIBE "childex" // Assing the variable label
#define DEVICE_LABEL "super-exo" // Assig the device label

//#define relay 2 // Set the GPIO26 as RELAY

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic1[150];
char topic2[150];

//char topicSubscribe[100];
// Space to store values to send
char str_sensor1[10];
char str_sensor2[10];



MPU6050 mpu(Wire);

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
      //client.subscribe(topicSubscribe);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  if (message == "0.0") {
//    digitalWrite(relay, LOW);
  } else {
//    digitalWrite(relay, HIGH);
  }
  
  Serial.write(payload, length);
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  //MPU
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  //pinMode(relay, OUTPUT);

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

  //sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  
  //client.subscribe(topicSubscribe);
}

void loop() {
  if (!client.connected()) {
    reconnect();
    //client.subscribe(topicSubscribe);   
  }   
  mpu.update();
   float sensor1 = mpu.getAngleZ();
   //sensor1 +=1;
  Serial.print("Value of Sensor is:- ");
  Serial.println(sensor1);
  //4 is mininum width, 2 is precision; float value is copied onto str_sensor
  dtostrf(sensor1, 4, 2, str_sensor1);
  
   float sensor2 = mpu.getAngleX();
   //sensor2 +=1;
  Serial.print("Value of Sensor is:- ");
  Serial.println(sensor2);
  //4 is mininum width, 2 is precision; float value is copied onto str_sensor
  dtostrf(sensor2, 4, 2, str_sensor2);
  
  sprintf(topic1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor1);
  Serial.println("Publishing temperature to Ubidots Cloud");
  client.publish(topic1, payload);
 
  sprintf(topic2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL2);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor2);
  Serial.println("Publishing humidity to Ubidots Cloud");
  client.publish(topic2, payload);
 
  /*sprintf(topic3, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL3);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_Pressure);
  Serial.println("Publishing Pressure data to Ubidots Cloud");
  client.publish(topic3, payload);
 
  sprintf(topic4, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL4);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_Altitude);
  Serial.println("Publishing Altitude data to Ubidots Cloud");
  client.publish(topic4, payload);
 
  sprintf(topic5, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL5);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_DewPoint);
  Serial.println("Publishing Dew Point data to Ubidots Cloud");
  client.publish(topic5, payload);
 
  sprintf(topic6, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL6);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_Gas);
  Serial.println("Publishing Gas data to Ubidots Cloud");
  client.publish(topic6, payload);
  

  
 /* sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);*/
  
  client.loop();
  delay(10);
}
