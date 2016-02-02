#include <EEPROM.h>
#include <EEPROM_sys.h>
#include <ComVector.h>
#include <com.h>
#include <global.h>

#define RCV_PIN 3
#define LED_PIN 13
#define SCOPE_PIN 5
#define TRAN_PIN 4
EEPROM_sys EE_manager;
void setup()
{
  Serial.begin(9600);//configuration
  pinMode(RCV_PIN,INPUT);//data from reciver
  pinMode(SCOPE_PIN,OUTPUT);//for debugging-scope
  pinMode(LED_PIN,OUTPUT);//led receving
  pinMode(TRAN_PIN,OUTPUT);//transmition pin
}


void loop()
{
 // com m;
  //m.MultiRead();
  //ComVector* a = m.GetVec();
 ComVector a(200);
  //a->writeEE(0);
  a.readEE(0);
  while(1);
  
}

