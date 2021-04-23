void setup() {
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}
  int x = 0 ; 

void loop() {
  //Serial2.write(x); 
  //delay(1000);
  Serial2.print(x);       // serial print are most accurate " verified  "
  delay(1000);
  ++x;


}
