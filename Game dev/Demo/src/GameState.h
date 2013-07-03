#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__


#include "Ogre.h"
#include "OIS.h"

#include "State.h"
#include "SingletonT.h"


namespace Demo{
	/**
		��Ϸ״̬
	*/
	class GameState:public State, public SingletonT<GameState>
	{
		SINGLETON_DEFINE(GameState)

	public:
		~GameState();

		// ����״̬
		virtual void enter( void );
		// �˳�״̬
		virtual void exit( void );

		// ��ͣ״̬
		virtual void pause( void ){};
		// �ظ�״̬
		virtual void resume( void ){};

		// ����״̬
		virtual void update( float timeSinceLastFrame );
		// ���Ĵ��ڴ�С
		void changeSize(int width, int height);


		// OIS::KeyListener
		bool keyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );
		// OIS::MouseListener
		bool mouseMoved(const OIS::MouseEvent &e);
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

	protected:
		GameState();
		void createScene();
		void createCamera();
		void createLight();
		//void createUI();


		void createNewUnit();
		void wipeUnit();
		void moveNode (Ogre::Real timeSinceLastFrame,Ogre::SceneNode* node);


	protected:
		Ogre::SceneManager* mSceneManager;
		Ogre::Root* mRoot;
		Ogre::RenderWindow		*mRenderWindow;
		Ogre::Viewport					*mViewport;


		Ogre::SceneNode* mSinbadNode;
		Ogre::Entity* mSinbadEnt;

		std::vector<std::pair<std::string,Ogre::SceneNode*>> mSBNodeVec;
		std::vector<std::pair<std::string,Ogre::Entity*>> mSBEntVec;
		int mVecNodeNum;

		static const std::string mSBNodeName;
		


		Ogre::AnimationState* mAniState;
		Ogre::AnimationState* mAniStateTop;// �ϰ�������
		Ogre::AnimationState* mAniDance;


		Ogre::Camera* mCamera;
		Ogre::Real mCamMovementSpeed;
		Ogre::Real mCamPitchSpeed;
		Ogre::Vector3 mCamMoveDirection;
		static const float mCoordDelta;


		Ogre::Vector3 SinbadTranslate;
		Ogre::Real SinbadRotation;

		Ogre::Real mWalkingSpeed;
		bool newUnitCreated;
		bool unitWiped;

		size_t walking;





	};


}


#endif