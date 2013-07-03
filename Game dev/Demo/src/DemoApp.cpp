#include "DemoApp.h"
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

		void DemoApp::setup()
		{			
			mIsShutDown=false;
			createRoot();
			defineResources();

			createSceneMgr();


			setupRenderSystem();
			createRenderWindow();
			initializeResourceGroups();
			setupScene();

			setupInputSystem();
			setupCEGUI();

			createListener();
			mStateManager=StateManager::getSingletonPtr();
		}


		void DemoApp::createRoot()
		{
#ifdef _DEBUG
	mRoot = new Root("Plugins_d.cfg");
#else
	mRoot = new Root("Plugins.cfg");
#endif
			
		}

		void DemoApp::defineResources()
		{
			String secName, typeName, archName;
			ConfigFile cf;
			cf.load("resources.cfg");

			ConfigFile::SectionIterator seci = cf.getSectionIterator();
			while (seci.hasMoreElements())
			{
				secName = seci.peekNextKey();
				ConfigFile::SettingsMultiMap *settings = seci.getNext();
				ConfigFile::SettingsMultiMap::iterator i;
				for (i = settings->begin(); i != settings->end(); ++i)
				{
					typeName = i->first;
					archName = i->second;
					ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
				}
			}
		}

		void DemoApp::setupRenderSystem()
		{
			if (!mRoot->restoreConfig() && !mRoot->showConfigDialog())
				throw Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");

			//// Do not add this to the application
			//RenderSystem *rs = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
			//                                      // or use "OpenGL Rendering Subsystem"
			//mRoot->setRenderSystem(rs);
			//rs->setConfigOption("Full Screen", "No");
			//rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
		}

		void DemoApp::createRenderWindow()
		{
			mRenderWindow = mRoot->initialise(true, "Demo");
			
			// Do not add this to the application
			//mRoot->initialise(false);
			//HWND hWnd = 0; // Get the hWnd of the application!
			//NameValuePairList misc;
			//misc["externalWindowHandle"] = StringConverter::toString((int)hWnd);
			//mRenderWindow = mRoot->createRenderWindow("Demo", 800, 600, false, &misc);
		}

		void DemoApp::initializeResourceGroups()
		{
			TextureManager::getSingleton().setDefaultNumMipmaps(5);
			ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		}

		void DemoApp::setupScene()
		{
			SceneManager *mgr = mRoot->createSceneManager(ST_GENERIC, "Default SceneManager");
			//Camera *cam = mgr->createCamera("Camera");
			//Viewport *vp = mRoot->getAutoCreatedWindow()->addViewport(cam);

		}

		void DemoApp::setupInputSystem()
		{
			mInputSystem = InputSystem::getSingletonPtr();
			mInputSystem -> init(mRenderWindow, false);
		}

		void DemoApp::setupCEGUI()
		{
			mGUISystem = GUISystem::getSingletonPtr();
			
			if (mGUISystem -> init())
			{
				std::cout<<"done!!!!!"<<std::endl;
			}		

		}	
		void DemoApp::createListener()
		{
			//设置OIS回调函数
			mInputSystem->setKeyboardEventCallback(this);
			mInputSystem->setMouseEventCallback(this);

			mWindowWidth = float(mRenderWindow->getWidth());
			mWindowHeight = float(mRenderWindow->getHeight());

			// 注册窗口事件
			Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);
		}

		void DemoApp::startRenderLoop()
		{

			unsigned long timeLastFrame = 0;
			unsigned long timeCurrentFrame = 0;
			unsigned long timeSinceLastFrame = 0;

			Ogre::Timer *timer = mRoot->getTimer();

			mStateManager->pushState(MenuState::getSingletonPtr());

			while(!mIsShutDown)
			{
				timeCurrentFrame	= timer->getMilliseconds();
				timeSinceLastFrame	= timeCurrentFrame - timeLastFrame;
				timeLastFrame		= timeCurrentFrame;
									
				/** 如果当前渲染窗口没有丢失焦点则, 对其渲染, 否则更新*/
				if (!mLostFouse){
				mInputSystem->capture();

				mStateManager->update(timeSinceLastFrame);
				mRoot->renderOneFrame();
				mStateManager->updateAfterRender(timeSinceLastFrame);

				mGUISystem->update(timeSinceLastFrame);				
				}
				else
					::Sleep(100);

			::Sleep(20);
				Ogre::WindowEventUtilities::messagePump();
			}
			release();
		}


	//---------------------------------------------------------------------------------------------------------

		bool DemoApp::keyPressed( const OIS::KeyEvent &arg )
		{
			return mStateManager->keyPressed(arg);
		}	
		bool DemoApp::keyReleased( const OIS::KeyEvent &arg )
		{
			return mStateManager->keyReleased(arg);
		}

	
		bool DemoApp::mouseMoved( const OIS::MouseEvent &arg )
		{
			if (!checkWindowBound(arg))
				return true;

			// 时时更新CEGUI鼠标位置
			OIS::MouseState state = arg.state;

			mGUISystem->injectMouseMove(state.X.rel, state.Y.rel, state.X.abs, state.Y.abs);
			return mStateManager->mouseMoved(arg);
		}



		bool DemoApp::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if (!checkWindowBound(arg))
				return true;

			if (mGUISystem->injectMouseButtonDown(MB_OISToCEGUI(id)))
				return true;
			return mStateManager->mousePressed(arg, id);
		}



		bool DemoApp::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			if (!checkWindowBound(arg))
				return true;

			if (mGUISystem->injectMouseButtonUp(MB_OISToCEGUI(id)))
				return true;

			return mStateManager->mouseReleased(arg, id);
		}


		//---------------------------------------------------------------------------------------------------------

		void DemoApp::windowResized(Ogre::RenderWindow* rw)
		{
			mRenderWindow->windowMovedOrResized(); 

			mWindowWidth = mRenderWindow->getWidth();
			mWindowHeight = mRenderWindow->getHeight();

			// 注: 如果可以更改窗口大小,再更改大小之后需要调用此函数更新窗口
			mInputSystem->updateMouseExtents(mWindowWidth, mWindowHeight);

			// 通知CEGUI重绘
			mGUISystem->changeSize(mWindowWidth, mWindowHeight);

			// 通知State更改视图大小
			//todo
		}

		void DemoApp::release()
		{
			mStateManager->destroy();
			mInputSystem->destroy();
			mGUISystem->destroy();

			// 清除场景
			mGameSceneMgr->clearScene();

			mRoot->destroySceneManager(mGameSceneMgr);	
			mRenderWindow->destroy();
			mRoot->shutdown();
		}

		void DemoApp::createSceneMgr()
		{
			mGameSceneMgr = mRoot->createSceneManager(ST_GENERIC);

			//// 创建阴影
			//mGameSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
			//mGameSceneMgr->setShadowTextureSize(512);
			//mGameSceneMgr->setShadowColour(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
			//mGameSceneMgr->setShadowFarDistance(1000);
			//mGameSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));


		}

}
