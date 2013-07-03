#include "State.h"
#include "StateManager.h"

namespace Demo
{
	//---------------------------------------------------------------------------------------------------------

	void State::changeState( State *newState )
	{
		StateManager::getSingletonPtr()->changeState(newState);
	}

	//---------------------------------------------------------------------------------------------------------

	void State::pushState( State *newState )
	{
		StateManager::getSingletonPtr()->pushState(newState);
	}

	//---------------------------------------------------------------------------------------------------------

	void State::popState( void )
	{
		StateManager::getSingletonPtr()->popState();
	}

	//---------------------------------------------------------------------------------------------------------
}