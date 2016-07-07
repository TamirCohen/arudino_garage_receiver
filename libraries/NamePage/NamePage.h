#ifndef NamePage_h
#define NamePage_h
#include "Page.h"
#include <arduino.h>
class NamePage : public Page
{
	public:
		NamePage(String Row2);
		void right();
		void left();
		void next();
		String GetName();
		void Cfocus();
		void show();
	private:
		int loc;
		String getName();
		String row2;
		String name;
		boolean CanPass();
};


#endif