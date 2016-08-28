#include "Arduino.h"
#include "ComVector.h"
#include "com.h"
#include "ComQueue.h"
#include "global.h"

#define LED_PIN 13
ComVector* com::GetVec()
{
	return &_ArrVec[0];

}
void com::clean()
{
	_ArrVec[0].clean_arr();
	_ArrVec[1].clean_arr();
}
void com::MultiRead(uint8_t n)
{
	bool same;
	char VerfStat=0;
	Serial.println(UI_Manager.event());
	while(VerfStat!=1 && !UI_Manager.event())
	{
	  Serial.println("loop");
	  if(_ArrVec[VerfStat!=0].receive())
	  { 
		same=_ArrVec[0].compare(_ArrVec[1]);
		if (same|(!VerfStat)) 
		{
		  VerfStat = ((!VerfStat) ? n : (VerfStat-1));//if status=0->5 else status--
		}
		else//if not stat 0 or not tottaly equals
		{
		  _ArrVec[0].copy(_ArrVec[1]);
		  VerfStat=0;
		}
	  } 
	  else//if the new arr is bad
	  {
		_ArrVec[VerfStat!=0].clean_arr();// clean it
	  }
	_ArrVec[1].clean_arr();//clean the compare arr
	}
	if(UI_Manager.event())
	{
		Serial.println("noticed flag inside");
		clean();
	}
}
void com::transmit(uint8_t loc)
{
	_ArrVec[0].readEE(loc);
	_ArrVec[0].transmit();
	Serial.println(F("Transmited"));
	_ArrVec[0].printVec();
	clean();
}
void com::Cinterupt(void)
{
	interupt=!interupt;
}
boolean com::status(void)
{
	return !interupt;
}