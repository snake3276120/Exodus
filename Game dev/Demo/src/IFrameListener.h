#pragma once

#include <OIS.h>

namespace Demo
{
	// ֡������
	class IFrameListener
	{
	public:
		/**
			״̬����, ÿһ֡����
			@timeSinceLastFrame	����һ֡��ʱ��(����s)
		*/
		virtual void update( float timeSinceLastFrame ) = 0;

		/**
			��Ⱦ�����״̬, ÿһ֡����
			@timeSinceLastFrame	����һ֡��ʱ��(����s)
		*/
		virtual void updateAfterRender( float timeSinceLastFrame) {}
	};


}