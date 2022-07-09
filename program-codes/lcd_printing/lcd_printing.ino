#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16 , 2) ;
void setup(){
 lcd.begin();
 lcd.backlight();
lcd.print("hello");
}
// the loop function runs over and over again forever
void loop(){
//lcd.clear();
//lcd.print("hello");
//delay(500);
//lcd.clear();
}
