#include "Menu.h"
#include "Spage.h"
#include "NamePage.h"
#ifndef UIManager_h
#define UIManager_h
#include <arduino.h>
class UIManager
{
	public:
		UIManager();
		void Start();
		void LongClick();
		void ShortClick();
		void Right();
		void Left();
	private:
		Menu *TransMenu;
		Menu *SetMenu;
		Spage *TransPage;
		NamePage *NPage;
		boolean IsMenu();
		
};


#endif