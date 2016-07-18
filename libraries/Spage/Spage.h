#include "Page.h"
#ifndef Spage_h
#define Spage_h
#include <arduino.h>
class Spage: public Page
{
	private:
		String row1;
		String row2;
	public:
		Spage(String Row1);
		Spage(String Row1,String Row2);
		void setRow1(String Row1);
		void setRow2(String Row2);
		void Cfocus();
};


#endif