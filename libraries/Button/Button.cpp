#include "Button.h"
#include "Arduino.h"
#define PHASE_A_PIN 2
#define PHASE_B_PIN 7
#define PUSH_PIN 3
#define DelayTime 0
Button::Button()
{
	loc=0;
	Last_update=0;
	LastStateA=false;
	
}
void Button::UpdateLoc(void)
{
		bool temp = digitalRead(PHASE_B_PIN);
		if(temp==LOW)
		{
			loc--;
		}
		else
		{
			loc++;
		}
		Serial.println(loc);

}
void Button::CheckLoc()
{
  static bool temp;
  temp =digitalRead(PHASE_A_PIN);
  if ((LastStateA == LOW) && (temp == HIGH)) 
  {
    UpdateLoc();
    delay(3);
  } 
  LastStateA = temp;
}

int Button::GetLoc(void)
{
	return loc;
}
void Button::Click(void)
{
	if(digitalRead(PUSH_PIN)==LOW)
	{
		LastClick = millis();
	}
	else
	{
		if(millis()-LastClick>1000)
		{
			Serial.println("LongClick");
		}
		else if(millis()-LastClick>3)
		{
			Serial.println("ShortClick");
		}
	}
	
}