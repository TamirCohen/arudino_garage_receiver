#include "Arduino.h"
#include "ComVector.h"
#include "EEPROM_sys.h"
#include <global.h>

#define DEMO_ARRAY_LEN 30
#define N 200
#define ZeroNum 1000
#define RCV_PIN 3
#define DEBUG false
#define Tran_Factor 13.7 
#define Tran_Num 4
#define TRAN_PIN 4


ComVector::ComVector(void)
{
_length=0;
clean_arr();
}

ComVector::ComVector(int n)
{
  _length=n;
  int i;
  for(i=0;i<n;i++)
  {
	  _vector[i]=0;
  }
}
int ComVector::GetLength()
{
return _length;
}
char ComVector::read_bit(void)
{
static int demo[DEMO_ARRAY_LEN]={1500,70,30,70,30,70,30,70,30,70,1500,10,1500,70,30,70,30,70,30,70,30,70,1500,10,1500,40,50,40,1500,10};
static char idx=0;
static int idx_internal=demo[0];
static bool state=false;

if (!DEBUG) 
  return(digitalRead(RCV_PIN));
else 
{
  if (idx_internal==0)
  {
	idx++;
	idx=idx % DEMO_ARRAY_LEN;
	idx_internal=demo[idx];
	state=!state;
  }
  else
	idx_internal--;
  return(state);
}
}

boolean ComVector::zeroes(bool state,int c_c)
{
if ((!state) & (c_c>ZeroNum))//state 0 and lots of 0
{
  return(true);
}
else
{
  return(false);
}
}
boolean ComVector::Tcorrect(void)
{
int p;
for(p=0;p<N;p++)
{
  if(_vector[p] == 0)
  {
	return(true);
  }
  if(_vector[p]<10)
  {
	return(false);
  }
}
}
boolean ComVector::compare(ComVector &c2)
{
int p;
int equal=0;
if (_length!=c2._length) return(false);
for (p=0;p<_length;p++)
{
  if (abs(_vector[p]-c2._vector[p])<10) equal++;
}
if(equal < _length)
{return false;}
else
{return true;}

}
void ComVector::copy(ComVector &c2)
{
_length=c2._length;
int p;
for(p=0;p<N;p++)
{
  _vector[p]=c2._vector[p];
}
}


void ComVector::clean_arr(void)
{
int p;
for(p=0;p<N;p++)
{
_vector[p]=0;
}
_length=0;
}

void ComVector::printVec(void)
{
	int i;
	for(int i=0;i<_length;i++)
	{
		Serial.println(_vector[i]);
	}
}

boolean ComVector::receive(void)
{
int j = 0;
char c;
bool state = 0;
int c_nc = 0;//not correct
int c_c = 0;
bool mode_count = false;
while (j<N)
{
  c=read_bit();//read high/low - 1/0
  if(!(c==state))//if Read isnt state
  {
	c_nc++;
	if(c_nc == 5)//if 5 in a row
	{
	  _vector[j] = c_c+c_nc;//write # (numbers)
	  if (mode_count) //if in transmition
	  {
		j++;//byte num in transmition
		if(zeroes(state,c_c))//if stopped tansmition
		{
		  break;
		}
	  }
	  else
	  {
		mode_count = zeroes(state,c_c);//check new transmition?
		if (mode_count) j++;//if in transmition count byte        
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
_length = j;
return(Tcorrect());
}

void ComVector::writeEE(char idx)
{
	EE_manager.write(_vector,idx,_length);
}

void ComVector::readEE(char idx)
{
	_length = EE_manager.read(_vector,idx);
}

void ComVector::transmit(void)
{
	int i,j;
	for(i=0;i<Tran_Num;i++)
	{
		for(j=0;j<_length;j++)
		{
			if(j%2==1)
			{
				digitalWrite(TRAN_PIN,HIGH);
				delayMicroseconds(_vector[j]*Tran_Factor);
			}
			else
			{
				digitalWrite(TRAN_PIN,LOW);
				delayMicroseconds(_vector[j]*Tran_Factor);
			}
		}
	}
}