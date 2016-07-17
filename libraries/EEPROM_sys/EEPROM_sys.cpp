#include "Arduino.h"
#include "EEPROM_sys.h"
#define MAX_DATA_LENGTH 203
#define max_vec_len 195
#define buf_len 15
EEPROM_sys::EEPROM_sys(void)
{
	size=EEPROM.length();
	last_idx=EEPROM.read(0);
}

int EEPROM_sys::read_len(int *vec, char idx) 
{
	int offset,i,*p;
	int t_tran_len;
	uint8_t temp;
	offset = calc_offset(idx);
	offset = offset + buf_len*sizeof(char);
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
	Serial.println("reading name");
	int i;
	int t_str_len;
	int offset = calc_offset(idx);
	static char buffer1[buf_len];
	for(int i=0;i<buf_len;i++)
	{
	  buffer1[i]=EEPROM.read(offset);
	  offset = offset +sizeof(char);
	}
	String ret(buffer1);
	Serial.println(ret);
	return(ret);
	
}
void EEPROM_sys::writeName(String name,int offset0)
{
	String Str_name = name;
	static char buffer[buf_len];
	Str_name.toCharArray(buffer,buf_len);
	int offset = offset0;
	Serial.println("name:");
	for(int i=0;i<buf_len;i++)
	{
	  EEPROM.write(offset,(uint8_t)buffer[i]);
	  Serial.println((uint8_t)buffer[i]);
	  offset = offset +sizeof(char);
	}
	Serial.println("ename:");
}
bool EEPROM_sys::write(int *vec, char idx,int len,String name)//vi 
{
	Serial.print("writing in idx: ");
	Serial.println((uint8_t)idx);
	int offset,i;
	int* p=vec;
	Serial.print("len: ");
	Serial.println(len);
	Serial.print("maxlen: ");
	Serial.println(max_vec_len);
	if (len>max_vec_len) return(false);//checking
	offset = IsFit(len,idx);//calc offset
	Serial.print("offset: ");
	Serial.println(offset);
	if (offset<0) return(false);//checking
	else
	{
		
		writeName(name,offset);
		offset=offset+buf_len*sizeof(char);
		EEPROM.put(offset,len);
		offset = offset +sizeof(int);
		Serial.println("the vec");
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
bool EEPROM_sys::writeL(int *vec ,int len,String name)
{
	Serial.print("last idx");
	Serial.println((uint8_t)last_idx);
	if(write(vec,last_idx,len,name))
	{
		EEPROM.write(0,(uint8_t)last_idx+1);
		last_idx++;
		return(true);
	}
	Serial.println("didnt write");
	return(false);
}

int EEPROM_sys::IsFit(int len,char idx) 
{
	int start_loc=calc_offset(idx);
	if (start_loc + sizeof(int) + (len+buf_len)*sizeof(char) <= size) 
	{
		return(start_loc);
	}	
	
	else return(-1); //no space for this table
}

int EEPROM_sys::calc_offset(char idx)
{
	int start_loc = 1;
	int t_str_len;
	int t_tran_len;
	for(int i=0;i<(uint8_t)idx;i++)
	{
		start_loc = start_loc+buf_len*sizeof(char);
		EEPROM.get(start_loc,t_tran_len);
		start_loc = start_loc + sizeof(int) + t_tran_len*sizeof(char);
	}
	Serial.print("start_loc: ");
	Serial.println(start_loc);
	return start_loc;
}
char EEPROM_sys::LastIdx()
{
	return(last_idx);
}

void EEPROM_sys::clear()
{
	for(int i=0; i<EEPROM.length();i++)
	{
		EEPROM.write(i,0);
	}
}

String* EEPROM_sys::GetNames()
{
	Serial.println("in get names");
	String* p = new String[last_idx];
	for(uint8_t i=0;i<(uint8_t)last_idx;i++)
	{
		p[i]=read_name(char(i));
		Serial.println(read_name(char(i)));
	}
	return p;
}

