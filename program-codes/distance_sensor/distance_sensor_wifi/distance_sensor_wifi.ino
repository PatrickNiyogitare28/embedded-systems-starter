#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
WiFiClient wifiClient;

int redPin = 13; 
int greenPin = 15;//GPIO 13 corresponds to pin D7. You can check the pinout.
const int trigPin = 12;
const int echoPin = 14;
long duration, distance;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
WiFi.begin("RCA-WiFi", "rca@2019");
lcd.begin();
lcd.backlight();
// initialize ledPin as an output.
Serial.begin(9600);
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
 pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
// the loop function runs over and over again forever
void loop(){
  String host = "192.168.1.68";
  String path = "/iot/";
    int port = 8000;
 digitalWrite(trigPin, LOW);

  delayMicroseconds(2);         

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

 

  if (distance >= 100 || distance <= 0){
digitalWrite(greenPin,HIGH);
digitalWrite(redPin,LOW);
   Serial.println("Out of range");
  
   }

   else {
digitalWrite(greenPin,LOW);
digitalWrite(redPin,HIGH);
   
   }
   lcd.clear();
   lcd.print("distance");
   lcd.setCursor(0,1);   
   lcd.print(distance);
    String request = "POST /iot?device=RCA0125BGE&distance="+(String)distance+" HTTP/1.1";
  wifiClient.connect(host, port);
  wifiClient.println(request);
  wifiClient.println("Host: "+host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("C: ESP8266/1.0");
  wifiClient.println();
  Serial.println("Response: "+wifiClient.readStringUntil('\n'));
   delay(500);
}
