/**
 *
 * Serial input to display for a 16x2 sunfounder display by Zach Stein
 * This code is licensed under the MIT license. (c) 2020.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * the above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
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
  int currentPosition = 0;
  int currentLine = 0;
  if (Serial.available() > 0) {
    lcd.clear();
    // Grab all lines from serial input
    while(Serial.available() > 0) {
      if (currentPosition == 16) {
        // line wrap
        currentLine = 1;
        currentPosition = 0;
      }
      lcd.setCursor(currentPosition, currentLine);
      lcd.print((char)Serial.read());  
      currentPosition++; 
    }
  }
  delay(1);
}

