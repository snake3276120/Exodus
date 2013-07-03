#pragma once
#include <OIS.h>

namespace Demo
{
	// Êó±ê¼üÅÌ¼àÌıÆ÷
	class IKeyMouseListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		// Êó±ê,¼üÅÌÊÂ¼ş
		virtual bool keyPressed( const OIS::KeyEvent &e ){ return true; }
		virtual bool keyReleased( const OIS::KeyEvent &e ){ return true; }

		virtual bool mouseMoved(const OIS::MouseEvent &e){ return true; }
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
	};

}