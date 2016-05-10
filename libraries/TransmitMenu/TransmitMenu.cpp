#include "TransmitMenu.h"
#include "Menu.h"
#include "global.h"
#include <EEPROM_sys.h>
#include <ComVector.h>
TransmitMenu::TransmitMenu(String arr[],int size,int row):Menu(arr,size,row)
{
	
}
void TransmitMenu::click()
{
	Com_manager.TransmitVec(0);
}