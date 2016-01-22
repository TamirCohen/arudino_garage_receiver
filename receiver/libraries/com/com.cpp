#include "Arduino.h"
#include "ComVector.h"
#include "com.h"

#define LED_PIN 13
  ComVector* com::GetCode()
  {
	  return &_ArrVec[0];
  }
  void com::MultiRead()
  {
    char VerfStat=0;
    while(VerfStat!=1)
    {

      digitalWrite(LED_PIN,HIGH);
      digitalWrite(LED_PIN,LOW);//finish
      if(_ArrVec[VerfStat!=0].receive())
      {
        bool same=_ArrVec[0].compare(_ArrVec[1]);      
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
