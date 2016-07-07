#include "Arduino.h"
#include "Page.h"
#ifndef Menu_h
#define Menu_h
#define header_loc 0
#define text_loc 1
#define arrow_left_loc 2
#define arrow_right_loc 3
#define max_length 10

class Menu : public Page
{
	public:
		void left();
		void right();
		//virtual void click();
		Menu(String arr[],String header);
	private:
		String header;
		String str_array[max_length];
		int mid_pos(String SingleStr);
		void update_menu(int move);
		int str_loc;
		int arr_len;
};
#endif