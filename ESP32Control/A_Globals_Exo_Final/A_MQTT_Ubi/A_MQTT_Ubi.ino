//This code is edited by Sachin Soni(techiesms) for a project tutorital on
//Controlling Appliances and monitoring sensor's data over Internet using Ubidots MQTT server
//The video is uploaded on youtube whose link is :- https://youtu.be/LvzCeBce2mU

/****************************************
 * Include Libraries
 ****************************************/
#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "elsolia" // Put your WifiSSID here
#define PASSWORD "b4m1sh13abdo" // Put your wifi password here
#define TOKEN "BBFF-3EtINY1smPeyHUg6SMmgKAC4rfGGuX" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "soli2898" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

/****************************************
 * Define Constants
 ****************************************/
#define CHILD_EX_SUBSCRIBE "childex" // Assing the variable label 
#define SPEED_SUBSCRIBE    "speed" // Assing the variable label
#define STAND_P_SUBSCRIBE  "stand-position" // Assing the variable label
#define SET_P_SUBSCRIBE    "set-position" // Assing the variable label
#define STEP_B_SUBSCRIBE   "step-backward" // Assing the variable label
#define STEP_F_SUBSCRIBE   "step-forward" // Assing the variable label
#define MOVE_S_SUBSCRIBE   "move-separate" // Assing the variable label
#define LOWER_L_SUBSCRIBE  "lower-left" // Assing the variable label
#define LOWER_R_SUBSCRIBE  "lower-right" // Assing the variable label
#define UPPER_L_SUBSCRIBE  "upper-left" // Assing the variable label
#define UPPER_R_SUBSCRIBE  "upper_right" // Assing the variable label




#define DEVICE_LABEL "Super_Exo" // Assig the device label


char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char topicSubscribe1[100];
char topicSubscribe2[100];
char topicSubscribe3[100];
char topicSubscribe4[100];
char topicSubscribe5[100];
char topicSubscribe6[100];
char topicSubscribe7[100];
char topicSubscribe8[100];
char topicSubscribe9[100];
char topicSubscribe10[100];
char topicSubscribe11[100];


// Space to store values to send
//char str_sensor[10];

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
  client.subscribe(topicSubscribe1);
  client.subscribe(topicSubscribe2);
  client.subscribe(topicSubscribe3);
  client.subscribe(topicSubscribe4);
  client.subscribe(topicSubscribe5);
  client.subscribe(topicSubscribe6);
  client.subscribe(topicSubscribe7);
  client.subscribe(topicSubscribe8);
  client.subscribe(topicSubscribe9);
  client.subscribe(topicSubscribe10);
  client.subscribe(topicSubscribe11);
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
                                                  /**********     CHILD_EX = [4,5]
                                                                  SPEED=[1,2,3] 
                                                                  STAND_P = [6,7]
                                                                  SET_P = 
                                                  
                                                  *********/
  if (message == "0.0") {
    Serial.println("NULL");

    digitalWrite(2, LOW);
  }
  else if(message == "1.0") {
        Serial.println("1");

    digitalWrite(2, HIGH);
  }
   else if(message == "2.0") {
Serial.println("Stand position is off");
}
   else if(message == "3.0") {
Serial.println("Stand position is on");
  }
   else if(message == "4.0") {
Serial.println("set position is off");
  }
   else if(message == "5.0") {
Serial.println("set position is on");
  }
  Serial.write(payload, length);
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
//  pinMode(relay, OUTPUT);

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


  sprintf(topicSubscribe1, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, CHILD_EX_SUBSCRIBE);       //CHILD_EX_SUBSCRIBE
  sprintf(topicSubscribe2, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, SPEED_SUBSCRIBE);          //SPEED_SUBSCRIBE
  sprintf(topicSubscribe3, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, STAND_P_SUBSCRIBE);        //STAND_P_SUBSCRIBE
  sprintf(topicSubscribe4, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, SET_P_SUBSCRIBE);          //SET_P_SUBSCRIBE
  sprintf(topicSubscribe5, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, STEP_B_SUBSCRIBE);         //STEP_B_SUBSCRIBE
  sprintf(topicSubscribe6, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, STEP_F_SUBSCRIBE);         //STEP_F_SUBSCRIBE
  sprintf(topicSubscribe7, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, MOVE_S_SUBSCRIBE);         //MOVE_S_SUBSCRIBE
  sprintf(topicSubscribe8, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, LOWER_L_SUBSCRIBE);        //LOWER_L_SUBSCRIBE
  sprintf(topicSubscribe9, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, LOWER_R_SUBSCRIBE);        //LOWER_R_SUBSCRIBE
  sprintf(topicSubscribe10, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, UPPER_L_SUBSCRIBE);       //UPPER_L_SUBSCRIBE
  sprintf(topicSubscribe11, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, UPPER_R_SUBSCRIBE);       //UPPER_R_SUBSCRIBE

  client.subscribe(topicSubscribe1);
  client.subscribe(topicSubscribe2);
  client.subscribe(topicSubscribe3);
  client.subscribe(topicSubscribe4);
  client.subscribe(topicSubscribe5);
  client.subscribe(topicSubscribe6);
  client.subscribe(topicSubscribe7);
  client.subscribe(topicSubscribe8);
  client.subscribe(topicSubscribe9);
  client.subscribe(topicSubscribe10);
  client.subscribe(topicSubscribe11);


}

void loop() {
  if (!client.connected()) {
  client.subscribe(topicSubscribe1);
  client.subscribe(topicSubscribe2);
  client.subscribe(topicSubscribe3);
  client.subscribe(topicSubscribe4);
  client.subscribe(topicSubscribe5);
  client.subscribe(topicSubscribe6);
  client.subscribe(topicSubscribe7);
  client.subscribe(topicSubscribe8);
  client.subscribe(topicSubscribe9);
  client.subscribe(topicSubscribe10);
  client.subscribe(topicSubscribe11);
   
    reconnect();
  }

 // sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  //sprintf(payload, "%s", ""); // Cleans the payload
//  sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label





    /*sprintf(topicToSubscribe_variable_1, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_1, "%s/%s/lv", topicToSubscribe_variable_1, VARIABLE_LABEL_SUB_1);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_1);
    client.subscribe(topicToSubscribe_variable_1);*/
                                                                   /*#define CHILD_EX_SUBSCRIBE "childex" // Assing the variable label 
                                                                  #define SPEED_SUBSCRIBE "speed" // Assing the variable label
                                                                  #define STAND_P_SUBSCRIBE "stand-position" // Assing the variable label
                                                                  #define SET_P_SUBSCRIBE "set-position" // Assing the variable label
                                                                  #define STEP_B_SUBSCRIBE "step-backward" // Assing the variable label
                                                                  #define STEP_F_SUBSCRIBE "step-forward" // Assing the variable label
                                                                  #define MOVE_S_SUBSCRIBE "move-separate" // Assing the variable label
                                                                  #define LOWER_L_SUBSCRIBE "lower-left" // Assing the variable label
                                                                  #define LOWER_R_SUBSCRIBE "lower-right" // Assing the variable label
                                                                  #define UPPER_L_SUBSCRIBE "upper-left" // Assing the variable label
                                                                  #define UPPER_R_SUBSCRIBE "upper_right" // Assing the variable label*/
    
  /*float sensor = hallRead();
  Serial.print("Value of Sensor is:- ");
  Serial.println(sensor);
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor
  dtostrf(sensor, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);*/
  client.loop();
  delay(1000);
}
