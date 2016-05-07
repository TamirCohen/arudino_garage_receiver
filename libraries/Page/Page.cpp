#include "Arduino.h"
#include "Page.h"
#include "LcdString.h"
#include <global.h>
#define max_Str 10
Page::Page(LcdString* arr)
{
	for (int j=0;j<sizeof(arr);j++)
	{
		Serial.println(arr[j].GetText());
	}
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
	for(i=0;i<10;i++)
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