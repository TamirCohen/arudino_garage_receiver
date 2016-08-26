#include "Menu.h"
#include "Spage.h"
#include "NamePage.h"
#include "com.h"
//#include "global.h"
#include "EEPROM_sys.h"
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
		void CLong(boolean l);
		void CShort(boolean s);
		boolean CheckClick();
		boolean event();
	private:
		String SetMenu_arr[5]={"New","Spy Mode","Delete","Transmit","Reset"};
		Menu TransMenu;
		Menu SetMenu;
		Spage TransPage;
		Spage RecvPage;
		NamePage NPage;
		com m;
		boolean IsMenu();
		boolean LongPress;
		boolean ShortPress;
		
};


#endif