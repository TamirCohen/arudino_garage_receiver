#include "UIManager.h"
#include "Menu.h"
#include "Spage.h"
#include "NamePage.h"
#include "global.h"
#include "com.h"
#include "ComVector.h"
#include <arduino.h>
UIManager::UIManager() : TransMenu(EE_manager.GetNames(),EE_manager.LastIdx(),0,F("")),SetMenu(SetMenu_arr,3,1,F("Settings")),TransPage(F("Transmiting:")),RecvPage(F("Receiving..."),F("Click the remote")),NPage(F("Long to Save"))
{
	if(EE_manager.LastIdx()==0)
	{
		TransMenu.Cfocus();
		
	}
	else
	{
		SetMenu.Cfocus();
	}
}
boolean UIManager::IsMenu()
{
	return(TransMenu.IsFocus()||SetMenu.IsFocus());
}
void UIManager::Start()
{
	SetMenu.show();
	TransMenu.show();
}
void UIManager::LongClick()
{
	if(IsMenu())
	{
		TransMenu.Cfocus();
		SetMenu.Cfocus();
		SetMenu.setLoc(0);
		TransMenu.show();
		SetMenu.show();
	}
	if(NPage.IsFocus())
	{	
		String name =NPage.GetName();
		Serial.println(name);
		if(name!=F(""))
		{
			ComVector* a = m.GetVec();
			a->setName(name);
			a->printVec();
			a->writeEE();
			TransMenu.setNames(EE_manager.GetNames(),EE_manager.LastIdx());
			m.clean();
			NPage.Cfocus();
			TransMenu.Cfocus();
			TransMenu.show();
			SetMenu.show();
			
			//add transmition in eeprom-get str
		}
		
		
		
		
	}
}
void UIManager::ShortClick()
{
	if(IsMenu())
	{
		if(TransMenu.IsFocus())
		{
			TransMenu.Cfocus();
			TransPage.setRow2(TransMenu.getStr());
			TransPage.Cfocus();
			TransPage.show();
			m.transmit(TransMenu.getLoc());
			Serial.println(F("Transmiting!"));
			TransPage.Cfocus();
			TransMenu.Cfocus();
			TransMenu.show();
			SetMenu.show();
		}
		else if(SetMenu.getStr()==F("Transmit"))
		{
			SetMenu.Cfocus();
			TransPage.setRow2(TransMenu.getStr());
			TransPage.Cfocus();
			TransPage.show();
			m.transmit(TransMenu.getLoc());
			TransPage.Cfocus();
			SetMenu.Cfocus();
			SetMenu.show();
			TransMenu.show();
		}
		else if(SetMenu.getStr()==F("New"))
		{
			SetMenu.Cfocus();
			RecvPage.Cfocus();
			RecvPage.show();
			m.MultiRead();
			//finshed getting the transmition
			RecvPage.Cfocus();
			NPage.Cfocus();
			NPage.show();
		}
		else if(SetMenu.getStr()==F("Delete"))
		{
			EE_manager.Delete((char)TransMenu.getLoc());
			SetMenu.Cfocus();
			TransMenu.Cfocus();
			TransMenu.setNames(EE_manager.GetNames(),EE_manager.LastIdx());
			TransMenu.setLoc(0);
			SetMenu.show();
			TransMenu.show();
			
		}
	}
	else if(NPage.IsFocus())
	{
		NPage.next();
		NPage.show();
	}
}
void UIManager::Right()
{
	if(IsMenu())
	{
		TransMenu.right();
		SetMenu.right();
		TransMenu.show();
		SetMenu.show();
	}
	if(NPage.IsFocus())
	{
		NPage.right();
		NPage.show();
	}
}
void UIManager::Left()
{
	if(IsMenu())
	{
		TransMenu.left();
		SetMenu.left();
		TransMenu.show();
		SetMenu.show();
	}
	if(NPage.IsFocus())
	{
		NPage.left();
		NPage.show();
	}
}
