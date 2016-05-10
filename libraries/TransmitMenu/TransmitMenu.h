#include "Arduino.h"
#include "Menu.h"
#ifndef TransmitMenu_h
#define TransmitMenu_h

class TransmitMenu : public Menu
{
	public:
		TransmitMenu(String arr[],int size,int row);
		void click();
};








#endif