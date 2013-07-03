#include <CEGUI.h>


#include "UnfinisheState.h"
#include "DemoApp.h"
#include "State.h"
#include "SingletonT.h"
#include "GUISystem.h"
#include "Util.h"
#include "StateManager.h"


namespace Demo
{


	// ½øÈë×´Ì¬
	void UnfinishState::enter( void )	
	{
		GUISystem::loadWindow("UnfinishUI");
		GUISystem::subscribeEvent("UnfinishUI/Background/ButtonFrame/Button", CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&UnfinishState::onBack, this));

		setAlpha(1.0f);	
		mToShow = true;
		mFactor = 0.0f;

	}


	void UnfinishState::update( float timeSinceLastFrame )
	{
		if(mToShow)
		{
			if(getAlpha()-timeSinceLastFrame/20000-mFactor<0)
			{
				setAlpha(0.0f);
				setVisible(false);
				mToShow=false;
				mFactor = 0.0f;
			}
			else
			{
				setAlpha(getAlpha()-timeSinceLastFrame/20000-mFactor);
				mFactor=mFactor+0.04f;
			}
		}
		if (mToHide)
		{
			if(getAlpha()+timeSinceLastFrame/20000+mFactor>1.0f)
			{
				setAlpha(1.0f);
				setVisible(true);
				mToHide=false;
				mFactor = 0.0f;
				if (mToBack)
				{
					GUISystem::destoryWindow("UnfinishUI");
					changeState(MenuState::getSingletonPtr());
					mToBack=false;
				}
			}
			else
			{
				setAlpha(getAlpha()+timeSinceLastFrame/20000+mFactor);
				mFactor=mFactor+0.04f;
			}
		}
	}

	bool UnfinishState::onBack(const CEGUI::EventArgs& e)
	{
		mToHide = true;
		mToBack = true;
		mFactor = 0.0f;
		return true;
	}



}
