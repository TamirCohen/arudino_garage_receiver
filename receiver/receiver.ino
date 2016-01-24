#include <EEPROM.h>
#include <EEPROM_sys.h>
#include <ComVector.h>
#include <com.h>

  #define RCV_PIN 3
  #define LED_PIN 13
  #define SCOPE_PIN 5

  void setup()
  {
    Serial.begin(9600);//configuration
    pinMode(RCV_PIN,INPUT);//data from reciver
    pinMode(SCOPE_PIN,OUTPUT);//for debugging-scope
    pinMode(LED_PIN,OUTPUT);//led receving
  }


  void loop()
  {
    com m;
    m.MultiRead();
    Serial.println(m.GetCode()->GetLength());
    
    
  }

