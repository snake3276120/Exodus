
#include "StateManager.h"
#include "Util.h"

namespace Demo
{
	//---------------------------------------------------------------------------------------------------------

	StateManager::~StateManager()
	{

	}

	//---------------------------------------------------------------------------------------------------------

	void StateManager::destroy()
	{
		/**
		ע��: ����vector��˵���ݵĸ��Ļᵼ�µ�������Ч, �����������
		*/
		while (!empty())
			popState();

		mStates.clear();
	}

	//---------------------------------------------------------------------------------------------------------

	void StateManager::changeState( State *newState )
	{
		// ����ջ��״̬
		if (!mStates.empty())
		{
			mStates.back()->exit();
			mStates.pop_back();
		}

		mStates.push_back(newState);
		newState->enter();
	}

	//---------------------------------------------------------------------------------------------------------

	void StateManager::pushState( State *newState )
	{
		// ��ջ��״̬��ͣ
		if (!mStates.empty())
			mStates.back()->pause();

		mStates.push_back(newState);
		newState->enter();
	}

	//---------------------------------------------------------------------------------------------------------

	void StateManager::popState( void )
	{
		// ����ջ��״̬
		if (!mStates.empty())
		{
			mStates.back()->exit();
			mStates.pop_back();
		}

		// �ָ���һ��״̬
		if (!mStates.empty())
			mStates.back()->resume();
	}

	//---------------------------------------------------------------------------------------------------------
}