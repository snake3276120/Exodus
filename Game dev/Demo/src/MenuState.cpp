#include <CEGUI.h>


#include "MenuState.h"
#include "DemoApp.h"
#include "State.h"
#include "SingletonT.h"
#include "GUISystem.h"
#include "Util.h"
#include "StateManager.h"
#include "AchievementState.h"
#include "UnfinisheState.h"
#include "GameState.h"


namespace Demo
{


		// 进入状态
	void MenuState::enter( void )	
	{
		if (mInit)
		{
			GUISystem::loadWindow("MenuUI");
			GUISystem::setCursorType(CURSOR_NORMAL);
			subscribeEvent();
			setMenuRotation(-90);
			mToShowMenu = true;
			mFactor = 0.0f;//一旦出现Todo什么的时候就必须跟着恢复效果因子。
		}
		else
		{
			GUISystem::loadWindow("LogoUI");
			mFactor = -3.1415926f;
			GUISystem::showGUICursor(false);
		}
	}


	void MenuState::update( float timeSinceLastFrame )
	{
			
		//=========淡入淡出logoUI==============================

		if (!mDestory && !mInit &&  (mFactor < 3.1415926f))
		{
			mFactor+=timeSinceLastFrame/1000;
			float alphaa =  0.5f+cos(mFactor)/2;
			GUISystem::getSingletonPtr()-> getGUISheet() -> setAlpha( alphaa );

		}else if(!mDestory){
			//======第一次进入MenuUI
			mInit = true;
			mDestory = true;
			mToShowMenu = true;
			mFactor = 0.0f;//恢复效果因子
			GUISystem::destoryWindow("LogoUI");
			GUISystem::loadWindow("MenuUI");
			subscribeEvent();
			setMenuRotation(-90);
			float a = getMenuRotation();

			GUISystem::showGUICursor(true);
			//std::cout<<a<<" ";
		}
		//======================================================		

		if (mInit && mDestory)
		{

			if (mToShowMenu)
			{
				float a = getMenuRotation();
				std::cout<<"a:"<<a<<" time:"<<timeSinceLastFrame<<"";

				if(getMenuRotation()+timeSinceLastFrame/4+mFactor>0)
				{
					setMenuRotation(0);
					mToShowMenu=false;
				}
				else
				{
					setMenuRotation(getMenuRotation()+timeSinceLastFrame/4+mFactor);
					mFactor=mFactor+3.0f;
				}
			}
			//===============================================================================
			if (mToHideMenu)
			{
				if(getMenuRotation()-timeSinceLastFrame/4-mFactor<-90)
				{
					setMenuRotation(-90);
					mToHideMenu=false;
					if (mToQuit)
					{
						DemoApp::getSingletonPtr()->shutDown();
						mToQuit=false;
					}else if (mToAchievement)
					{
						GUISystem::destoryWindow("MenuUI");
						changeState(AchievementState::getSingletonPtr());
						mToAchievement = false;
					}else if (mToUnfinish)
					{
						GUISystem::destoryWindow("MenuUI");
						changeState(UnfinishState::getSingletonPtr());
						mToUnfinish = false;
					}else if (mToStarGame)
					{
						GUISystem::destoryWindow("MenuUI");
						changeState(GameState::getSingletonPtr());
						mToStarGame = false;
					}


				}else
				{
					setMenuRotation(getMenuRotation()-timeSinceLastFrame/4-mFactor);
					mFactor=mFactor+3.0f;
				}
			}



		}


	}


	void MenuState::subscribeEvent ()
	{
		GUISystem::subscribeEvent("MenuUI/MenuFrame/Exit", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuState::onExit, this));
		GUISystem::subscribeEvent("MenuUI/MenuFrame/Achievement", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuState::onAchievement, this));
		GUISystem::subscribeEvent("MenuUI/MenuFrame/ChangePlayer", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuState::onUnfinish, this));
		GUISystem::subscribeEvent("MenuUI/MenuFrame/Play", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuState::onStarGame, this));
		GUISystem::subscribeEvent("MenuUI/MenuFrame/Settings", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&MenuState::onUnfinish, this));
	}

	bool MenuState::onExit(const CEGUI::EventArgs& e)
	{
			mToHideMenu = true;
			mToQuit = true;
			mFactor = 0.0f;
		return true;
	}
	bool MenuState::onAchievement(const CEGUI::EventArgs& e)
	{
		mToHideMenu = true;
		mToAchievement = true;
		mFactor = 0.0f;
		return true;
	}

	bool MenuState::onUnfinish(const CEGUI::EventArgs& e)
	{
		mToHideMenu = true;
		mToUnfinish = true;
		mFactor = 0.0f;
		return true;
	}

	bool MenuState::onStarGame( const CEGUI::EventArgs& e )
	{
		mToHideMenu = true;
		mToStarGame = true;
		mFactor = 0.0f;
		return true;
	}

}
