
#include "GUISystem.h"
#include "Util.h"


namespace Demo{

	CEGUI::MouseButton MB_OISToCEGUI(int buttonID)
	{
		switch (buttonID)
		{
		case 0: return CEGUI::LeftButton;
		case 1: return CEGUI::RightButton;
		case 2:	return CEGUI::MiddleButton;
		case 3: return CEGUI::X1Button;
		default: return CEGUI::LeftButton;
		}
	}

	// 鼠标类型名称
	const std::string MOUSE_CURSOR[3] = {"CursorOn", "CursorFire", "CursorNormal"};

	//---------------------------------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------------------------------

	void GUISystem::destroy()
	{

	}


	//---------------------------------------------------------------------------------------------------------

	bool GUISystem::init()
	{


			mpGUIRenderer=&CEGUI::OgreRenderer::bootstrapSystem();
			mpSystem = CEGUI::System::getSingletonPtr();


			CEGUI::SchemeManager::getSingleton().create("VanillaSkin.scheme");
			CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
			CEGUI::SchemeManager::getSingleton().create("WindowsLook.scheme");

			mpSystem->setDefaultFont("BlueHighway-10");
			mpSystem->setDefaultTooltip("WindowsLook/Tooltip");



#ifdef _DEBUG
			CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
#endif

 			setCursorType(CURSOR_NORMAL);
			showGUICursor(true);
			return true;

	}

	//---------------------------------------------------------------------------------------------------------

	CEGUI::Window* GUISystem::getWindow(const std::string &windowName)
	{
		return getWindowManager()->getWindow(windowName);
	}

	//---------------------------------------------------------------------------------------------------------

	CEGUI::Window* GUISystem::createWindow(const std::string &type, const std::string &name)
	{
		return getWindowManager()->createWindow(type, name);
	}

	//---------------------------------------------------------------------------------------------------------

	bool GUISystem::loadWindow(const std::string &windowName)
	{
		bool flag = false;
		// 检测给定layout的文件是否加载,没有加载则加载
		if(!getWindowManager()->isWindowPresent(windowName))
		{
			// 从 .layout脚本文件读取一个UI布局设计，并将其放置到GUI资源组中。
			CEGUI::Window *editorGuiSheet = getWindowManager()->loadWindowLayout(windowName + ".layout");
			// 接下来我们告诉CEGUI显示哪份UI布局。当然我们可以随时更换显示的UI布局。
			getSingletonPtr()->getSystem()->setGUISheet(editorGuiSheet);
			editorGuiSheet->setVisible(true);

			flag = true;
		}
		else
		{	
			// 如果已经加载则直接显示
			CEGUI::Window *window = getWindowManager()->getWindow(windowName);
			getSingletonPtr()->getSystem()->setGUISheet(window);
			window->show();
		}

		return flag;
	}

	void GUISystem::changeSize(float width, float height) 
	{ 
		// 更新CEGUI窗口大小, 同步鼠标显示范围, 来解决CEGUI鼠标范围与系统鼠标范围一致
		mpGUIRenderer->setDisplaySize(CEGUI::Size(width, height)); 
		CEGUI::Size s = mpGUIRenderer->getDisplaySize();
		// 确保UI重新绘制并显示
		//		说明, 当窗口大小发生改变的时候, UI会消失, 调用mpSystem->signalRedraw();
		// 来重新绘制并显示UI
		mpSystem->signalRedraw();
		mpSystem->notifyDisplaySizeChanged(CEGUI::Size(width, height));
		std::cout<<"[width:"<<s.d_height<<",height:"<<s.d_width<<"]";
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::update( float timeSinceLastFrame )
	{
		mpSystem->injectTimePulse(timeSinceLastFrame / 1000);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::showGUICursor(bool enable)
	{
		if (enable)
			CEGUI::MouseCursor::getSingletonPtr()->show();
		else
			CEGUI::MouseCursor::getSingletonPtr()->hide();

		::ShowCursor(!enable);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::setCursorType(CURSOR_TYPE cursor)
	{
		//CEGUI::MouseCursor::getSingletonPtr()->setImage("NormalImageSet", MOUSE_CURSOR[cursor]);
		getSingletonPtr()->mpSystem->setDefaultMouseCursor("NormalImageSet", MOUSE_CURSOR[cursor]);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::destoryWindow(const std::string &windowName)
	{
		getWindowManager()->destroyWindow(windowName);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::createImageset(const std::string& name, const std::string& filename)
	{
		CEGUI::ImagesetManager::getSingleton().createFromImageFile(name, filename);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::subscribeEvent(const CEGUI::String& windowName, 
														const CEGUI::String &eventName, 
														const CEGUI::Event::Subscriber &subscriber)
	{
		CEGUI::WindowManager::getSingleton().getWindow(CEGUI::String(windowName))
			->subscribeEvent(eventName,subscriber);
	}

	//---------------------------------------------------------------------------------------------------------

	void GUISystem::setProperty(const std::string &windowName, const std::string& PropName, 
												   const std::string& PropValue)
	{
		getWindow(windowName)->setProperty(PropName, PropValue);
	}

	//---------------------------------------------------------------------------------------------------------

}