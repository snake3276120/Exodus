//����������
#pragma once
#ifndef __UTIL_H__
#define __UTIL_H__

#include <Ogre.h>
//#include "Config.h"

namespace Demo{

	// ��ȫɾ��ָ��궨��
	#define SAFE_DELETE(point) \
	{											\
		if (point)							\
			delete point;					\
		point = 0;							\
	}

	//// ������Դ����
	//enum ResType
	//{
	//	FILE_TYPE,	// ������ͨĿ¼����Դ
	//	ZIP_TYPE,		// ����zip�ļ�����Դ
	//};


//	/**
//		����������
//	*/
//	class Util
//	{
//	public:
//
//		/**
//			���ַ�������ת���ɸ�������
//			@num Ҫת���������ַ���
//		*/
//		inline static float toFloat(const std::string&num) 
//		{ 
//			return atof(num.c_str());
//		}
//
//		/**
//			����������ת�����ַ�����ʽ
//			@num Ҫת������ֵ
//		*/
//		inline static std::string toString(float num)
//		{
//			return Ogre::StringConverter::toString(num);
//		}
//
//		// ������ֵ
//		inline static bool randomBool() { return ((int)Ogre::Math::RangeRandom(0, 2)) == 1; }
//		
//		// �����Χ��
//		inline static float randomRange(float low, float heigh) { return Ogre::Math::RangeRandom(low, heigh); }
//
//		// ��־��¼
//		static void log(const std::string &msg)
//		{
//			Ogre::LogManager::getSingletonPtr()->getDefaultLog()->logMessage(msg);
//		}
//
//		/**
//			�Ը������ֽ��и�ʽ��
//			exp: format(1234, 6) = 001234
//			@num	Ҫ��ʽ��������
//			@digit	Ҫ��ʽ����λ��
//		*/
//		static std::string format(int num, int digit);
//
//		// ���ַ������ߵĿհ�����
//		static std::string trim(const std::string &line);
//
//		// �����Ǵ�Сд�Ƚ��ַ�����ȷ�
//		static bool equal(const std::string &left, const std::string &right);
//
//		/**
//			�ֶ�������Դ
//			@path ������Դ��·��
//			@type ��Դ����, ������FILE_TYPE(Ŀ¼��ʽ) �� ZIP_TYPE(.zip�ļ���ʽ)
//			@groupName	��Դ���ڵ���Դ��
//			@load	�Ƿ����̼���
//			@recursive	�Ƿ�����ļ��еݹ�����
//		*/
//		static void loadResouse(const std::string &path, ResType type, 
//													 const std::string &groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
//													 bool load = true, bool recursive = false);
//
//		/**
//			ж����Դ
//			@groupName	Ҫж�ص���Դ��
//		*/
//		static void unloadResouse(const std::string &GroupName);
//
//		/**
//			����.scene�ļ������ɶ�Ӧ����,����ǰ��Ҫ��֤ʹ��loadResouse()����.scene�����Դ
//			@sceneName		.scene�ļ�����
//			@groupName		.scene��Դ������Դ��
//			@yourSceneMgr	����������
//			@pAttachNode		���������ĸ��ڵ�, ���ΪNULL����root SceneNode������
//		*/
//		static void parseDotScene(const std::string &sceneName, 	Ogre::SceneManager *sceneMgr,  
//												const std::string &groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//												Ogre::SceneNode *rootNode = NULL);
//	};
//}
}
#endif