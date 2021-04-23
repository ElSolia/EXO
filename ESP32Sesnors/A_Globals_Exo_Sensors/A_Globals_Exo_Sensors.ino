#include <WiFi.h>
#include <PubSubClient.h>
#include "Wire.h"
#include <MPU6050_light.h>


                      /****************************** Wifi Parameters  ****************************/
                      
#define WIFISSID "elsolia" // Put your WifiSSID here
#define PASSWORD "b4m1sh13abdo" // Put your wifi password here
#define TOKEN "BBFF-3EtINY1smPeyHUg6SMmgKAC4rfGGuX" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "a7sd35w69cvb" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 





                    /************************* Variables ID  From Website **************************/   
                    
#define VARIABLE_LABEL_1   "mpu_forward_backward" // Assing the variable label
#define VARIABLE_LABEL_2   "mpu_left_right"       // Assign the variable label
#define VARIABLE_LABEL_3   "left-foot-force-sensor"
#define VARIABLE_LABEL_4   "right-foot-force-sensor"
#define VARIABLE_LABEL_5   "lower-left-emg"
#define VARIABLE_LABEL_6   "lower-right-emg"
#define VARIABLE_LABEL_7   "mid-left-emg"
#define VARIABLE_LABEL_8   "mid-right-emg"
#define VARIABLE_LABEL_9   "upper-left-emg"
#define VARIABLE_LABEL_10  "upper-right-emg"


#define DEVICE_LABEL "super-exo" // Assig the device label




                    /************************ array to store topics to send ***************************/
                    
char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[50]; // was 100 indexes 
char topic1[50]; // was 150 indexes
char topic2[50];
char topic3[50];
char topic4[50];
char topic5[50];
char topic6[50];
char topic7[50];
char topic8[50];
char topic9[50];
char topic10[50];




                  /**************************** Space to store values to send ******************************/       
char str_MPU_FP[10];
char str_MPU_LR[10];
char str_L_FSR[10];
char str_R_FSR[10];
char str_L_L_EMG[10];
char str_L_R_EMG[10];
char str_M_L_EMG[10];
char str_M_R_EMG[10];
char str_U_L_EMG[10];
char str_U_R_EMG[10];




              /******************************************* EMG ************************************************/
#define emg_Sensor_0_Pin 36
#define emg_Sensor_1_Pin 33 //mux
#define emg_Sensor_2_Pin 32
#define emg_Sensor_3_Pin 39
#define emg_Sensor_4_Pin 35
#define emg_Sensor_5_Pin 34 

typedef enum {
  EMG_Sensor_0,
  EMG_Sensor_1,
  EMG_Sensor_2,
  EMG_Sensor_3,
  EMG_Sensor_4,
  EMG_Sensor_5
  }EMG_sensor_ID; 

unsigned char EMG_sens_PIN[6];  // sensor PIN number with respect to ID
const uint16_t EMG_sens_SOOR[6]={650,620,1200,3000,2250,2600}; // Start of operating Range
  
void EMG_init(EMG_sensor_ID sensorname , char EMG_pin );
uint16_t EMG_sens_Read(EMG_sensor_ID sensorname);

/* 
 * EMG_Sensor_0 tested on pin no. 36 and the normal value = 650; changes from 0 to 325
 * EMG_Sensor_1 tested on pin no. 39 and the normal value = 620; changes from 0 to 325
 * EMG_Sensor_2 tested on pin no. 35 and the normal value = 1200; no big changes 
 * EMG_Sensor_3 tested on pin no. 32 and the normal value = 3000;no big changes
 * EMG_Sensor_4 tested on pin no. 34 and the normal value = 2250; changes from 0 to 1200
 * EMG_Sensor_5 tested on pin no. 33 and the normal value = 2600;changes from 0 to 1000
*/

//const bool EMG_sens_Fn[6]={0,0,0,0,0,1}; // the fuctionality of the sensor (0--> decreasing , 1--> increasing )



                      /****************************** Analog Mux **********************************/
#define Selection_Pin_No_0 19
#define Selection_Pin_No_1 18





                      /******************************  FSR  ************************************/ 
#define FSR_LEFT_Pin  33     // the FSR and 10K pulldown are connected to fsrPin
#define FSR_RIGHT_Pin 33     // the FSR and 10K pulldown are connected to fsrPin
//#define Enable_pin 5
float FSR_Read(char FSR_Pin);





                    /******************************** MPU **********************************/ 
MPU6050 mpu(Wire);





                  /************************* Auxiliar Functions ************************/
                  
WiFiClient ubidots;
PubSubClient client(ubidots);
