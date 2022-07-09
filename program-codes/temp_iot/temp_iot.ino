void setup(){
  Serial.begin(9600);
}

void loop(){
    int rawData = analogRead(A0);
    float vcc = 5.0;
    float voltage = rawData * (vcc / 1024.0);
    float temperature = voltage * 100;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    delay(500);
}   
