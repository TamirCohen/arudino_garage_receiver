#include "UIManager.h"
#include "Menu.h"
#include "Spage.h"
#include "NamePage.h"
#include "global.h"
#include "com.h"
#include "ComVector.h"
#include <arduino.h>
UIManager::UIManager() : TransMenu(EE_manager.GetNames(),EE_manager.LastIdx(),0,F("")),SetMenu(SetMenu_arr,5,1,F("Settings")),TransPage(F("Transmiting:")),RecvPage(F("Receiving..."),F("Click the remote")),NPage(F("Long to Save"))
{
	if(EE_manager.LastIdx()==0)
	{
		TransMenu.Cfocus();
		
	}
	else
	{
		SetMenu.Cfocus();
	}
	LongPress=false;
	ShortPress=false;
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
		if(name!=F(""))
		{
			ComVector* a = m.GetVec();
			a->setName(name);
			a->printVec();
			a->writeEE();
			String* tmp = EE_manager.GetNames();
			TransMenu.setNames(tmp,EE_manager.LastIdx());
			delete [] tmp;
			m.clean();
			SetMenu.setLoc(0);
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
			RecvPage.setRow2("Click The Remote");
			RecvPage.Cfocus();
			RecvPage.show();
			CShort(false);
			Serial.println(F("killed flag"));
			m.MultiRead(5);
			//finshed getting the transmition
			Serial.println(F("finshed reading"));
			if(LongPress||ShortPress)
			{
				Serial.println(F("noticed flag outside"));
				RecvPage.Cfocus();
				SetMenu.Cfocus();
				SetMenu.show();
				TransMenu.show();
			}
			else
			{
				Serial.println(F("didnt notice flag outside"));
				RecvPage.Cfocus();
				NPage.Cfocus();
				NPage.show();
				
			}
		}
		else if(SetMenu.getStr()==F("Spy Mode"))
		{
			SetMenu.Cfocus();
			RecvPage.setRow2("Spy Mode");
			RecvPage.Cfocus();
			RecvPage.show();
			CShort(false);
			Serial.println(F("killed flag"));
			m.MultiRead(2);
			//finshed getting the transmition
			Serial.println(F("finshed reading"));
			if(LongPress||ShortPress)
			{
				Serial.println(F("noticed flag outside"));
				RecvPage.Cfocus();
				SetMenu.Cfocus();
				SetMenu.show();
				TransMenu.show();
			}
			else
			{
				Serial.println(F("didnt notice flag outside"));
				RecvPage.Cfocus();
				NPage.Cfocus();
				NPage.show();
				
			}
		}
		else if(SetMenu.getStr()==F("Delete"))
		{
			EE_manager.Delete((char)TransMenu.getLoc());
			String* tmp = EE_manager.GetNames();
			TransMenu.setNames(tmp,EE_manager.LastIdx());
			delete [] tmp;
			TransMenu.setLoc(0);
			SetMenu.setLoc(0);
			SetMenu.Cfocus();
			TransMenu.Cfocus();
			SetMenu.show();
			TransMenu.show();
		}
		else if(SetMenu.getStr()==F("Reset"))
		{
			EE_manager.clear();
			String* tmp = EE_manager.GetNames();
			TransMenu.setNames(tmp,EE_manager.LastIdx());
			delete [] tmp;
			TransMenu.setLoc(0);
			SetMenu.setLoc(0);
			SetMenu.Cfocus();
			TransMenu.Cfocus();
			SetMenu.Cfocus();
			TransMenu.Cfocus();
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
void UIManager::CLong(boolean l)
{
	LongPress = l;
}
void UIManager::CShort(boolean s)
{
	digitalWrite(13,HIGH);
	ShortPress = s;
	digitalWrite(13,LOW);
}
boolean UIManager::CheckClick()
{
	if(LongPress)
	{
		LongClick();
		LongPress = false;
		return(true);
	}
	if(ShortPress)
	{
		Serial.println(F("short fleg up"));
		ShortClick();
		ShortPress = false;
		return(true);
	}
	return(false);
}
boolean UIManager::event()
{
	return(ShortPress||LongPress);
}