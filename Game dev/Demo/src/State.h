#ifndef __STATE_H__
#define __STATE_H__


#include <Ogre.h>
#include "IFrameListener.h"
#include "IKeyMouseListener.h"

namespace Demo
{
	/*
		游戏状态基类
		其他游戏状态如菜单状态,游戏状态等均需要由此继承并实现具体操作.
	*/
	class State : public IFrameListener, public IKeyMouseListener
	{
	public:
		virtual ~State(){}

		// 进入状态
		virtual void enter( void )  = 0;
		// 退出状态
		virtual void exit( void )   = 0;

		// 暂停状态
		virtual void pause( void ) {}
		// 回复状态
		virtual void resume( void ) {}
		



		//=============================================================================
		/** 
			更换状态,将栈顶状态弹出,将此状态压栈
			@newState 新状态
		*/	
		void changeState( State *newState );

		/**
			入栈状态,先将栈顶状态pause()后压栈
			@newState	新状态
		*/
		void pushState( State *newState );

		// 弹出状态
		void popState( void );

	protected:
		State(){}
		State(const State&);
		State& operator=(const State&);
	};
}
#endif