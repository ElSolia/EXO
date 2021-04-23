char fsrPin = 4;     // the FSR and 10K pulldown are connected to a0

float FSR_Read(char FSR_Pin){
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
float fsrResistance;  // The voltage converted to resistance
float fsrConductance; 
float fsrForce;       // Finally, the resistance converted to force
  fsrReading = analogRead(FSR_Pin);  
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
 fsrVoltage = map(fsrReading, 0, 4095, 0, 3300);
  Serial.print("Voltage reading in mV = ");
  Serial.println(fsrVoltage);  
  if (fsrVoltage == 0) {
    Serial.println("No pressure");  
     fsrForce=0;
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 3300 - fsrVoltage;     // fsrVoltage is in millivolts so 3.3V = 3300mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
    //Serial.print("FSR resistance in ohms = ");
    //Serial.println(fsrResistance);
 
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
    //Serial.print("Conductance in microMhos: ");
    //Serial.println(fsrConductance);
 
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 0.8;
      //Serial.print("Force in Newtons: ");
      //Serial.println(fsrForce);      
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 50;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);  
                
    }
  }
  Serial.println("--------------------");
  //delay(1000);
  return (fsrForce);
  }
 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {
  float F = FSR_Read(fsrPin);
  Serial.print("Force ' loop ' in Newtons: ");
  Serial.println(F); 
  delay(1000);
}
