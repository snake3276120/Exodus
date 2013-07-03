#ifndef __STATE_H__
#define __STATE_H__


#include <Ogre.h>
#include "IFrameListener.h"
#include "IKeyMouseListener.h"

namespace Demo
{
	/*
		��Ϸ״̬����
		������Ϸ״̬��˵�״̬,��Ϸ״̬�Ⱦ���Ҫ�ɴ˼̳в�ʵ�־������.
	*/
	class State : public IFrameListener, public IKeyMouseListener
	{
	public:
		virtual ~State(){}

		// ����״̬
		virtual void enter( void )  = 0;
		// �˳�״̬
		virtual void exit( void )   = 0;

		// ��ͣ״̬
		virtual void pause( void ) {}
		// �ظ�״̬
		virtual void resume( void ) {}
		



		//=============================================================================
		/** 
			����״̬,��ջ��״̬����,����״̬ѹջ
			@newState ��״̬
		*/	
		void changeState( State *newState );

		/**
			��ջ״̬,�Ƚ�ջ��״̬pause()��ѹջ
			@newState	��״̬
		*/
		void pushState( State *newState );

		// ����״̬
		void popState( void );

	protected:
		State(){}
		State(const State&);
		State& operator=(const State&);
	};
}
#endif