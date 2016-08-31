#include "ComQueue.h"
#include "arduino.h"
#include "global.h"
#define N 195
void ComQueue::insert(uint8_t n)
{
	_vector[(_length+first)%N] = n;
	if(_length==N)
	{
		first++;
	}
	else
	{
		_length++;
	}
}
void ComQueue::empty()
{
	_length=0;
}
void ComQueue::printVec()
{
	int j;
	for(j=first;j<first+_length;j++)
	{
		Serial.println(_vector[j%N]*4);
	}
}
boolean ComQueue::fill()
{
	char c;
	bool state = 0;
	int c_nc = 0;//not correct
	int c_c = 0;
	bool mode_count = false;
	while (!UI_Manager.event())
	{
	  c=read_bit();//read high/low - 1/0
	  if(!(c==state))//if Read isnt state
	  {
		c_nc++;
		if(c_nc == 5)//if 5 in a row
		{
			if(c_c+c_nc>255*4)//we have just 8 bits
			{
				insert(255);
				if(!state)
				{
					return true;
				}
			}
			else if((c_c+c_nc)/4<3)
			{
				empty();
				Serial.println("drop");
				//Serial.println(c_c+c_nc);
			}
			else
			{
				insert((uint8_t)((c_c+c_nc)/4));
			}
			state=!state;//change state
			c_c=0;
			c_nc=0;
		}
	  }
	  else
	  {
		c_c++;//add to correct
		c_c+=c_nc;//add c_nc to c_c
		c_nc=0;
	  }
	}
	return false;

}