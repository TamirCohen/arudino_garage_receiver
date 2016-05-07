#include "Arduino.h"
#include "LcdString.h"
#ifndef Page_h
#define Page_h
#define max_Str 10

class Page
{
	public:
		void show();
		Page(LcdString* arr);
		void clear();
		Page();
		//virtual void click();
	protected:
		LcdString lcd_array[max_Str];
		
};
#endif