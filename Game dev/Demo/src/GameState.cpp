#include "GameState.h"
#include "DemoApp.h"


namespace Demo{

	const std::string GameState::mSBNodeName("sbNode");
	float const GameState::mCoordDelta = 20.0f;



	//////////////////////////////////////////////////////////////////////////


	GameState::GameState()
		:mCamMovementSpeed( 80 ),
		mCamPitchSpeed( 0.3f ),
		mCamMoveDirection( Ogre::Vector3::ZERO ), 
		mSceneManager( NULL ),
		mRoot( NULL ),
		mSinbadNode( NULL ),
		mSinbadEnt( NULL ),
		mVecNodeNum( 0 ),
		mWalkingSpeed( 10.0f )
	{

	}

	GameState::~GameState()
	{

	}


	void GameState::enter( void )
	{
		mRoot = Ogre::Root::getSingletonPtr();
		mSceneManager	= DemoApp::getSingletonPtr()->getGameSceneMgr();
		mRenderWindow	= DemoApp::getSingletonPtr()->getRenderWindow();
	
		createCamera();
		createScene();
		createLight();
	}


	void GameState::exit( void )
	{
		mSceneManager->clearScene();
		mSceneManager->destroyAllCameras();
		mSceneManager->destroyAllLights();
		mRenderWindow->removeAllViewports();
	}

