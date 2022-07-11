//Libraries
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

// Needed variables
#define REDPIN 12
#define GREENPIN 13
#define TEMPVOUT A0

int lcdColumns = 16;
int lcdRows = 2;
WiFiClient wifiClient;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {

    Serial.begin(9600);

    Serial.println("================================");
    Serial.println("===== DOBY's TEMPO LIMITED =====");
    Serial.println("================================");
    
    // LEDs
    pinMode(REDPIN, OUTPUT);
    pinMode(GREENPIN, OUTPUT);

    // LCD
    lcd.begin(5,4);
    lcd.init();
    lcd.backlight();    

    // SETUP WiFi
     WiFi.begin("RCA-WiFi", "rca@2019");
}

void loop() {

  // Write to LCD
  
  lcd.setCursor(0,0);
  lcd.print("DOBY's TEMPO LIMITED");
  delay(2000);

  // Read Temperature Meter
  int analogValue = analogRead(TEMPVOUT);
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;

  Serial.print("Degrees RED=   ");
  Serial.println(celsius);

  String mData="";
  String dummy_device = "tibigi";
  String dummy_distance = "working cm";
  mData = "device="+dummy_device+"&distance="+(String)celsius;
    
  sendData(80, "insecure.benax.rw", "/iot/" , mData); 
  
  if(celsius < 27 || celsius > 30 ){
    // Turn on RED LED
    digitalWrite(REDPIN, HIGH);
    // Turn off GREEN LED
    digitalWrite(GREENPIN, LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("YO BODY IN DANGER");

    
  }else{
    // Turn on RED LED
    digitalWrite(REDPIN, LOW);
    // Turn off GREEN LED
    digitalWrite(GREENPIN, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("HEALTHY :'");   
  }

  delay(2000);

}


void sendData(const int httpPort, const char* host,const char* filepath , String data){
  
  wifiClient.connect(host, httpPort); 

  wifiClient.println("POST "+(String)filepath+" HTTP/1.1");
  wifiClient.println("Host: " + (String)host);
  wifiClient.println("User-Agent: ESP8266/1.0");
  wifiClient.println("Content-Type: application/x-www-form-urlencoded");
  wifiClient.println("Content-Length: " +(String)data.length());
  wifiClient.println();
  wifiClient.print(data);

  Serial.println("Response: " + wifiClient.readStringUntil('\n'));

}