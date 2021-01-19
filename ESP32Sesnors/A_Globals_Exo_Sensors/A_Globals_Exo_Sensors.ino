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
#define SPEED_SUBSCRIBE "speed" // Assing the variable label
#define STAND_P_SUBSCRIBE "stand-position" // Assing the variable label
#define SET_P_SUBSCRIBE "set-position" // Assing the variable label
#define STEP_B_SUBSCRIBE "step-backward" // Assing the variable label
#define STEP_F_SUBSCRIBE "step-forward" // Assing the variable label
#define MOVE_S_SUBSCRIBE "move-separate" // Assing the variable label
#define LOWER_L_SUBSCRIBE "lower-left" // Assing the variable label
#define LOWER_R_SUBSCRIBE "lower-right" // Assing the variable label
#define UPPER_L_SUBSCRIBE "upper-left" // Assing the variable label
#define UPPER_R_SUBSCRIBE "upper_right" // Assing the variable label




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
char str_sensor[10];

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);
