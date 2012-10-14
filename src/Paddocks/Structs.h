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
 * Structs.h
 *************************************************************************
 * Structs that will be reused throughout the program.
 *************************************************************************/


struct OgrePtrs
{
	// Pointer to the Ogre root.
	Ogre::Root *root;

	/* The memory pointed to by these pointers will be cleaned up by
	 * the Ogre Root and shouldn't be deleted manually. */
	Ogre::RenderWindow *window;
	Ogre::SceneManager *sceneManager;
	Ogre::SceneNode *rootSceneNode;
	Ogre::Camera *camera;
	Ogre::Viewport *viewport;

	// Initialise pointers
	OgrePtrs()
		: root(NULL), window(NULL), sceneManager(NULL),
		rootSceneNode(NULL), camera(NULL), viewport(NULL)
	{ }
};
