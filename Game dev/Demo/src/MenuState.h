
#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

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

	class MenuState : public State, public SingletonT<MenuState>
	{
		SINGLETON_DEFINE(MenuState)

	public:
		~MenuState(){};

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

		bool onExit(const CEGUI::EventArgs& e);
	private:
		MenuState()
		{
			mInit			 = false;           
			mDestory		 = false;         

			mToHideMenu		 = false;

			mToShowMenu		 = false;


			mToAchievement   = false;
			mToUnfinish		 = false;
			mToQuit          = false;
			mToStarGame      = false;
			mFactor			 = 0.0f;
		}

		bool mInit;              //true表示LOGO已载入过。
		bool mDestory;           //true表示


		bool mToHideMenu;        //ture表示按钮触发事件，菜单要旋转。
		bool mToShowMenu;        //ture表示按钮触发事件，菜单要旋转。


		bool mToAchievement;
		bool mToQuit;
		bool mToUnfinish;
		bool mToStarGame;
	
		float mFactor;    //效果因子

		void subscribeEvent ();

		float inline getMenuRotation(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("MenuUI/MenuFrame")->getRotation().d_z;}
		void inline setMenuRotation(float rotation){ GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("MenuUI/MenuFrame")->setRotation(CEGUI::Vector3(0,0,rotation)); }

		bool onStarGame(const CEGUI::EventArgs& e);
		bool onAchievement(const CEGUI::EventArgs& e);
		bool onUnfinish(const CEGUI::EventArgs& e);

	};
}
#endif