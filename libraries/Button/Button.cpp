#include "Button.h"
#include "Arduino.h"
#include "global.h"
#define DelayTime 0
#define PHASE_A_PIN 8//red
#define PHASE_B_PIN 9//green
#define PUSH_PIN 2//blue
Button::Button()
{
	loc=0;
	LastClick=0;
	LastStateA=false;
	
}
void Button::UpdateLoc(void)
{
		bool temp = digitalRead(PHASE_B_PIN);
		if(temp==LOW)
		{
			UI_Manager.Right();
		}
		else
		{
			UI_Manager.Left();
		}

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
		if(millis()-LastClick>900)
		{
			UI_Manager.CLong(true);
		}
		else if(millis()-LastClick>50)
		{
			UI_Manager.CShort(true);
		}
	}

}