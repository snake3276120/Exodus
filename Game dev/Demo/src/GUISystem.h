
#ifndef __GUISYSTEM_H__
#define __GUISYSTEM_H__

#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <RendererModules/Ogre/CEGUIOgreResourceProvider.h>
//#include <ScriptingModules/LuaScriptModule/CEGUILua.h>  
#include <Ogre.h>

#include "IFrameListener.h"
#include "SingletonT.h"
#include "Util.h"

namespace Demo{

	/**
		��OIS���ת����CEGUI���
		@buttonID	OIS���ö��
	*/
	CEGUI::MouseButton MB_OISToCEGUI(int buttonID);

	// �������
	enum CURSOR_TYPE
	{
		CURSOR_ON				= 0,		// ��ָ��
		CURSOR_FIRE				= 1,		// ������
		CURSOR_NORMAL			= 2,		// ��ͨ��
	};

	/**
		GUI����ϵͳ,����GUI����ļ���,�¼��͹���
	*/
	class GUISystem : public SingletonT <GUISystem> , public IFrameListener
	{
		SINGLETON_DEFINE(GUISystem)

	public:
		virtual ~GUISystem(){};

		// �ͷ���Դ
		void destroy();

		/**
			��ʼ��GUI,ֻ�ڵ�һ�ε�����Ч
			@rendweWindow		��Ⱦ����
			@sceneManager		GUI��ʾ�ĳ���
		*/
		bool init();


		// ��ȡCEGUI::System
		inline CEGUI::System* getSystem() { return mpSystem; }
		inline CEGUI::OgreRenderer* getGUIRender() { return mpGUIRenderer; }
		// ��ȡ��ǰGUI�ĸ�Window
		inline CEGUI::Window* getGUISheet() { return mpSystem->getGUISheet(); }
		
		// ע��CEGUI����¼�
		inline bool injectMouseButtonDown(CEGUI::MouseButton id) { return mpSystem->injectMouseButtonDown(id);}
		inline bool injectMouseButtonUp(CEGUI::MouseButton id) { return mpSystem->injectMouseButtonUp(id); }
		// ע��CEGUI����ƶ��¼�, ʱʱ�������λ��, ����Ƶ������, ������֮
		inline bool injectMouseMove(float xRel, float yRel, float xAbs, float yAbs)
		{
			//static CEGUI::MouseCursor* mouse = CEGUI::MouseCursor::getSingletonPtr();
			//mouse->setPosition(CEGUI::Point(xAbs, yAbs));
			mpSystem->injectMouseMove(xRel, yRel);
			return mpSystem->injectMousePosition(xAbs, yAbs);
		}

		/**
			�����ڸ��´�С�����
			@width	���Ĵ��ں���Ⱦ���ڵĿ��
			@height	���Ĵ��ں���Ⱦ���ڵĸ߶�
		*/
		void changeSize(float width, float height);

		 void update( float timeSinceLastFrame );

		/**
			ע��CEGUI�ؼ��¼�
			@windowName	Ҫע���¼��Ŀؼ�����
			@eventName		ע��Ŀؼ��¼�
			@subscriber			�¼�����ʱ�Ļص�����
		*/
		static void subscribeEvent(const CEGUI::String& windowName, 
									const CEGUI::String &eventName, 
									const CEGUI::Event::Subscriber &subscriber);

		// ��ȡGUI���ڹ�����
		static CEGUI::WindowManager* getWindowManager() { return CEGUI::WindowManager::getSingletonPtr(); }
		
		/**
			����WIndow�ؼ�
			@type	��������
			@name	��������, ����ȫ��Ψһ
		*/
		static CEGUI::Window* createWindow(const std::string &type, const std::string &name);
		
		/**
			��ȡWindow
			@name Ҫ��ȡ���ڿؼ�������
		*/
		static CEGUI::Window* getWindow(const std::string &windowName);

		// ��ָ�������趨����
		static void setProperty(const std::string& windowName, 
								const std::string& name, 
								const std::string& value);

		/**
			����ͼƬ����Imageset
			@name		������Imageset����, ȫ��Ψһ
			@filename	����Imageset��ͼƬ����
		*/
		static void createImageset(const std::string& name, const std::string& filename);

		/**
			����UI����,���غ�����Ϊ��ǰUI
				ע�� : ��֤�����ļ���Root������ͬ:Root name = Window, Window.layout
			���layoutδ�����򷵻�true, ���layout�Ѿ������򷵻�false
			@windowName	���ص�layout�ļ�����
		*/
		static bool loadWindow(const std::string &windowName);
		
		/**
			���ٴ���
			@windowName	Ҫ���ٵĴ��ڿؼ�������
		*/
		static void destoryWindow(const std::string &windowName);

		// ��ʾ/����GUI���
		static void showGUICursor(bool enable);
		// ���������ʽ
		static void setCursorType(CURSOR_TYPE cursor);




	private:
		GUISystem():mpSystem(0), mpGUIRenderer(0){};

	private:
		CEGUI::OgreRenderer			*mpGUIRenderer;
		CEGUI::System				*mpSystem;
		

	};


}

#endif