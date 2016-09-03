#include "Arduino.h"
#include "EEPROM_sys.h"
#define MAX_DATA_LENGTH 203
#define max_vec_len 190
#define buf_len 15
EEPROM_sys::EEPROM_sys(void)
{
	size=EEPROM.length();
	last_idx=EEPROM.read(0);
}

int EEPROM_sys::read_len(uint8_t *vec, char idx) 
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
		vec[i]=temp;
		//Serial.println(vec[i]);
		offset = offset +sizeof(char);
			
	}
	return(t_tran_len);
}
void EEPROM_sys::read_all()
{
	uint8_t temp;
	int offset=0;
	for (int j=0;j<size;j++)
	{
		EEPROM.get(offset,temp);
		Serial.println(temp);
		offset = offset + sizeof(char);
	}
}
String EEPROM_sys::read_name(char idx)
{
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
	//Serial.println(ret);
	return(ret);
	
}
void EEPROM_sys::writeName(String name,int offset0)
{
	String Str_name = name;
	static char buffer[buf_len];
	Str_name.toCharArray(buffer,buf_len);
	int offset = offset0;
	for(int i=0;i<buf_len;i++)
	{
	  EEPROM.write(offset,(uint8_t)buffer[i]);
	  offset = offset +sizeof(char);
	}
}
bool EEPROM_sys::write(uint8_t *vec, char idx,int len,String name,int first)//vi 
{
	int offset,i;
	uint8_t* p=vec;
	if (len>max_vec_len) return(false);//checking
	offset = IsFit(len,idx);//calc offset
	if (offset<0) return(false);//checking
	else
	{
		
		writeName(name,offset);
		offset=offset+buf_len*sizeof(char);
		EEPROM.put(offset,len);
		offset = offset +sizeof(int);
		Serial.println("writeEE");
		for(i=0;i<len;i++)
		{
			EEPROM.put(offset,p[(i+first)%max_vec_len]);
			offset = offset +sizeof(char);
		}
		return(true);		
	}
}
bool EEPROM_sys::writeL(uint8_t *vec ,int len,String name,int first)
{
	if(write(vec,last_idx,len,name,first))
	{
		EEPROM.write(0,(uint8_t)last_idx+1);
		last_idx++;
		return(true);
	}
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
	last_idx=0;
}

String* EEPROM_sys::GetNames()
{
	String* p = new String[last_idx];
	for(uint8_t i=0;i<(uint8_t)last_idx;i++)
	{
		p[i]=read_name(char(i));
	}
	return p;
}
void EEPROM_sys::Delete(char idx)
{
	if(last_idx>0)
	{
		//Serial.print(F("idx"));
		//Serial.println((uint8_t)idx);
		uint8_t temp;
		int offset = calc_offset(idx);
		//Serial.print(F("offset: "));
		//Serial.println(offset);
		int last = calc_offset(idx+1);
	//	Serial.print(F("last: "));
	//	Serial.println(last);
		int last_bit = calc_offset(last_idx);
		int i;
	//	Serial.println(last_idx);
		for(i=offset;i<last;i++)
		{
			EEPROM.write(i,0);
		}
		Serial.print(F("super last"));
		Serial.println(last_bit);
		for(i=last;i<last_bit;i++)
		{
			EEPROM.get(i,temp);
			//Serial.println(temp);
			EEPROM.write(i+offset-last,temp);
			EEPROM.write(i,0);
		}
		EEPROM.write(0,(uint8_t)last_idx-1);
		last_idx--;
	}
}

