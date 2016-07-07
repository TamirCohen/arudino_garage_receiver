#include "Arduino.h"
#include "Page.h"
#ifndef Menu_h
#define Menu_h
#define max_length 10

class Menu : public Page
{
	public:
		void left();
		void right();
		//virtual void click();
		void Cfocus();
		Menu(String arr[],int size ,int row,String Message);
		int getLoc();
		String getStr();
		void setLoc(int n);
	private:
		String str_array[max_length];
		void update_menu(int move);
		int str_loc;
		int arr_len;
		String message;
		int row;
};
#endif