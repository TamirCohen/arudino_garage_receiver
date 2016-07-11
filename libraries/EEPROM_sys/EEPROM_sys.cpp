#include "Arduino.h"
#include "EEPROM_sys.h"
#define MAX_DATA_LENGTH 203
#define max_vec_len 195

EEPROM_sys::EEPROM_sys(void)
{
	size=EEPROM.length();
}

int EEPROM_sys::read_len(int *vec, char idx) 
{
	int offset,i,*p;
	int t_str_len;
	int t_tran_len;
	uint8_t temp;
	offset = calc_offset(idx);
	EEPROM.get(offset,t_str_len);
	offset = offset + sizeof(int) + t_str_len*sizeof(char);
	EEPROM.get(offset,t_tran_len);
	offset = offset + sizeof(int);
	for(i=0;i<t_tran_len;i++)
	{
		EEPROM.get(offset,temp);
		vec[i]=((int)temp)*4;
		offset = offset + sizeof(char);
	}
	return(t_tran_len);
		
}

String EEPROM_sys::read_name(char idx)
{
	int i;
	int t_str_len;
	char *buffer;
	int offset = calc_offset(idx);
	EEPROM.get(offset,t_str_len);
	offset = offset +sizeof(int);
	for(i=0;i<t_str_len;i++)
	{
		EEPROM.get(offset,buffer[i]);
		offset=offset+sizeof(char);
	}
	String ret =buffer;
	return(ret);
}

bool EEPROM_sys::write(int *vec, char idx,int len,String name)//vi 
{
	int offset,i;
	int* p=vec;
	Serial.println("name before:");
	Serial.println(name);
	char buffer[name.length()];
	name.toCharArray(buffer,name.length());
	Serial.print("new str:");
	String tmp1(buffer);
	Serial.println(tmp1);
	if (len>max_vec_len) return(false);//checking
	offset = IsFit(len,idx,name);//calc offset
	if (offset<0) return(false);//checking
	else
	{
		EEPROM.put(offset,name.length());
		offset=offset+sizeof(int);
		
		for(i=0;i<name.length();i++)
		{
			EEPROM.put(offset,buffer[i]);
			offset=offset+sizeof(char);
		}
		
		EEPROM.put(offset,len);
		offset=offset+sizeof(int);
		
		for(i=0;i<len;i++)
		{
			if(vec[i]<255*4)
			{
				EEPROM.put(offset,(char)(p[i]/4));
			}
			else
			{
				EEPROM.put(offset,255);
			}
			offset=offset+sizeof(char);
		}
		return(true);		
	}
}


int EEPROM_sys::IsFit(int len,char idx,String name) 
{
	int start_loc=calc_offset(idx);
	if (start_loc + 2*sizeof(int) + (len+name.length())*sizeof(char) <= size) 
	{
		return(start_loc);
	}	
	
	else return(-1); //no space for this table
}

int EEPROM_sys::calc_offset(char idx)
{
	int start_loc = 0;
	int t_str_len;
	int t_tran_len;
	for(int i=0;i<(uint8_t)idx;i++)
	{
		EEPROM.get(start_loc,t_str_len);
		start_loc = sizeof(int) + t_str_len*sizeof(char);
		EEPROM.get(start_loc,t_tran_len);
		start_loc = sizeof(int) + t_tran_len*sizeof(char);
	}
}

void EEPROM_sys::clear()
{
	for(int i=0; i<EEPROM.length();i++)
	{
		EEPROM.write(i,0);
	}
}

