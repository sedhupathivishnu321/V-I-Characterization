const int voltagePin = A0; // voltage sensor
const int currentPin = A1; //  current sensor

void setup() {
  Serial.begin(9600); 
}

void loop() {
  float voltage = analogRead(voltagePin) * (5.0 / 1023.0); 
  float current = analogRead(currentPin) * (5.0 / 1023.0); 


  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, Current: ");
  Serial.print(current);
  Serial.println(" A");

  delay(1000);
}
