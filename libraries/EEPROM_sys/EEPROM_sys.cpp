#include "Arduino.h"
#include "EEPROM_sys.h"

#define max_vec_len 200

EEPROM_sys::EEPROM_sys(void)
{
	size=EEPROM.length();
}

bool EEPROM_sys::read(ComVector &vec, char idx) 
{
	int offset,i,*p,len;
	
	p=vec.GetVec();
	
	offset = calc_offset(max_vec_len,idx);
	if (offset<0) return(-1);
	else
	{	
		EEPROM.get(offset,len);
		for(i=0;i<max_vec_len;i++)
		{
			EEPROM.get(offset+(i+1)*sizeof(int),p[i]);
		}			

		return(len);
	}
}

bool EEPROM_sys::write(ComVector &vec, char idx) 
{
	int offset,i,*p,len;
	
	len=vec.GetLength();
	if (len>max_vec_len) return(false);
	p=vec.GetVec();
	
	offset = calc_offset(max_vec_len,idx);
	if (offset<0) return(false);
	else
	{
		EEPROM.put(offset+i,len);
		for(i=0;i<len;i++) EEPROM.put(offset+(i+1)*sizeof(int),p[i]);
		return(true);
	}
}


int EEPROM_sys::calc_offset(int len, char idx) 
{
	if (((idx+1)*(len+1)*sizeof(int)) <= size) 
	{
		return(idx*(len+1)*sizeof(int));
	}	
	
	else return(-1); //no space for this table
}

