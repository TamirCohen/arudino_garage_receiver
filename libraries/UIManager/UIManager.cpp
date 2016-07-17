#include "UIManager.h"
#include "Menu.h"
#include "Spage.h"
#include "NamePage.h"
#include "global.h"
#include <arduino.h>
UIManager::UIManager()
{
	String *arrr = EE_manager.GetNames(); 
    TransMenu=new Menu(arrr,EE_manager.LastIdx(),0,"");
    String arr[3] ={"New","Delete","Transmit"};
    SetMenu=new Menu(arr,3,1,"Settings");
	TransPage=new Spage("Transmiting:");
	NPage =new NamePage("Long to Save");
	SetMenu->Cfocus();

}
boolean UIManager::IsMenu()
{
	return(TransMenu->IsFocus()||SetMenu->IsFocus());
}
void UIManager::Start()
{
	SetMenu->show();
	TransMenu->show();
}
void UIManager::LongClick()
{
	if(IsMenu())
	{
		TransMenu->Cfocus();
		SetMenu->Cfocus();
		SetMenu->setLoc(0);
		TransMenu->show();
		SetMenu->show();
	}
	if(NPage->IsFocus())
	{
		
		String name =NPage->GetName()
		if(name!="")
		{
			NPage->Cfocus();
			TransMenu->Cfocus();
			TransMenu->show();
			SetMenu->show();
			
			//add transmition in eeprom-get str
		}
		
		
		
		
	}
}
void UIManager::ShortClick()
{
	if(IsMenu())
	{
		if(TransMenu->IsFocus())
		{
			TransMenu->Cfocus();
			TransPage->setRow2(TransMenu->getStr());
			TransPage->Cfocus();
			TransPage->show();
			delay(250000);////transmit!!
			TransPage->Cfocus();
			TransMenu->Cfocus();
			TransMenu->show();
			SetMenu->show();
		}
		else if(SetMenu->getStr()=="Transmit")
		{
			SetMenu->Cfocus();
			TransPage->setRow2(TransMenu->getStr());
			TransPage->Cfocus();
			TransPage->show();
			delay(250000);//transmit!!
			TransPage->Cfocus();
			SetMenu->Cfocus();
			SetMenu->show();
			TransMenu->show();
		}
		else if(SetMenu->getStr()=="New")
		{
			SetMenu->Cfocus();
			NPage->Cfocus();
			NPage->show();
		}
	}
	else if(NPage)
	{
		NPage->next();
		NPage->show();
	}
}
void UIManager::Right()
{
	if(IsMenu())
	{
		TransMenu->right();
		SetMenu->right();
		TransMenu->show();
		SetMenu->show();
	}
	if(NPage->IsFocus())
	{
		NPage->right();
		NPage->show();
	}
}
void UIManager::Left()
{
	if(IsMenu())
	{
		TransMenu->left();
		SetMenu->left();
		TransMenu->show();
		SetMenu->show();
	}
	if(NPage->IsFocus())
	{
		NPage->left();
		NPage->show();
	}
}
