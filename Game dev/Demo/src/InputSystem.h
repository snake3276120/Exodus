
#ifndef __INPUTSYSTEM_H_
#define __INPUTSYSTEM_H_

#include <Ogre.h>
#include <OIS.h>
#include "SingletonT.h"

namespace Demo
{
	/**
		OIS�豸������
	*/
	class InputSystem : public SingletonT<InputSystem>
	{
		SINGLETON_DEFINE(InputSystem)

	public:
		~InputSystem();

		// �����豸
		void destroy();

		/**
			��ʼ��,ֻ�е�һ�ε�����Ч
			@renderWindow	��Ⱦ����
			@isNexclusive	����Ƿ��ռ(�Ƕ�ռģʽ�������Ƴ�����֮��)
		*/
		void init(Ogre::RenderWindow* renderWindow, bool isNexclusive = true);

		// �������,���̻ص�����
		void setMouseEventCallback(OIS::MouseListener *mouse);
		void setKeyboardEventCallback(OIS::KeyListener *keyboard);

		/**
			��������ƶ���Χ
			@width	���º���Ⱦ���ڵĿ��
			@height	���º���Ⱦ���ڵĸ߶�
		*/
		void updateMouseExtents(float width, float height);

		// �������,�����¼�
		inline void capture()
		{
			mMouse->capture();
			mKeyboard->capture();
		}

		// ��������Ƿ�Ϊ��ռģʽ
		inline bool isNexclusive() const { return mIsNexclusive; }
		// ��ȡ����豸
		inline OIS::Mouse* getMouse() { return mMouse; }
		// ��ȡ�����豸
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