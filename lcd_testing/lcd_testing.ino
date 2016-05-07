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
#include <LcdString.h>
#include <global.h>
#include "Menu.h"

#define PHASE_A_PIN 2
#define PHASE_B_PIN 7
#define PUSH_PIN 3
LiquidCrystal lcd(12, 11, 5, 6, 3, 2);
void setup() {
  // set up the LCD's number of columns and rows:
  
  // Print a message to the LCD.
  //lcd.print("->");
   Serial.begin(9600);
  lcd.begin(16, 2);
  

  
}

void loop() 
{
  String arrr[3]={"transmition1","transmition2","transmition3"};
  Menu bla(arrr,"Transmit");
 bla.show();
 delay(5000);
 bla.right();
 bla.show();
 delay(5000);
 bla.right();
 bla.show();
  //LcdString a(1,0,"<");
  //a.Display();
  //LcdString b(1,15,">");
  //b.Display();
  while(1);


  // print the number of seconds since reset:
 // lcd.print(millis() / 1000);
}

