#pragma once
#include <OIS.h>

namespace Demo
{
	// �����̼�����
	class IKeyMouseListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		// ���,�����¼�
		virtual bool keyPressed( const OIS::KeyEvent &e ){ return true; }
		virtual bool keyReleased( const OIS::KeyEvent &e ){ return true; }

		virtual bool mouseMoved(const OIS::MouseEvent &e){ return true; }
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){ return true; }
	};

}