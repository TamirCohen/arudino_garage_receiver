#include "Arduino.h"
#include "EEPROM_sys.h"

EEPROM_sys::EEPROM_sys(void)
{
	size=EEPROM.length();
}

bool EEPROM_sys::read(ComVector &vec, char idx) 
{
	int offset,i,*p,len;
	
	len=vec.GetLength();
	p=vec.GetVec();
	
	offset = calc_offset(len,idx);
	if (offset<0) return(false);
	else
	{
		for(i=0;i<len;i++)
		{
			EEPROM.get(offset+i*sizeof(int),p[i]);
		}			

		return(true);
	}
}

bool EEPROM_sys::write(ComVector &vec, char idx) 
{
	int offset,i,*p,len;
	
	len=vec.GetLength();
	p=vec.GetVec();
	
	offset = calc_offset(len,idx);
	if (offset<0) return(false);
	else
	{
		for(i=0;i<len;i++) EEPROM.put(offset+i*sizeof(int),p[i]);
		return(true);
	}
}


int EEPROM_sys::calc_offset(int len, char idx) 
{
	if (((idx+1)*len*sizeof(int)) <= size) 
	{
		return(idx*len*sizeof(int));
	}	
	
	else return(-1); //no space for this table
}

