#include "Page.h"
#include "NamePage.h"
#include "global.h"
#include <arduino.h>
#define info_pos 1
#define str_pos 0
NamePage::NamePage(String Row2)
{
	row2=Row2;
	loc=1;
	lcd_array[info_pos].SetText(Row2);
	lcd_array[info_pos].SetRow(1);
	lcd_array[info_pos].SetColumn(mid_pos(row2));
	lcd_array[str_pos].SetRow(0);
	lcd_array[str_pos].SetColumn(1);
	focus=false;
	name="";
}
void NamePage::Cfocus()
{
	focus=!focus;
	if(focus==false)
	{
		lcd.noCursor();
		name="";
		loc=1;
		clear();
		lcd_array[str_pos].SetText(name);
	}
}
void NamePage::show()
{
	int i;
	for(i=0;i<10;i++)
	{
		if(lcd_array[i].GetText()!="")
		{
			lcd_array[i].Display();
		}
	}
	lcd.cursor();
	lcd.setCursor(loc,0);
}
void NamePage::right()
{
	if(loc-name.length()!=0)
	{
		name=name+"a";
	}
	else
	{
		name.setCharAt(name.length()-1,'a'+(name.charAt(name.length()-1)-'a'+1)%26);
	}
	lcd_array[str_pos].SetText(name);
}
void NamePage::left()
{
	if(loc-name.length()!=0)
	{
		name=name+"z";
	}
	else
	{
		name.setCharAt(name.length()-1,'z'+(name.charAt(name.length()-1)-'z'-1)%26);
	}
	lcd_array[str_pos].SetText(name);
}
void NamePage::next()
{
	if(CanPass())
	{
		loc++;
		
	}
}
String NamePage::GetName()
{
	return name;
}
boolean NamePage::CanPass()
{
	return(name.length()<14&&loc-name.length()==0);
}
