/********************************
 * name:I2C LCD1602
 * function:You should now see your I2C LCD1602 display the flowing characters: "SunFounder" and "hello, world".
 ********************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int tim = 500; //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
int currentPosition = 0;
void setup()
{
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.clear();
  Serial.begin(9600);
}
/*********************************************************/
void loop() 
{
  if (Serial.available() > 0) {
    if (currentPosition == 11) {
      currentPosition = 0; // reset;
      lcd.clear();
    }
    lcd.setCursor(currentPosition,0); //Top line current position.
    lcd.print((char)Serial.read()); // Add character to the display
    currentPosition++; 
  }
  delay(1);
}

