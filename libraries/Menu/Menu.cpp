#include "Arduino.h"
#include "Menu.h"
#include "LcdString.h"
#define header_loc 0
#define text_loc 1
#define arrow_left_loc 2
#define arrow_right_loc 3
#define led_length 16
#define max_length 10



Menu::Menu(String arr[],String Header):Page()
{
	arr_len=sizeof(arr)+1;
	int j;
	for(j=0;j<arr_len;j++)
	{
		str_array[j]=arr[j];
	}
	str_loc=0;
	header=Header;
	lcd_array[arrow_left_loc].SetText("<");
	lcd_array[arrow_left_loc].SetRow(1);
	lcd_array[arrow_left_loc].SetColumn(0);
	lcd_array[arrow_right_loc].SetText(">");
	lcd_array[arrow_right_loc].SetRow(1);
	lcd_array[arrow_right_loc].SetColumn(15);
	lcd_array[header_loc].SetRow(0);
	lcd_array[text_loc].SetRow(1);
	update_menu(0);
	
}
int Menu::mid_pos(String SingleStr)
{
	return((led_length-SingleStr.length())/2);
}
void Menu::right()
{
	update_menu(1);
}
void Menu::left()
{
	update_menu(-1);
}
void Menu::update_menu(int move)
{
	clear();
	Serial.print("arr_len ");
	Serial.println(arr_len);
	
	
	if(str_loc+move<arr_len&&str_loc+move>-1)
	{
		str_loc = str_loc+move;
		lcd_array[arrow_left_loc].SetText("<");
		lcd_array[arrow_right_loc].SetText(">");
		if(str_loc==0)
		{
			Serial.println("to left");
			lcd_array[arrow_left_loc].SetText("");
			if(arr_len==0)
			{
				lcd_array[arrow_right_loc].SetText("");
			}
		}
		else if(str_loc==arr_len-1)
		{
			Serial.println("to right");
			lcd_array[arrow_right_loc].SetText("");
		}
		lcd_array[text_loc].SetText(str_array[str_loc]);
		lcd_array[text_loc].SetColumn(mid_pos(str_array[str_loc]));
		lcd_array[header_loc].SetText(header);
		lcd_array[header_loc].SetColumn(mid_pos(header));
		Serial.println("right");
		Serial.println(lcd_array[arrow_right_loc].GetText());
		Serial.println("left");
		Serial.println(lcd_array[arrow_left_loc].GetText());
	}
}