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

boolean backlightState = true;

// Button variable definitions
const int buttonPin = 6;     // the number of the pushbutton pin
// Use the onboard LED for debugging
const int ledPin = 13;      // the number of the LED pin

long debounceDelay = 100;
long lastDebounceTime = 0;
int buttonState;
int lastButtonState = HIGH;



/*********************************************************/
void setup() {
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  // Input pullup is used when the button is connected to ground, like this project is meant to be.
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  lcd.clear();
  Serial.begin(9600);
}
/*********************************************************/
void loop()  {
  handleButton();
  handleSerialCommunication();
  if (backlightState) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
}


void handleButton() {
  int buttonReading = digitalRead(buttonPin);
  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }
  // Only do the thing if we've seen the state change for long enough
  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (buttonReading != buttonState) {
      buttonState = buttonReading;

      // Toggle the backlight if trhe button is low.
      if (buttonState == LOW) {
        toggleBacklight();
      }
    }
  }
  lastButtonState = buttonReading;
}

void toggleBacklight() {
  if (backlightState) {
    lcd.noBacklight();
    backlightState = false;
  } else {
    lcd.backlight();
    backlightState = true;
  }
}

void handleSerialCommunication() {
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
}
