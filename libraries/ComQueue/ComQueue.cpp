#include "ComQueue.h"
#include "arduino.h"
#include "global.h"
#define N 190
void ComQueue::insert(uint8_t n)
{
	_vector[(_length+first)%N] = n;
	if(_length==N)
	{
		first = (first+1)%N;
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
	Serial.println("printing vec");
	Serial.print("first: ");
	Serial.println(first);
	Serial.print("last idx: ");
	Serial.println(first+_length);
	int j;
	for(j=first;j<first+_length;j++)
	{
		Serial.println(_vector[j%N]*4);
	}
}
boolean ComQueue::compare(ComQueue *c2)
{
	int p;
	if (_length!=c2->_length) return(false);
	for (p=0;p<_length;p++)
	{
		//Serial.print(abs(_vector[(p+first)%N]));
		//Serial.print("-");
		//Serial.println(c2->_vector[(p+c2->first)%N]);
		if (!(abs(_vector[(p+first)%N]-c2->_vector[(p+c2->first)%N])<4))
		{

			return false;
		}
	}
	return true;

}
boolean ComQueue::fill()
{
	char c;
	bool state = 1;
	int c_nc = 0;//not correct
	int c_c = 0;
	bool started = false;
	while (true)//!UI_Manager.event()!!!!!important
	{
	  c=read_bit();//read high/low - 1/0
	  if(!(c==state))//if Read isnt state
	  {
		c_nc++;
		if(c_nc == 5)//if 5 in a row
		{
			if(started||state)
			{
				if(c_c+c_nc>255*4)//we have just 8 bits
				{
					insert(255);
					if(!state)
					{
						return true;
					}
					if(!started)
					{
						started=true;
					}
				}
				else if((c_c+c_nc)/4<3)
				{
					//Serial.println("emptied");
					empty();
					started=false;
					//Serial.println(c_c+c_nc);
				}
				else
				{
					insert((uint8_t)((c_c+c_nc)/4));
					if(!started)
					{started=true;}
				}
				c_c=0;
			}
			else
			{
				c_c=5;
			}
			c_nc=0;
			state=!state;

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
boolean ComQueue::filltest()
{
	uint8_t i;
	for(i=0;i<20;i++)
	{
		insert(i);
	}
	return true;
}
void ComQueue::writeEE()
{
	EE_manager.writeL(_vector,_length,name,first);
}