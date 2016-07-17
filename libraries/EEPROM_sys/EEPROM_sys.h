#ifndef EEPROM_sys_h
#define EEPROM_sys_h

#include "Arduino.h"
#include <EEPROM.h>
#include "ComVector.h"

class EEPROM_sys
{
	public:
		EEPROM_sys(void);
		int read_len(int *vec, char idx) ;
		void clear();
		String read_name(char idx);
		bool writeL(int *vec ,int len,String name);
		char LastIdx(void);
		String* GetNames(void);
		
	private:
		int size;
		int IsFit(int len,char idx);
		int calc_offset(char idx);
		void writeName(String name,int offset0);
		bool write(int *vec, char idx,int len,String name);
		char last_idx;
		
};

#endif