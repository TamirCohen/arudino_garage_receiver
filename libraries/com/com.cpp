#include "Arduino.h"
#include "ComVector.h"
#include "com.h"

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
void com::MultiRead()
{
	bool same;
	char VerfStat=0;
	while(VerfStat!=1)
	{
	  if(_ArrVec[VerfStat!=0].receive())
	  {
		same=_ArrVec[0].compare(_ArrVec[1]);      
		if (same|(!VerfStat)) 
		{
		  VerfStat = ((!VerfStat) ? 5 : (VerfStat-1));//if status=0->5 else status--
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
}
void com::transmit(uint8_t loc)
{
	Serial.println(F("loc: "));
	Serial.println(loc);
	_ArrVec[0].readEE(loc);
	_ArrVec[0].transmit();
	Serial.println(F("Transmited"));
	_ArrVec[0].printVec();//to del
	clean();
}