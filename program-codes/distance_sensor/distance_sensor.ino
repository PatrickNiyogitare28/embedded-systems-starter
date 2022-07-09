#include<Wire.h>
#include<LiquidCrystal_I2C.h>

int redPin = 13; 
int greenPin = 12;//GPIO 13 corresponds to pin D7. You can check the pinout.
const int trigPin = 14;
const int echoPin = 16;
long duration, distance;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup(){
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
lcd.print(distance);
   }

   else {
digitalWrite(greenPin,LOW);
digitalWrite(redPin,HIGH);
     Serial.print(distance);
     Serial.println(" cm");
   }
   delay(500);
}