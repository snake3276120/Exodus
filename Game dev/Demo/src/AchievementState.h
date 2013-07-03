
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
		主菜单状态
	*/

	
	class DemoApp;

	class AchievementState : public State, public SingletonT<AchievementState>
	{
		SINGLETON_DEFINE(AchievementState)

	public:
		~AchievementState(){};

		// 进入状态
		void enter( void );

		// 退出状态
		void exit( void ){}

		// 暂停状态
		void pause( void ) {}
		// 回复状态
		void resume( void ) {}

		// 更新状态
		void update( float timeSinceLastFrame );
		// 渲染后更新状态
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
	
		float mFactor;    //效果因子


		float inline getPosition(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("AchievementUI/Frame")->getXPosition().d_scale; }
		void inline setPosition(float x){GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("AchievementUI/Frame")->setXPosition(CEGUI::UDim(x,0)) ;}
		bool onBack(const CEGUI::EventArgs& e);
	};
}
#endif