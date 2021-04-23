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
#define MQTT_CLIENT_NAME "Elsokia_Sensor" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                           //it should be a random and unique ascii string and different from all other devices

/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL1 "left-foot-force-sensor" // Assing the variable label
#define VARIABLE_LABEL2 "right-foot-force-sensor" // Assing the variable label
#define VARIABLE_LABEL3 "lower-left-emg" // Assing the variable label
#define VARIABLE_LABEL4 "lower-right-emg" // Assing the variable label
#define VARIABLE_LABEL5 "mid-left-emg" // Assing the variable label
#define VARIABLE_LABEL6 "mid-right-emg" // Assing the variable label
#define VARIABLE_LABEL7 "upper-left-emg" // Assing the variable label
#define VARIABLE_LABEL8 "upper-right-emg" // Assing the variable label
#define VARIABLE_LABEL9 "inclination-forward-backward" // Assing the variable label
#define VARIABLE_LABEL10 "inclination-right-left" // Assing the variable label

#define DEVICE_LABEL "SuperExoSensorUploading" // Assig the device label


char mqttBroker[]  = "things.ubidots.com";
char payload[100];
char topic[150];

// Space to store values to send
char str_sensor[10];

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
/*void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  if (message == "0") {
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
  
  Serial.write(payload, length);
  Serial.println();
}*/

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
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
  //client.setCallback(callback);

  //sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  
  //client.subscribe(topicSubscribe);
}

void loop() {
  if (!client.connected()) {
    //client.subscribe(topicSubscribe);   
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1); // Adds the variable label
  
  float sensor = hallRead();
  Serial.print("Value of Sensor is:- ");
  Serial.println(sensor);
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(sensor, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
}
