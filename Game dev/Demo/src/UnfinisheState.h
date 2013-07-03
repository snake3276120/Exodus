
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
		���˵�״̬
	*/

	
	class DemoApp;

	class UnfinishState : public State, public SingletonT<UnfinishState>
	{
		SINGLETON_DEFINE(UnfinishState)

	public:
		~UnfinishState(){};

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
		UnfinishState()
		{
			mToHide		 = false;
			mToShow		 = false;

			mFactor			 = 0.0f;
		}


		bool mToHide;    
		bool mToShow;  
		bool mToBack;
	
		float mFactor;    //Ч������


		float inline getAlpha(){	return GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->getAlpha(); }
		void inline setAlpha(float x){  GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->setAlpha(x) ;  }
		void setVisible(bool visibility){  GUISystem::getSingletonPtr()-> getGUISheet() -> getChild("UnfinishUI/Frontground")->setVisible(visibility); }
		bool onBack(const CEGUI::EventArgs& e);
	};
}
#endif