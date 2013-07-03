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

	// 初始化,只有第一次调用有效
	// isNexclusive 鼠标是否独占(非独占模式下鼠标可移出窗口之外)
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
				// 非独占模式下鼠标可移出窗口之外
				pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_FOREGROUND"));
				pl.insert(std::make_pair(std::string("w32_mouse"), "DISCL_NONEXCLUSIVE"));
				// 隐藏系统鼠标
				//::ShowCursor(false);
			}


			// 构造OI设备
			mInputManager = OIS::InputManager::createInputSystem( pl );

			mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
			mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

			// 更新鼠标移动范围, 与渲染窗口大小相同
			updateMouseExtents(float(mRenderWindow->getWidth()), float(mRenderWindow->getHeight()));
		}		
	}

	//---------------------------------------------------------------------------------------------------------

	// 设置鼠标移动范围
	void InputSystem::updateMouseExtents(float width, float height)
	{
		// 设置鼠标范围(如果窗口更改大小,需要修改这个范围)
		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width  = width;
		mouseState.height = height;
	}

	//---------------------------------------------------------------------------------------------------------

	// 设置鼠标,键盘回调函数
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