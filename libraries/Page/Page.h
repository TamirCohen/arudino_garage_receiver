#include "Arduino.h"
#include "LcdString.h"
#ifndef Page_h
#define Page_h
#define max_Str 3

class Page
{
	public:
		virtual void show();
		Page(LcdString* arr);
		void clear();
		Page();
		boolean IsFocus();
		//virtual void click();
	protected:
		LcdString lcd_array[max_Str];
		int mid_pos(String SingleStr);
		boolean focus;
		
};
#endif