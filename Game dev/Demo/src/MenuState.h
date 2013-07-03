
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
		���˵�״̬
	*/

	
	class DemoApp;

	class MenuState : public State, public SingletonT<MenuState>
	{
		SINGLETON_DEFINE(MenuState)

	public:
		~MenuState(){};

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

		bool mInit;              //true��ʾLOGO���������
		bool mDestory;           //true��ʾ


		bool mToHideMenu;        //ture��ʾ��ť�����¼����˵�Ҫ��ת��
		bool mToShowMenu;        //ture��ʾ��ť�����¼����˵�Ҫ��ת��


		bool mToAchievement;
		bool mToQuit;
		bool mToUnfinish;
		bool mToStarGame;
	
		float mFactor;    //Ч������

		void subscribeEvent ();

		float inline getMenuRotation(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("MenuUI/MenuFrame")->getRotation().d_z;}
		void inline setMenuRotation(float rotation){ GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("MenuUI/MenuFrame")->setRotation(CEGUI::Vector3(0,0,rotation)); }

		bool onStarGame(const CEGUI::EventArgs& e);
		bool onAchievement(const CEGUI::EventArgs& e);
		bool onUnfinish(const CEGUI::EventArgs& e);

	};
}
#endif