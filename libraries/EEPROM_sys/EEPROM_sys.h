#ifndef EEPROM_sys_h
#define EEPROM_sys_h

#include "Arduino.h"
#include <EEPROM.h>
#include "ComVector.h"

class EEPROM_sys
{
	public:
		EEPROM_sys(void);
		bool write(ComVector &vec, char idx) ;
		bool read(ComVector &vec, char idx) ;
		
	private:
		int size;
		int calc_offset(int len, char idx);
};
#endif