
#include <EEPROM.h>
#include <EEPROM_sys.h>
#include <ComVector.h>
#include <com.h>
#include <UIManager.h>
#include <Button.h>
#include <LiquidCrystal.h>
#include <LcdString.h>
#include <global.h>
#include <Menu.h>
#include <arduino.h>
#include <NamePage.h>//to del

#define RCV_PIN 10
#define LED_PIN 13
#define SCOPE_PIN 5
#define TRAN_PIN 9//change
#define PHASE_A_PIN 7//red
#define PHASE_B_PIN 8//green
#define PUSH_PIN 3//blue
LiquidCrystal lcd(12, 11, 5, 6, 4, 2); 
EEPROM_sys EE_manager;
Button Button_manager;
UIManager UI_Manager;
void DoClick()
{
  Button_manager.Click();
}
void setup()
{
  Serial.begin(9600);//configuration
  Serial.println(F("begin trans"));
  lcd.begin(16, 2);
  pinMode(RCV_PIN,INPUT);//data from reciver
  pinMode(SCOPE_PIN,OUTPUT);//for debugging-scope
  //pinMode(LED_PIN,OUTPUT);//led receving
  pinMode(TRAN_PIN,OUTPUT);//transmition pin
  pinMode(PHASE_A_PIN,INPUT_PULLUP);
  pinMode(PHASE_B_PIN,INPUT_PULLUP);
  pinMode(PUSH_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PUSH_PIN),DoClick, CHANGE);
  UI_Manager.Start();
}


void loop()
{ 
 
//EE_manager.clear();
//Serial.println(F("finshed"));
//while(1);
// com m;
// m.MultiRead();
// ComVector* a = m.GetVec();
// a->setName("yosef");
// a->printVec();
// a->writeEE();
// Serial.println("----break----");
// ComVector b(195,"Tran0");
//  b.readEE(2);
//  b.printVec();
//  Serial.println(b.GetName());

//Serial.println(a->GetLength());
 Button_manager.CheckLoc();
 
 
}


