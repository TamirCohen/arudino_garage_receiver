#include "Spage.h"
#define Row1_loc 0
#define Row2_loc 1
#include "Page.h"
#include <arduino.h>
Spage::Spage(String Row1):Page()
{
	row1=Row1;
	row2="";
	lcd_array[Row1_loc].SetText(row1);
	lcd_array[Row1_loc].SetRow(0);
	lcd_array[Row1_loc].SetColumn(mid_pos(row1));
	lcd_array[Row2_loc].SetRow(1);
	focus=false;
}
Spage::Spage(String Row1,String Row2):Page()
{
	row1=Row1;
	row2=Row2;
	lcd_array[Row1_loc].SetText(row1);
	lcd_array[Row1_loc].SetRow(0);
	lcd_array[Row1_loc].SetColumn(mid_pos(row1));
	lcd_array[Row2_loc].SetRow(1);
	lcd_array[Row2_loc].SetText(row2);
	lcd_array[Row2_loc].SetColumn(mid_pos(row2));
	
	focus=false;
}
void Spage::setRow2(String Row2)
{
	row2=Row2;
	lcd_array[Row2_loc].SetText(row2);
	lcd_array[Row2_loc].SetColumn(mid_pos(row2));
}
void Spage::setRow1(String Row1)
{
	row1=Row1;
	
}
void Spage::Cfocus()
{
	clear();
	focus=!focus;
}