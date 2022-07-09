#include <ESP8266WiFi.h>
WiFiClient wifiClient;
const int trigPin = 14;
const int echoPin = 16;
void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  WiFi.begin("RCA-WiFi", "rca@2019");
}
long get_distance(){
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return ((duration / 2) / 29.1);
}
void loop(){
  String data = "device=RCA0125BGE&distance=20";
  String host = "192.168.1.68";
  String path = "/iot/";
  int port = 8000;
 int distance=25;
 String request = "POST /iot?device=RCA0125BGE&distance="+(String)distance+" HTTP/1.1";
  wifiClient.connect(host, port);
  wifiClient.println(request);
  wifiClient.println("Host: "+host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("C: ESP8266/1.0");
  wifiClient.println();
 // wifiClient.print(data);
  Serial.println("Response: "+wifiClient.readStringUntil('\n'));
  delay(5000);
}