	void GameState::createScene()
	{
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
		Ogre::MeshManager::getSingleton().createPlane("plane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,1500,1500,200,200,true,1,5,5,Ogre::Vector3::UNIT_Z);

		Ogre::Entity* ground = mSceneManager->createEntity("LightPlaneEntity", "plane");
		mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
		ground->setMaterialName("Examples/BeachStones");


		mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

		mSinbadNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
		mSinbadEnt = mSceneManager->createEntity("sb1","Sinbad.mesh");
		mSinbadNode->attachObject(mSinbadEnt);



		mAniState = mSinbadEnt->getAnimationState("RunBase");
		mAniState->setLoop(false);
		mAniStateTop = mSinbadEnt->getAnimationState("RunTop");
		mAniStateTop->setLoop(false);
		mAniDance = mSinbadEnt->getAnimationState("Dance");
		mAniDance->setLoop(true);
	}

	void GameState::createNewUnit()
	{
		std::string nodenumber;
		std::string nodename;
		std::stringstream nodestream;

		nodestream << mVecNodeNum;
		nodenumber = nodestream.str();
		nodename = mSBNodeName + nodenumber;

		float dacord = mCoordDelta * (mVecNodeNum + 1);	
		mSBNodeVec.push_back(std::make_pair(nodename,mSceneManager->getRootSceneNode()->createChildSceneNode(nodename)));
		mSBEntVec.push_back(std::make_pair(nodename,mSceneManager->createEntity("Sinbad.mesh")));

		mSBNodeVec.back().second->attachObject(mSBEntVec.back().second);
		mSBNodeVec.back().second->setPosition (dacord,0.0,dacord);
		mVecNodeNum++;
	}

	void GameState::wipeUnit()
	{
		if (mSBNodeVec.size() > 0)
		{
			mSBNodeVec[0].second->detachAllObjects(); 
			mSceneManager->getRootSceneNode()->removeAndDestroyChild(mSBNodeVec[0].first);

			if (!mSBEntVec[0].second->isAttached())
			{
				mSceneManager->destroyEntity(mSBEntVec[0].second);
			}


			mSBEntVec.erase (mSBEntVec.begin());
			mSBNodeVec.erase (mSBNodeVec.begin());

			std::cout<<"SB NODE SIEZ IS "<<mSBNodeVec.size()<<std::endl;
		}
	}

	void GameState::createCamera()
	{
		mCamera = mSceneManager->createCamera("Camera");
		mCamera->setPosition(Ogre::Vector3(0,100,150));
		mCamera->lookAt(Ogre::Vector3(0,0,0));
		mCamera->setNearClipDistance(5);
		mViewport = mRenderWindow->addViewport(mCamera);

		mViewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
		mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth())/Ogre::Real(mViewport->getActualHeight()));
	}

	void GameState::createLight()
	{
		Ogre::Light* light = mSceneManager->createLight("Light1");
		light->setType(Ogre::Light::LT_DIRECTIONAL);
		light->setDirection(Ogre::Vector3(1,-1,0));

		// 下面那句话不知道为啥一加就有问题，放的地方不对么？
		//
	}

	void GameState::update( float timeSinceLastFrame )
	{
		mAniState->addTime(timeSinceLastFrame/1000);
		mAniStateTop->addTime(timeSinceLastFrame/1000);
		mAniDance->addTime(timeSinceLastFrame/1000);

		if(walking > 0)
		{
			mAniState->setEnabled(true);
			mAniStateTop->setEnabled(true);
			mAniDance->setEnabled(false);
			if(mAniState->hasEnded())
			{
				mAniState->setTimePosition(0.0f);
			}
			if(mAniStateTop->hasEnded())
			{
				mAniStateTop->setTimePosition(0.0f);
			}
		}else{
			mAniState->setTimePosition(0.0f);
			mAniState->setEnabled(false);
			mAniStateTop->setTimePosition(0.0f);
			mAniStateTop->setEnabled(false);
			mAniDance->setEnabled(true);
		}
		//Temp Cam Function Calls
		//	_Cam->pitch(Ogre::Radian(rotY));
		mCamera->move(mCamMoveDirection * timeSinceLastFrame / 1000 * mCamMovementSpeed);

		moveNode (timeSinceLastFrame / 1000, mSinbadNode);
	}



	bool GameState::keyReleased( const OIS::KeyEvent &e )
	{
		// TODO:
		// 被拾取（被选中实体）体列表的KeyPressed事件，而不是像现在这样的对单个物体的处理
		switch (e.key)
		{
		case OIS::KC_UP :
		case OIS::KC_DOWN :
			SinbadTranslate.z = 0;
			--walking;
			break;
		case OIS::KC_LEFT :
		case OIS::KC_RIGHT :
			SinbadTranslate.x = 0;
			--walking;
			break;
		case OIS::KC_W :
		case OIS::KC_S :
			mCamMoveDirection.z = 0;
			break;
		case OIS::KC_A :
		case OIS::KC_D :
			mCamMoveDirection.x = 0;
			break;
		case OIS::KC_R :	
			newUnitCreated = false;
			break;
		case OIS::KC_E :
			unitWiped = false;
			break;
		case OIS::KC_T :
			break;
		default:
			break;
		}

		return true;
	}

	bool GameState::keyPressed( const OIS::KeyEvent &e )
	{
		// TODO:
		// 被拾取（被选中实体）体列表的KeyPressed事件，而不是像现在这样的对单个物体的处理

		switch (e.key)
		{
		case OIS::KC_ESCAPE:
			changeState(MenuState::getSingletonPtr());
			break;
		case OIS::KC_UP :
			SinbadTranslate.z = -1;
			SinbadRotation = 3.14f;
			++walking;
			break;
		case OIS::KC_DOWN :
			SinbadTranslate.z = 1;
			SinbadRotation = 0.0f;
			++walking;
			break;
		case OIS::KC_LEFT :
			SinbadTranslate.x = -1;
			SinbadRotation = -1.57f;
			++walking;
			break;
		case OIS::KC_RIGHT :
			SinbadTranslate.x = 1;
			SinbadRotation = 1.57f;
			++walking;
			break;
		case OIS::KC_W :
			mCamMoveDirection.z = -1;
			break;
		case OIS::KC_S :
			mCamMoveDirection.z = 1;
			break;
		case OIS::KC_A :
			mCamMoveDirection.x = -1;
			break;
		case OIS::KC_D :
			mCamMoveDirection.x = 1;
			break;
		case OIS::KC_R :
			//Manual Debounce
			if (!newUnitCreated) {
				newUnitCreated = true;
				createNewUnit();
			}
			break;
		case OIS::KC_E :
			if (!unitWiped) {
				unitWiped = true;
				wipeUnit();
			}
			break;
		case OIS::KC_T :
			//		m_App->count = 0;
			break;
		default:
			break;
		}

		return true;
	}

	bool GameState::mouseMoved( const OIS::MouseEvent &e )
	{
		if(e.state.X.abs<=(float)e.state.width/10.0)
			mCamMoveDirection.x = -1;
		else if(e.state.X.abs<=(float)e.state.width/5.0)
			mCamMoveDirection.x = -0.5;
		else if(e.state.X.abs>=(float)e.state.width*9.0/10.0)
			mCamMoveDirection.x = 1;
		else if(e.state.X.abs>=(float)e.state.width*4.0/5.0)
			mCamMoveDirection.x = 0.5;
		else 
			mCamMoveDirection.x = 0;

		if(e.state.Y.abs<=(float)e.state.height/10.0)
			mCamMoveDirection.z = -1;
		else if(e.state.Y.abs<=(float)e.state.height/5.0)
			mCamMoveDirection.z = -0.5;
		else if((float)e.state.Y.abs>=e.state.height*9.0/10.0)
			mCamMoveDirection.z = 1;
		else if((float)e.state.Y.abs>=e.state.height*4.0/5.0)
			mCamMoveDirection.z = 0.5;
		else 
			mCamMoveDirection.z = 0;

		return true;
	}

	bool GameState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
	{
		return true;
	}

	bool GameState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
	{
		return true;
	}

	void GameState::changeSize( int width, int height )
	{
		// 更改Viewport
		Ogre::Viewport *vp = mCamera->getViewport();
		mCamera->setAspectRatio((Ogre::Real)(vp->getActualWidth()) / (Ogre::Real)(vp->getActualHeight()));
	}

	void GameState::moveNode( Ogre::Real timeSinceLastFrame,Ogre::SceneNode* node )
	{
		if (SinbadTranslate == Ogre::Vector3::ZERO) 
			return;
		if (abs(SinbadTranslate.x) + abs(SinbadTranslate.z) == 2) 
			node->translate(0.707f * SinbadTranslate * timeSinceLastFrame * mWalkingSpeed);
		else
			node->translate(SinbadTranslate * timeSinceLastFrame * mWalkingSpeed);


		node->resetOrientation();
		node->yaw(Ogre::Radian(SinbadRotation));
	}





}