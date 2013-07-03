
#ifndef __INPUTSYSTEM_H_
#define __INPUTSYSTEM_H_

#include <Ogre.h>
#include <OIS.h>
#include "SingletonT.h"

namespace Demo
{
	/**
		OIS设备管理器
	*/
	class InputSystem : public SingletonT<InputSystem>
	{
		SINGLETON_DEFINE(InputSystem)

	public:
		~InputSystem();

		// 销毁设备
		void destroy();

		/**
			初始化,只有第一次调用有效
			@renderWindow	渲染窗口
			@isNexclusive	鼠标是否独占(非独占模式下鼠标可移出窗口之外)
		*/
		void init(Ogre::RenderWindow* renderWindow, bool isNexclusive = true);

		// 设置鼠标,键盘回调函数
		void setMouseEventCallback(OIS::MouseListener *mouse);
		void setKeyboardEventCallback(OIS::KeyListener *keyboard);

		/**
			更新鼠标移动范围
			@width	更新后渲染窗口的宽度
			@height	更新后渲染窗口的高度
		*/
		void updateMouseExtents(float width, float height);

		// 捕获鼠标,键盘事件
		inline void capture()
		{
			mMouse->capture();
			mKeyboard->capture();
		}

		// 返回鼠标是否为独占模式
		inline bool isNexclusive() const { return mIsNexclusive; }
		// 获取鼠标设备
		inline OIS::Mouse* getMouse() { return mMouse; }
		// 获取键盘设备
		inline OIS::Keyboard* getKeyboard() { return mKeyboard; }

	protected:
		InputSystem();

	protected:
		OIS::InputManager		*mInputManager;
		OIS::Mouse				*mMouse;
		OIS::Keyboard			*mKeyboard;

		Ogre::RenderWindow		*mRenderWindow;

		bool					mIsNexclusive;
	};
}

#endif