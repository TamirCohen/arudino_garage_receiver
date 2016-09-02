#include "Arduino.h"
#include "ComVector.h"
#include "com.h"
#include "ComQueue.h"
#include "global.h"

#define LED_PIN 13
ComQueue* com::GetVec()
{
	return Base;

}
void com::clean()
{
	_ArrVec[0].clean_arr();
	_ArrVec[1].clean_arr();
}
void com::MultiRead(uint8_t n)
{
	Serial.println(F("in multyread"));
	Serial.println(n);
	bool same;
	uint8_t VerfStat=0;
	ComQueue * CompareVec = &(_ArrVec[0]);//zero loc
	ComQueue * BaseVec = &(_ArrVec[1]);//first loc
	ComQueue * tmp;
	//Serial.println(UI_Manager.event());
	while(VerfStat!=1)//VerfStat!=1 && !UI_Manager.event()!!!important
	{
	  CompareVec->fill();
	  //CompareVec->printVec();
	  if(VerfStat!=0)
	  {
		same=BaseVec->compare(CompareVec);
		if(!same)
		{
			tmp = CompareVec;
			CompareVec = BaseVec;//switch between vectors
			BaseVec = tmp;
			CompareVec->empty();
			VerfStat = n;
		}
		else
		{
			CompareVec->empty();
			VerfStat = VerfStat-1;
		}
	  }
	  else
	  {
		tmp = CompareVec;
		CompareVec = BaseVec;//switch between vectors
		BaseVec = tmp;
		CompareVec->empty();
		VerfStat = n;

		  
	  } 

	}
	/*if(UI_Manager.event())
	{
		Serial.println(F("noticed flag inside"));
		clean();
	}superrr important!!*/
	Base = BaseVec;
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