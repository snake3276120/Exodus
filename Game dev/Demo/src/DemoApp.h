
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

		// 游戏场景管理器, 游戏状态使用
		inline Ogre::SceneManager *getGameSceneMgr() { return mGameSceneMgr; }
		// 获取Ogre主渲染窗口
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
		Ogre::SceneManager		*mGameSceneMgr;	// 游戏使用的场景管理器

		

		float	mWindowWidth;		// 窗口宽度
		float	mWindowHeight;		// 窗口高度
		bool	mLostFouse;			// 是否丢失焦点
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

		// 窗口事件
		void windowResized(Ogre::RenderWindow* rw);
		void windowClosed(Ogre::RenderWindow* rw) { shutDown(); }


		inline bool checkWindowBound(const OIS::MouseEvent &arg)
		{
			// 检测如果鼠标非独占模式则检测鼠标有效点击范围,鼠标移出窗口则直接返回
			if(	arg.state.X.abs<=0 || arg.state.X.abs >= mWindowWidth
				|| arg.state.Y.abs<=0 || arg.state.Y.abs>=mWindowHeight)
				return false;

			return true;
		}

		// 游戏结束后对资源进行清理
		void release();
	};

}
#endif