#include "EEPROM.h"
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("start");
int len=15;
String Str_name="tamir";
static char buffer[15];
Str_name.toCharArray(buffer,15);
int offset=sizeof(int);
for(int i=0;i<15;i++)
{
  EEPROM.write(offset,(uint8_t)buffer[i]);
  Serial.println((uint8_t)buffer[i]);
  offset = offset +sizeof(char);
}

offset=sizeof(int);
static char buffer1[15];
for(int i=0;i<15;i++)
{
  buffer1[i]=EEPROM.read(offset);
  Serial.println((uint8_t)buffer1[i]);
  offset = offset +sizeof(char);
}
String ret(buffer1);
Serial.println(ret);
while(1);
}
