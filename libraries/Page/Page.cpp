#include "Arduino.h"
#include "Page.h"
#include "LcdString.h"
#include <global.h>
#define max_Str 3
#define led_length 16
#define text_loc 0
#define arrow_left_loc 1
#define arrow_right_loc 2
#define max_len 14
Page::Page(LcdString* arr)
{
	if(sizeof(arr)<max_Str+1)
	{
		int i;
		for(i=0;i<sizeof(arr);i++)
		{
			lcd_array[i]=arr[i];
		}
	}
}
Page::Page()
{
	for(int i=0;i<max_Str;i++)
	{
		lcd_array[i]=LcdString();
	}
}
void Page::show()
{
	int i;
	for(i=0;i<max_Str;i++)
	{
		if(lcd_array[i].GetText()!="")//check it later
		{
			lcd_array[i].Display();
		}
	}
	
}
void Page::clear()
{
	lcd.clear();
}
int Page::mid_pos(String SingleStr)
{
	return((led_length-SingleStr.length())/2);
}
boolean Page::IsFocus()
{
	return focus;
}