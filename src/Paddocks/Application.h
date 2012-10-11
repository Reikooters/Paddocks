#pragma once
/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * Application.h
 *************************************************************************/
#include "PaddocksFrameListener.h"


/*************************************************************************
 * class Application.
 *************************************************************************
 * Application class.
 *************************************************************************/
class Application
{
	// Variables
	std::auto_ptr<PaddocksFrameListener> frameListener;

	struct OgrePtrs
	{
		/* We use an auto_ptr for the Ogre Root so that it will always
		 * be cleaned up automatically. */
		std::auto_ptr<Ogre::Root> root;

		/* The memory pointed to by these pointers will be cleaned up by
		 * the Ogre Root and shouldn't be deleted manually. */
		Ogre::RenderWindow *window;
		Ogre::SceneManager *sceneManager;
		Ogre::SceneNode *rootSceneNode;
		Ogre::Camera *camera;
		Ogre::Viewport *viewport;

		// Initialise pointers
		OgrePtrs()
			: window(NULL), sceneManager(NULL), rootSceneNode(NULL),
			camera(NULL), viewport(NULL)
		{ }
	} ogrePtrs;


	// Functions
	bool initOgre();
	bool createScene();
	void mainLoop();
	void loadConfigIni();

public:
	int go();

	Application();
};
