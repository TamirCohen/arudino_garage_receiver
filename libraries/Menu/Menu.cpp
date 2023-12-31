#include "Arduino.h"
#include "Menu.h"
#include "LcdString.h"
#define led_length 16
#define text_loc 0
#define arrow_left_loc 1
#define arrow_right_loc 2
#define max_len 14
#define max_length_menu 10
Menu::Menu(String arr[],int size,int Row,String Message):Page()
{
	row=Row;
	message=Message;
	arr_len=size;
	uint8_t j;
	for(j=0;j<arr_len;j++)
	{
		str_array[j]=arr[j];
	}
	str_loc=0;
	
	lcd_array[text_loc].reserve(max_len);
	lcd_array[arrow_left_loc].reserve(1);//reserve memory
	lcd_array[arrow_right_loc].reserve(1);
	
	lcd_array[arrow_left_loc].SetText(F("<"));
	lcd_array[arrow_left_loc].SetRow(row);
	lcd_array[arrow_left_loc].SetColumn(0);
	lcd_array[arrow_right_loc].SetText(F(">"));
	lcd_array[arrow_right_loc].SetRow(row);
	lcd_array[arrow_right_loc].SetColumn(15);
	lcd_array[text_loc].SetRow(row);
	update_menu(0);
	focus=true;
	
}
void Menu::right()
{
	if(focus)
	{
		update_menu(1);
	}
}
void Menu::left()
{
	if(focus)
	{
		update_menu(-1);
	}
}
void Menu::update_menu(int move)
{
	clear();
	if(str_loc+move<arr_len&&str_loc+move>-1)
	{
		str_loc = str_loc+move;
		lcd_array[arrow_left_loc].SetText(F("<"));
		lcd_array[arrow_right_loc].SetText(F(">"));
		if(str_loc==0)
		{
			lcd_array[arrow_left_loc].SetText(F(""));
			if(arr_len==0||arr_len==1)
			{
				lcd_array[arrow_right_loc].SetText(F(""));
			}
		}
		else if(str_loc==arr_len-1)
		{
			lcd_array[arrow_right_loc].SetText(F(""));
		}
		lcd_array[text_loc].SetText(str_array[str_loc]);
		lcd_array[text_loc].SetColumn(mid_pos(str_array[str_loc]));

	}
}
void Menu::Cfocus()
{
	clear();
	focus=!focus;

	if(focus)
	{
		update_menu(0);
	}
	else if(row==1)
	{
		lcd_array[text_loc].SetText(message);
		lcd_array[text_loc].SetColumn(mid_pos(message));
		lcd_array[arrow_left_loc].SetText(F(""));
		lcd_array[arrow_right_loc].SetText(F(""));
	}
	else
	{
		lcd_array[arrow_left_loc].SetText(F(""));
		lcd_array[arrow_right_loc].SetText(F(""));
		lcd_array[text_loc].SetText(str_array[str_loc]);
	}
}
int Menu::getLoc()
{
	return str_loc;
}
String Menu::getStr()
{
	return 	str_array[str_loc];
}
void Menu::setLoc(int n)
{
	str_loc=n;
}
void Menu::setNames(String arr[],int size)
{
	
	arr_len=size;
	int j;		
	for(j=0;j<arr_len;j++)
	{
		str_array[j]=arr[j];
	}
	
	for(j=arr_len;j<max_length_menu;j++)
	{
		str_array[j]="";
	}
}

