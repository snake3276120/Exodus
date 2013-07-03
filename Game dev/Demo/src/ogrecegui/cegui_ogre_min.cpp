#include <elements/CEGUIPushButton.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <RendererModules/Ogre/CEGUIOgreResourceProvider.h>
#include <RendererModules/Ogre/CEGUIOgreGeometryBuffer.h>
//regular mem handler
#include <CEGUI.h>
#include "ExampleApplication.h"



int degree=0;

CEGUI::MouseButton convertOgreButtonToCegui(int buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
    case OIS::MB_Right:
        return CEGUI::RightButton;
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
    default:
        return CEGUI::LeftButton;
    }
}


class GuiFrameListener:public ExampleFrameListener,public OIS::MouseListener,public OIS::KeyListener
{
private:
    CEGUI::Renderer *mGUIRenderer;
    bool mShoutdownRequested;
	bool mPressed;

public:
    GuiFrameListener(RenderWindow* win,Camera* cam,CEGUI::Renderer* renderer)
        :ExampleFrameListener(win,cam,true,true),mGUIRenderer(renderer),mShoutdownRequested(false),mPressed(false)
    {
        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);

//         CEGUI::WindowManager* wmgr=CEGUI::WindowManager::getSingletonPtr();
//         CEGUI::Window* quitBtn=wmgr->getWindow((CEGUI::utf8*)"QuitButton");
//         quitBtn->subscribeEvent( CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GuiFrameListener::quit,this) );//注册回调函数
   }

    void requestShoutdown()
    {
        mShoutdownRequested=true;
    }

    bool quit(const CEGUI::EventArgs &evt)
    {
		mPressed=true;
		//requestShoutdown();


        return true;
    }

    bool frameStarted(const FrameEvent& evt)
    {
        if(mMouse)
            mMouse->capture();
        if(mKeyboard) 
            mKeyboard->capture();

// 		if (mPressed && (++degree)%90!=1)
// 		{
// 			CEGUI::WindowManager* wmgr=CEGUI::WindowManager::getSingletonPtr();
// 			wmgr->getWindow((CEGUI::utf8*)"QuitButton")->setRotation(CEGUI::Vector3(0,0,degree));
// 		}
// 		else
// 		{
// 	
// 			mPressed=false;
// 		}
        return ExampleFrameListener::frameStarted(evt);
    }

    bool frameEnded(const FrameEvent& evt)
    {
		if(mShoutdownRequested)
            return false; //return false 程序退出？
        else
            return ExampleFrameListener::frameEnded(evt);
    }

    bool mouseMoved(const OIS::MouseEvent &evt)
    {
        CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel,evt.state.Y.rel);
        return true;
    }

    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
    {
        CEGUI::System::getSingleton().injectMouseButtonDown(convertOgreButtonToCegui(id));
        return true;
    }

    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id )
   {
        CEGUI::System::getSingleton().injectMouseButtonUp(convertOgreButtonToCegui(id));
        return true;
    }

    bool keyPressed(const OIS::KeyEvent &evt )
    {
        if(evt.key==OIS::KC_ESCAPE)
        {
            mShoutdownRequested=true;
            return true;
        }

        CEGUI::System::getSingleton().injectKeyDown(evt.key);
        CEGUI::System::getSingleton().injectChar(evt.text);

        return true;
    }

    bool keyReleased(const OIS::KeyEvent &evt )
   {
        CEGUI::System::getSingleton().injectKeyUp(evt.key);
        return true;
    }
};



//========================================================================
class TutorialApplication:public ExampleApplication
{
public:
    CEGUI::OgreRenderer* mGUIRenderer;
    CEGUI::Window* mEditorGuiSheet;

public:
    TutorialApplication()
        :mGUIRenderer(NULL),mEditorGuiSheet(NULL)
    {
    }

    ~TutorialApplication()
    {
        /*if(mEditorGuiSheet)
        {
            CEGUI::WindowManager::getSingleton().destroyWindow(mEditorGuiSheet);
        }*/


    }

protected:
    void createScene(void)
   {
        mGUIRenderer=&CEGUI::OgreRenderer::bootstrapSystem();

       //设置日志
        //Ogre::Log::setLogDetail(Ogre::LoggingLevel::LL_NORMAL);
       CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::LoggingLevel::Informative);
		
       //CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
       //CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
       //CEGUI::System::getSingleton().setDefaultFont("DejaVuSans-10");
	   //CEGUI::MouseCursor::getSingleton().setImage("TaharezLook","MouseMoveCursor");
       //mEditorGuiSheet=(CEGUI::Window*)CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","Sheet");
       //CEGUI::System::getSingleton().setGUISheet(mEditorGuiSheet);

	   // 加载GUI主题并设置默认参数
	   CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
	   CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");

	   CEGUI::System::getSingleton().setDefaultFont("BlueHighway-10");
	   CEGUI::System::getSingleton().setDefaultTooltip("WindowsLook/Tooltip");

	   mEditorGuiSheet = (CEGUI::Window*)CEGUI::WindowManager::getSingleton().loadWindowLayout("LogoUI.layout");
	   CEGUI::System::getSingleton().setGUISheet(mEditorGuiSheet);
	   mEditorGuiSheet->setVisible(true);
		


       //CEGUI::PushButton* quitBtn=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button",(CEGUI::utf8*)"QuitButton");
       // quitBtn->setPosition(CEGUI::UVector2(cegui_reldim(.9f), cegui_reldim(.8f)));
       // quitBtn->setSize(CEGUI::UVector2(cegui_reldim(.10f), cegui_reldim(.05f)));
       // quitBtn->setText((CEGUI::utf8*)"OK");
       // mEditorGuiSheet->addChildWindow(quitBtn);


        /*
        mEditorGuiSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"Tutorial Gui.xml");
        CEGUI::System::getSingleton().setGUISheet(mEditorGuiSheet);
        CEGUI::PushButton* quitButton=(CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"Quit");
        */

		
		
	
        //mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
        //mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);



   }

    void createFrameListener(void)
    {
        mFrameListener = new GuiFrameListener(mWindow, mCamera, mGUIRenderer);
        mRoot->addFrameListener(mFrameListener);
    }
};






//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32

//#define WIN32_LEAN_AND_MEAN
#include "windows.h"
//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
//#else
int main(int argc, char **argv)
//#endif
{
    // Create application object
    TutorialApplication app;
    try {
        app.go();
    } catch( Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occured: %s\n",e.getFullDescription().c_str());
#endif
    }

    return 0;
}