//辅助工具类
#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include <Ogre.h>
//#include "Config.h"

namespace Demo{

	// 安全删除指针宏定义
	#define SAFE_DELETE(point) \
	{											\
		if (point)							\
			delete point;					\
		point = 0;							\
	}

	//// 加载资源类型
	//enum ResType
	//{
	//	FILE_TYPE,	// 加载普通目录下资源
	//	ZIP_TYPE,		// 加载zip文件内资源
	//};


//	/**
//		辅助工具类
//	*/
//	class Util
//	{
//	public:
//
//		/**
//			将字符串数字转换成浮点类型
//			@num 要转换的数字字符串
//		*/
//		inline static float toFloat(const std::string&num) 
//		{ 
//			return atof(num.c_str());
//		}
//
//		/**
//			将浮点类型转换成字符串形式
//			@num 要转换的数值
//		*/
//		inline static std::string toString(float num)
//		{
//			return Ogre::StringConverter::toString(num);
//		}
//
//		// 随机真假值
//		inline static bool randomBool() { return ((int)Ogre::Math::RangeRandom(0, 2)) == 1; }
//		
//		// 随机范围数
//		inline static float randomRange(float low, float heigh) { return Ogre::Math::RangeRandom(low, heigh); }
//
//		// 日志记录
//		static void log(const std::string &msg)
//		{
//			Ogre::LogManager::getSingletonPtr()->getDefaultLog()->logMessage(msg);
//		}
//
//		/**
//			对给定数字进行格式化
//			exp: format(1234, 6) = 001234
//			@num	要格式化的数字
//			@digit	要格式化的位数
//		*/
//		static std::string format(int num, int digit);
//
//		// 将字符串两边的空白消除
//		static std::string trim(const std::string &line);
//
//		// 不考虑大小写比较字符串相等否
//		static bool equal(const std::string &left, const std::string &right);
//
//		/**
//			手动加载资源
//			@path 加载资源的路径
//			@type 资源类型, 可以是FILE_TYPE(目录形式) 或 ZIP_TYPE(.zip文件形式)
//			@groupName	资源所在的资源组
//			@load	是否立刻加载
//			@recursive	是否对子文件夹递归搜索
//		*/
//		static void loadResouse(const std::string &path, ResType type, 
//													 const std::string &groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
//													 bool load = true, bool recursive = false);
//
//		/**
//			卸载资源
//			@groupName	要卸载的资源组
//		*/
//		static void unloadResouse(const std::string &GroupName);
//
//		/**
//			解析.scene文件并生成对应场景,调用前需要保证使用loadResouse()加载.scene相关资源
//			@sceneName		.scene文件名称
//			@groupName		.scene资源所在资源组
//			@yourSceneMgr	场景管理器
//			@pAttachNode		创建场景的根节点, 如果为NULL则以root SceneNode来构建
//		*/
//		static void parseDotScene(const std::string &sceneName, 	Ogre::SceneManager *sceneMgr,  
//												const std::string &groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//												Ogre::SceneNode *rootNode = NULL);
//	};
//}
}
#endif