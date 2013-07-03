#include "Ogre.h"
#include "ExampleApplication.h"

class BaseCube
{
private:
	Ogre::SceneManager *mSceneManager;
	String mMeterial[6];
	Ogre::SceneNode* mNode;
	ManualObject* mCubeObject;
public:
	BaseCube(const Vector3& position,const String&[6] meterial)
	{
		mSceneManager=;

		mCubeObject = mSceneMgr->createManualObject("cube");
		_cubeNode= mSceneMgr->getRootSceneNode()->createChildSceneNode();
		_cubeNode->attachObject(cube);
		_cubeNode->setPosition(20 ,20 ,20);
		
		// ����
		cube->begin("q", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z-10);	//0
		cube->textureCoord(1, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z-10);    //1
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z+10);    //2
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z+10);    //3
		cube->textureCoord(1, 1);
		cube->end();

		/// ����
		cube->begin("a", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z+10);    //3
		cube->textureCoord(1, 0);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z+10);    //7
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z-10);    //4
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z-10);	//0
		cube->textureCoord(1, 1);
		cube->end();

		/// ����
		cube->begin("z", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z-10);    //4
		cube->textureCoord(1, 0);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z+10);    //7
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z+10);    //6
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z-10);    //5
		cube->textureCoord(1, 1);
		cube->end();

		/// ����
		cube->begin("w", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z-10);    //1
		cube->textureCoord(1, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z-10);    //5
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z+10);    //6
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z+10);    //2
		cube->textureCoord(1, 1);
		cube->end();

		/// ǰ��
		cube->begin("s", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z-10);    //1
		cube->textureCoord(1, 0);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z-10);	//0
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z-10);    //4
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z-10);    //5
		cube->textureCoord(1, 1);
		cube->end();

		// ����
		cube->begin("x", RenderOperation::OT_TRIANGLE_FAN);
		cube->position( position.UNIT_X+10, position.UNIT_Y-10, position.UNIT_Z+10);    //2
		cube->textureCoord(0, 0);
		cube->position( position.UNIT_X+10, position.UNIT_Y+10, position.UNIT_Z+10);    //6
		cube->textureCoord(0, 1);
		cube->position( position.UNIT_X-10, position.UNIT_Y+10, position.UNIT_Z+10);    //7
		cube->textureCoord(1, 1);
		cube->position( position.UNIT_X-10, position.UNIT_Y-10, position.UNIT_Z+10);    //3
		cube->textureCoord(1, 0);
		cube->end();
	};
	~BaseCube();
}