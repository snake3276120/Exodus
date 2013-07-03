
#ifndef __ACHIEVEMENTSTATE_H__
#define __ACHIEVEMENTSTATE_H__

#include <CEGUI.h>
#include "DemoApp.h"
#include "State.h"
#include "SingletonT.h"
#include "GUISystem.h"
#include "Util.h"
#include "StateManager.h"


namespace Demo
{
	/**
		���˵�״̬
	*/

	
	class DemoApp;

	class AchievementState : public State, public SingletonT<AchievementState>
	{
		SINGLETON_DEFINE(AchievementState)

	public:
		~AchievementState(){};

		// ����״̬
		void enter( void );

		// �˳�״̬
		void exit( void ){}

		// ��ͣ״̬
		void pause( void ) {}
		// �ظ�״̬
		void resume( void ) {}

		// ����״̬
		void update( float timeSinceLastFrame );
		// ��Ⱦ�����״̬
		void updateAfterRender( float timeSinceLastFrame){}

	private:
		AchievementState()
		{
			mToHide		 = false;
			mToShow		 = false;

			mFactor			 = 0.0f;
		}


		bool mToHide;    
		bool mToShow;  
		bool mToBack;
	
		float mFactor;    //Ч������


		float inline getPosition(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("AchievementUI/Frame")->getXPosition().d_scale; }
		void inline setPosition(float x){GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("AchievementUI/Frame")->setXPosition(CEGUI::UDim(x,0)) ;}
		bool onBack(const CEGUI::EventArgs& e);
	};
}
#endif