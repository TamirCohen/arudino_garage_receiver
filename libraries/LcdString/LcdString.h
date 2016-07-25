#include "Arduino.h"

#ifndef LcdString_h
#define LcdString_h
#include <LiquidCrystal.h>

class LcdString
{
	public:
		LcdString(int row,int column,String text);
		LcdString();
		void Display(void);
		String GetText();
		void SetText(String text);
		void SetRow(int row);
		void SetColumn(int col);
		void reserve(uint8_t);
	private:
		int Column;
		int Row;
		String Text;
};
#endif