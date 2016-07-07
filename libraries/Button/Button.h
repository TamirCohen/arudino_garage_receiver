#ifndef Button_h
#define Button_h
#include "Arduino.h"

class Button
{
	public:
		Button(void);
		void UpdateLoc(void);//change to private
		int GetLoc(void);
		void Click(void);
		void CheckLoc(void);
		
	private:
		int loc;
		bool LastStateA;
		unsigned long LastClick;

};

#endif