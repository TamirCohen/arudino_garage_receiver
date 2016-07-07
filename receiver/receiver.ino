
#include <EEPROM.h>
#include <EEPROM_sys.h>
#include <ComVector.h>
#include <com.h>
#include <global.h>
#include <Button.h>
#include <Menu.h>
#include <LiquidCrystal.h>

#define RCV_PIN 6
#define LED_PIN 13
#define SCOPE_PIN 5
#define TRAN_PIN 4//change
#define PHASE_A_PIN 7//red
#define PHASE_B_PIN 8//green
#define PUSH_PIN 4//blue 
EEPROM_sys EE_manager;
Button Button_manager; 
LiquidCrystal lcd(12, 11, 5, 6, 3, 2);
String Temparr[5]={"transmition1","transmition2","transmition3","transmition4","transmition5"};
Menu TransMenu(Temparr,"Transmit");
void DoClick()
{
  Button_manager.Click();
}
void setup()
{
  Serial.begin(9600);//configuration
  lcd.begin(16, 2);
  TransMenu.show();
  pinMode(RCV_PIN,INPUT);//data from reciver
  pinMode(SCOPE_PIN,OUTPUT);//for debugging-scope
  pinMode(LED_PIN,OUTPUT);//led receving
  pinMode(TRAN_PIN,OUTPUT);//transmition pin
  pinMode(PHASE_A_PIN,INPUT_PULLUP);
  pinMode(PHASE_B_PIN,INPUT_PULLUP);
  pinMode(PUSH_PIN,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PUSH_PIN),DoClick, CHANGE);
  
}


void loop()
{
 // com m;
 // m.MultiRead();
 //ComVector* a = m.GetVec();
 //ComVector a(200);
 //a->writeEE(0);
 // a->readEE(0);
 //a->printVec();
 //Serial.println(Button_manager.GetLoc());
 Button_manager.CheckLoc();
 TransMenu.show();
 while(1);
}


