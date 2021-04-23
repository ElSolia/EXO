//int rec_Byte;
void setup() {
  Serial2.begin(115200);
  Serial.begin(115200);
  Serial2.setTimeout(10); // set the time that the function called paraseInt will wait to the end of the int
  pinMode(24,OUTPUT);

}


void loop() {
  while (Serial2.available() == 0) {
     digitalWrite(24,LOW);}
     
  digitalWrite(24,HIGH);
  
  uint16_t rec_Byte = Serial2.read(); //can't read the negative number
  //int x = rec_Byte.toInt();
  //Serial2.parseInt(); read the value if represented in 4 digits
  Serial.print("the value recieved = ");
  Serial.println(rec_Byte);

}
