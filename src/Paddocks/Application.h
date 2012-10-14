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
#include "ConfigIni.h"

// Forward declaration
class GameState;


/*************************************************************************
 * class Application.
 *************************************************************************
 * Application class.
 *************************************************************************/
class Application
{
	// Variables
	// -------------------------------------------------------------
	std::auto_ptr<PaddocksFrameListener> frameListener;
	std::auto_ptr<ConfigIni> configIni;

	Ogre::Timer timer;
	unsigned long lastTime;

	/* We use an auto_ptr for the Ogre Root so that it will always
	 * be cleaned up automatically. */
	std::auto_ptr<Ogre::Root> ogreRoot;

	// Struct used to store pointers to Ogre things
	OgrePtrs ogrePtrs;

	// The current state
	GameState* activeState;

	// The stack of pending states
	std::vector<GameState*> states;

	/* Whether or not the game is running. Setting this to false will
	 * exit the game. */
	bool running;


	// Functions
	// -------------------------------------------------------------
	// Sets working directory to executable's directory
	void setCurrentWorkingDirectory();

	// Initialises Ogre
	bool initOgre();

	// Sets up the scene
	bool createScene();

	// Main program loop
	void mainLoop();

	// Loads the confuration file
	void loadConfigIni();

public:
	// Starts the program doing it's thing.
	int go();

	// Constructor
	Application();
};
