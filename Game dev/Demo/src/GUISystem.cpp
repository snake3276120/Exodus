
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

	// �����������
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
		// ������layout���ļ��Ƿ����,û�м��������
		if(!getWindowManager()->isWindowPresent(windowName))
		{
			// �� .layout�ű��ļ���ȡһ��UI������ƣ���������õ�GUI��Դ���С�
			CEGUI::Window *editorGuiSheet = getWindowManager()->loadWindowLayout(windowName + ".layout");
			// ���������Ǹ���CEGUI��ʾ�ķ�UI���֡���Ȼ���ǿ�����ʱ������ʾ��UI���֡�
			getSingletonPtr()->getSystem()->setGUISheet(editorGuiSheet);
			editorGuiSheet->setVisible(true);

			flag = true;
		}
		else
		{	
			// ����Ѿ�������ֱ����ʾ
			CEGUI::Window *window = getWindowManager()->getWindow(windowName);
			getSingletonPtr()->getSystem()->setGUISheet(window);
			window->show();
		}

		return flag;
	}

	void GUISystem::changeSize(float width, float height) 
	{ 
		// ����CEGUI���ڴ�С, ͬ�������ʾ��Χ, �����CEGUI��귶Χ��ϵͳ��귶Χһ��
		mpGUIRenderer->setDisplaySize(CEGUI::Size(width, height)); 
		CEGUI::Size s = mpGUIRenderer->getDisplaySize();
		// ȷ��UI���»��Ʋ���ʾ
		//		˵��, �����ڴ�С�����ı��ʱ��, UI����ʧ, ����mpSystem->signalRedraw();
		// �����»��Ʋ���ʾUI
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