#include <CEGUI.h>


#include "AchievementState.h"
#include "DemoApp.h"
#include "State.h"
#include "SingletonT.h"
#include "GUISystem.h"
#include "Util.h"
#include "StateManager.h"


namespace Demo
{


	// ½øÈë×´Ì¬
	void AchievementState::enter( void )	
	{
			GUISystem::loadWindow("AchievementUI");
			GUISystem::subscribeEvent("AchievementUI/Frame/Bottom/BackButton", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&AchievementState::onBack, this));
			
			setPosition(1);	
			mToShow = true;

	}


	void AchievementState::update( float timeSinceLastFrame )
	{
		if(mToShow)
		{
			if(getPosition()-timeSinceLastFrame/20000-mFactor<0.5f)
			{
				setPosition(0.5);
				mToShow=false;
				mFactor = 0.0f;
			}
			else
			{
				setPosition(getPosition()-timeSinceLastFrame/20000-mFactor);
				mFactor=mFactor+0.02f;
			}
		}
		if (mToHide)
		{
			if(getPosition()+timeSinceLastFrame/20000+mFactor>1.0f)
			{
				setPosition(1.0f);
				mToHide=false;
				mFactor = 0.0f;
				if (mToBack)
				{
					GUISystem::destoryWindow("AchievementUI");
					changeState(MenuState::getSingletonPtr());
					mToBack=false;
				}
			}
			else
			{
				setPosition(getPosition()+timeSinceLastFrame/20000+mFactor);
				mFactor=mFactor+0.02f;
			}
		}
	}

	bool AchievementState::onBack(const CEGUI::EventArgs& e)
	{
		mToHide = true;
		mToBack = true;
		mFactor = 0.0f;
		return true;
	}



}
