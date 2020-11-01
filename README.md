# arduino-cpu-display
Displays your current CPU speed on an arduino LCD

![CPU Display In Action](/IMG_20201101_004829.jpg)

## Requirements

- Arduino Uno or Nano (Or another compatible board. I've only tested with Uno and Nano, I cannot guarantee compatibility with anything else)
- Sunfounder I2C LCD1602 (Other displays may work, this is the one I have, I know this one works).
- Perl 5
- CPAN library: Device::SerialPort
- Sunfounder's LCD library http://wiki.sunfounder.cc/images/7/7e/LiquidCrystal_I2C.zip
- Requires a Linux operating system

## Wiring Directions

Connect GND on the display to a GND pin on the arduino
Connect VCC to a 5V pin on the Arduino
Connect SDA to Analog Pin 4
Connect SCL to Analog Pin 5
