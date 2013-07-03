#include "InputSystem.h"

namespace Demo
{
	//---------------------------------------------------------------------------------------------------------

	InputSystem::InputSystem() : 
		mInputManager(0), mMouse(0), mRenderWindow(0),
		mKeyboard(0), mIsNexclusive(false) {}

	//---------------------------------------------------------------------------------------------------------

	InputSystem::~InputSystem() { }

	//---------------------------------------------------------------------------------------------------------

	// ��ʼ��,ֻ�е�һ�ε�����Ч
	// isNexclusive ����Ƿ��ռ(�Ƕ�ռģʽ�������Ƴ�����֮��)
	void InputSystem::init(Ogre::RenderWindow* renderWindow, bool isNexclusive)
	{
		if (!mInputManager)
		{
			mRenderWindow = renderWindow;
			mIsNexclusive = isNexclusive;

			OIS::ParamList pl;
			size_t windowHnd = 0;
			std::ostringstream windowHndStr;

			renderWindow->getCustomAttribute("WINDOW", &windowHnd);
			windowHndStr << windowHnd;
			pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

			if (!isNexclusive)
			{	
				// �Ƕ�ռģʽ�������Ƴ�����֮��
				pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
				pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));
				// ����ϵͳ���
				//::ShowCursor(false);
			}


			// ����OI�豸
			mInputManager = OIS::InputManager::createInputSystem( pl );

			mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
			mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

			// ��������ƶ���Χ, ����Ⱦ���ڴ�С��ͬ
			updateMouseExtents(float(mRenderWindow->getWidth()), float(mRenderWindow->getHeight()));
		}		
	}

	//---------------------------------------------------------------------------------------------------------

	// ��������ƶ���Χ
	void InputSystem::updateMouseExtents(float width, float height)
	{
		// ������귶Χ(������ڸ��Ĵ�С,��Ҫ�޸������Χ)
		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width  = width;
		mouseState.height = height;
	}

	//---------------------------------------------------------------------------------------------------------

	// �������,���̻ص�����
	void InputSystem::setMouseEventCallback(OIS::MouseListener *mouse)
	{
		mMouse->setEventCallback(mouse);
	}

	//---------------------------------------------------------------------------------------------------------

	void InputSystem::setKeyboardEventCallback(OIS::KeyListener *keyboard)
	{
		mKeyboard->setEventCallback(keyboard);
	}

	//---------------------------------------------------------------------------------------------------------

	void InputSystem::destroy()
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);
			OIS::InputManager::destroyInputSystem(mInputManager);

			mInputManager = 0;
		}
	}

	//---------------------------------------------------------------------------------------------------------
}