#ifndef EEPROM_sys_h
#define EEPROM_sys_h

#include "Arduino.h"
#include <EEPROM.h>
#include "ComVector.h"

class EEPROM_sys
{
	public:
		EEPROM_sys(void);
		int read_len(uint8_t *vec, char idx) ;
		void clear();
		String read_name(char idx);
		bool writeL(uint8_t *vec ,int len,String name);
		char LastIdx(void);
		String* GetNames(void);
		void read_all(void);
		void Delete(char idx);
		
	private:
		int size;
		int IsFit(int len,char idx);
		int calc_offset(char idx);
		void writeName(String name,int offset0);
		bool write(uint8_t *vec, char idx,int len,String name);
		char last_idx;
		
};

#endif