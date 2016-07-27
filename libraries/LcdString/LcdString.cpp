#include "Button.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include <global.h>
#include "LcdString.h"

LcdString::LcdString(int row,int column,String text)
{
	Row=row;
	Column=column;
	Text=text;

}
LcdString::LcdString()
{
	Row=0;
	Column=0;
	Text=F("");
}
void LcdString::reserve(uint8_t n)
{
	Text.reserve(n);
}
void LcdString::Display()
{
	lcd.setCursor(Column,Row);
	lcd.print(Text);
	
}
String LcdString::GetText()
{
	return Text;
}
void LcdString::SetText(String text)
{
	Text=text;
}
void LcdString::SetColumn(int col)
{
	Column=col;
}
void LcdString::SetRow(int row)
{
	Row=row;
}