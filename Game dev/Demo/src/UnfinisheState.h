
#ifndef __UNFINISHSTATE_H__
#define __UNFINISHSTATE_H__

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

	class UnfinishState : public State, public SingletonT<UnfinishState>
	{
		SINGLETON_DEFINE(UnfinishState)

	public:
		~UnfinishState(){};

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
		UnfinishState()
		{
			mToHide		 = false;
			mToShow		 = false;

			mFactor			 = 0.0f;
		}


		bool mToHide;    
		bool mToShow;  
		bool mToBack;
	
		float mFactor;    //效果因子


		float inline getAlpha(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->getAlpha(); }
		void inline setAlpha(float x){  GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->setAlpha(x) ;  }
		void setVisible(bool visibility){  GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->setVisible(visibility); }
		bool onBack(const CEGUI::EventArgs& e);
	};
}
#endif