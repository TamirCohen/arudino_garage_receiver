#ifndef EEPROM_sys_h
#define EEPROM_sys_h

#include "Arduino.h"
#include <EEPROM.h>
#include "ComVector.h"

class EEPROM_sys
{
	public:
		EEPROM_sys(void);
		bool write(int *vec, char idx,int len,String name) ;
		int read_len(int *vec, char idx) ;
		void clear();
		String read_name(char idx);
	private:
		int size;
		int IsFit(int len,char idx,String name);
		int calc_offset(char idx);
		
};

#endif