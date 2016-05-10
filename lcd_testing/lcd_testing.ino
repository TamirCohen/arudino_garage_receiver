/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include "TransmitMenu.h"
#include <LcdString.h>
#include <global.h>
#include "Menu.h"

#define PHASE_A_PIN 2
#define PHASE_B_PIN 7
#define PUSH_PIN 3
LiquidCrystal lcd(12, 11, 5, 6, 3, 2);
ComVector Com_manager(200);
EEPROM_sys EE_manager;
void setup() {
  // set up the LCD's number of columns and rows:
  
  
  // Print a message to the LCD.
  //lcd.print("->");
   Serial.begin(9600);
  lcd.begin(16, 2);
  

  
}

void loop() 
{
String Temparr[5]={"transmition1","transmition2","transmition3","transmition4","transmition5"};
TransmitMenu TransMenu(Temparr,sizeof(Temparr)/sizeof(String),0);
TransMenu.show();
delay(5000);
TransMenu.right();
TransMenu.show();
delay(5000);
TransMenu.right();
TransMenu.show();
delay(5000);
TransMenu.right();
TransMenu.show();
TransMenu.click();
while(1);


  // print the number of seconds since reset:
 // lcd.print(millis() / 1000);
}

