#pragma once

#include <OIS.h>

namespace Demo
{
	// 帧监听器
	class IFrameListener
	{
	public:
		/**
			状态更新, 每一帧调用
			@timeSinceLastFrame	自上一帧的时间(基于s)
		*/
		virtual void update( float timeSinceLastFrame ) = 0;

		/**
			渲染后更新状态, 每一帧调用
			@timeSinceLastFrame	自上一帧的时间(基于s)
		*/
		virtual void updateAfterRender( float timeSinceLastFrame) {}
	};


}