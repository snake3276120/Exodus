
#ifndef __DEMOAPP_H__
#define __DEMOAPP_H__


#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>

#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <RendererModules/Ogre/CEGUIOgreResourceProvider.h>
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUIScriptModule.h>
#include <ScriptingModules/LuaScriptModule/CEGUILua.h>
#include "InputSystem.h"
#include "GUISystem.h"
#include "SingletonT.h"
#include "StateManager.h"
#include "MenuState.h"

using namespace Ogre;

namespace Demo
{
	class InputSystem;
	class DemoApp:public SingletonT<DemoApp> ,public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
	{
		SINGLETON_DEFINE(DemoApp)
	public:
		void go()
		{
			setup();
			startRenderLoop();
		}

		inline void shutDown() { mIsShutDown = true; }


		~DemoApp()
		{
			//mInputManager->destroyInputObject(mKeyboard);
			//OIS::InputManager::destroyInputSystem(mInputManager);
			mRenderWindow->destroy();
			delete mRoot;
		}
		inline float getWindowWidth() const { return mWindowWidth; }
		inline float getWindowHeight() const { return mWindowHeight; }

		// ��Ϸ����������, ��Ϸ״̬ʹ��
		inline Ogre::SceneManager *getGameSceneMgr() { return mGameSceneMgr; }
		// ��ȡOgre����Ⱦ����
		inline Ogre::RenderWindow* getRenderWindow() { return mRenderWindow; }


	private:
		DemoApp():mRenderWindow(0),mRoot(0),mGUISystem(0),mInputSystem(0),mWindowWidth(1.0f), mWindowHeight(1.0f),mLostFouse(false),mGameSceneMgr(0)
		{

		}
	
		Ogre::Root *mRoot;
		Ogre::RenderWindow *mRenderWindow;
		Demo::InputSystem *mInputSystem;
		Demo::GUISystem *mGUISystem;
		Demo::StateManager *mStateManager;
		Ogre::SceneManager		*mGameSceneMgr;	// ��Ϸʹ�õĳ���������

		

		float	mWindowWidth;		// ���ڿ��
		float	mWindowHeight;		// ���ڸ߶�
		bool	mLostFouse;			// �Ƿ�ʧ����
		bool	mIsShutDown;


	private:
		void setup();
		void createRoot();

		void defineResources();
		void setupRenderSystem();
		void createRenderWindow();
		void initializeResourceGroups();
		void setupScene();
		void setupInputSystem();
		void setupCEGUI();
		void createListener();
		void startRenderLoop();
		void createSceneMgr();

	protected:
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &arg );

		bool mouseMoved( const OIS::MouseEvent &arg );
		bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		// �����¼�
		void windowResized(Ogre::RenderWindow* rw);
		void windowClosed(Ogre::RenderWindow* rw) { shutDown(); }


		inline bool checkWindowBound(const OIS::MouseEvent &arg)
		{
			// ���������Ƕ�ռģʽ���������Ч�����Χ,����Ƴ�������ֱ�ӷ���
			if(	arg.state.X.abs<=0 || arg.state.X.abs >= mWindowWidth
				|| arg.state.Y.abs<=0 || arg.state.Y.abs>=mWindowHeight)
				return false;

			return true;
		}

		// ��Ϸ���������Դ��������
		void release();
	};

}
#endif