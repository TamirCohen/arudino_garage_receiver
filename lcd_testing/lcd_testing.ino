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
#include <UIManager.h>
#include <Button.h>
#include <LiquidCrystal.h>
#include <LcdString.h>
#include <global.h>
#include <Menu.h>

#define PHASE_A_PIN 2
#define PHASE_B_PIN 7
#define PUSH_PIN 3
LiquidCrystal lcd(12, 11, 5, 6, 4, 2);
Button Button_manager; 
void setup() {
  // set up the LCD's number of columns and rows:
  
  // Print a message to the LCD.
  //lcd.print("->");
   Serial.begin(9600);
  lcd.begin(16, 2);
  

  
}

void loop() 
{
  UIManager Manage;
  Manage=UIManager();
  delay(2500);
  Manage.Right();
  
//    String arrr[4]={"transmition1","transmition2","shalom3","tran4"};
//    Menu TransMenu(arrr,4,0,"");
//    String arr[3] ={"abcd","gfdgdfh","bambada"};
//    Menu SetMenu(arr,3,1,"Settings");
//    TransMenu.Cfocus();
//  
//SetMenu.show();
// TransMenu.show();
// 
// delay(2500);
// SetMenu.right();
// TransMenu.show();
// SetMenu.show();
// delay(2500);
// SetMenu.Cfocus();
// SetMenu.show();
// TransMenu.show();
// delay(2500);
// SetMenu.right();
// SetMenu.show();
// TransMenu.right();
// TransMenu.show();
  while(1);


  // print the number of seconds since reset:
 // lcd.print(millis() / 1000);
}

