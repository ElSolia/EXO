#define Selection_Pin_No_0 19
#define Selection_Pin_No_1 18
#define sensor_Pin 35
#define Enable_pin 5

void setup() {
  Serial.begin(115200);
  pinMode(Selection_Pin_No_0, OUTPUT);
  pinMode(Selection_Pin_No_1, OUTPUT);
  pinMode(Enable_pin, OUTPUT);
  digitalWrite(Enable_pin, LOW);


}

void loop() {
  digitalWrite(Selection_Pin_No_0, LOW);
  digitalWrite(Selection_Pin_No_1, LOW); // selecting channel  4
  delay(10);  // wait until the signal is stable

  Serial.print("Chan 0 = ");
  Serial.print(analogRead(sensor_Pin));
  

  digitalWrite(Selection_Pin_No_0, HIGH);
  digitalWrite(Selection_Pin_No_1, LOW); // selecting channel 8
  delay(10); // wait until the signal is stable

  Serial.print("  Chan 1 = ");
  Serial.println(analogRead(sensor_Pin));
  

   /*digitalWrite(Enable_pin, HIGH);
   delay(10);
   digitalWrite(Enable_pin, LOW);*/

 /* digitalWrite(Selection_Pin_No_0, LOW);
  digitalWrite(Selection_Pin_No_1, HIGH); // selecting channel 2
  delay(50);  // wait until the signal is stable

  /erial.print("  Chan 2 = ");
  Serial.print(analogRead(sensor_Pin));


  digitalWrite(Selection_Pin_No_0, HIGH);
  digitalWrite(Selection_Pin_No_1, HIGH); // selecting channel 2
  delay(50);  // wait until the signal is stable

  Serial.print("  Chan 3 = ");
  Serial.println(analogRead(sensor_Pin));*/





}
