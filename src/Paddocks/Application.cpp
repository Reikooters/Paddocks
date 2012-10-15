/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * Application.cpp
 *************************************************************************
 * This file contains the definitions for the functions declared in the
 * Application class. See Application.h for details on this class.
 *************************************************************************/
#include "Application.h"
#include "MainMenuState.h"


/*************************************************************************
 * Application::Application()
 *************************************************************************
 * Constructor. Initialises variables.
 *************************************************************************/
Application::Application()
	: lastTime(timer.getMilliseconds()), running(true)
{
	frameListener.reset(new PaddocksFrameListener());
}


/*************************************************************************
 * Application::~Application()
 *************************************************************************
 * Destructor. Performs cleanup.
 *************************************************************************/
Application::~Application()
{
	cleanupGameStates();
}


/*************************************************************************
 * Application::go()
 *************************************************************************
 * This function starts the program doing it's thing.
 * 
 * Returns: EXIT_SUCCESS if the program finished successfully, or some
 *          error code if it didn't.
 *************************************************************************/
int Application::go()
{
	// Set working directory to executable's directory
	setCurrentWorkingDirectory();

	// Load config.ini.
	loadConfigIni();

	// Initialise Ogre.
	if (!initOgre())
		return EXIT_FAILURE;

	createScene();

	// Create the Input Manager
	inputManager.reset(InputManager::getSingletonPtr());
	inputManager->initialise(ogrePtrs.window);

	// Create the Main Menu game state
	states.push_back(new MainMenuState(ogrePtrs, inputManager.get()));

	// Set it as the active state
	activeState = states.back();
	activeState->enter();

	// Start main program loop.
	mainLoop();

	// Program finished successfully.
	return EXIT_SUCCESS;
}


/*************************************************************************
 * Application::initOgre()
 *************************************************************************
 * Initialises Ogre - creates the Ogre Root, loads plugins and creates
 * the render window.
 * 
 * Returns: True if the initialisation was successful, false if not.
 *************************************************************************/
bool Application::initOgre()
{
	// STEP 1: Create the Ogre Root
	// ------------------------------------

	// This is the log filename we'll use
	Ogre::String logFilename = "Paddocks.log";

	/* Create the Ogre Root, telling it the log filename we want to use.
	 * We aren't loading the plugin list or config from file, so these
	 * are left blank. */
	ogreRoot.reset(new Ogre::Root("", "", logFilename));
	ogrePtrs.root = ogreRoot.get();
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_LOW);

	// STEP 2: Load plugins
	// ------------------------------------

	// Create a list of plugins we'll use. 
	{
		std::vector<Ogre::String> pluginNames;
		pluginNames.push_back("RenderSystem_GL");
		//pluginNames.push_back("RenderSystem_Direct3D9");
		pluginNames.push_back("Plugin_ParticleFX");
		pluginNames.push_back("Plugin_CgProgramManager");
		//pluginNames.push_back("Plugin_PCZSceneManager");
		//pluginNames.push_back("Plugin_OctreeZone");
		pluginNames.push_back("Plugin_OctreeSceneManager");
		//pluginNames.push_back("Plugin_BSPSceneManager");
		{
			// Load each plugin
			std::vector<Ogre::String>::iterator iter = pluginNames.begin();
			std::vector<Ogre::String>::iterator iterEnd = pluginNames.end();

			for( ; iter != iterEnd; iter++)
			{
				Ogre::String& pluginName = (*iter);

				/* Debug plugins have a _d at the end of the filename.
				 * So if we're in debug mode, append the _d. */
				if (OGRE_DEBUG_MODE)
					pluginName.append("_d");

				ogrePtrs.root->loadPlugin(pluginName);
			}
		}
	}

	// STEP 3: Select the RenderSystem
	// ------------------------------------
	{
		/* Get a list of the available renderers. The only one should be
		 * the one we loaded with the plugins earlier. */
		const Ogre::RenderSystemList& renderSystemList = ogrePtrs.root->getAvailableRenderers();

		// If there isn't only one, return an error.
		if( renderSystemList.size() != 1 )
		{
			Ogre::LogManager::getSingleton().logMessage("Error: Error selecting RenderSystem or no RenderSystem was loaded.");
			return false;
		}

		/* Assign the Root's RenderSystem as the first RenderSystem
		 * that was found. */
		ogrePtrs.root->setRenderSystem( renderSystemList[0] );
	}

	// STEP 4: Initialise the Root
	// ------------------------------------
	/* The Root can be initialised only once the RenderSystem has been
	 * selected. */
	{
		// We won't automatically create the render window.
		bool createAWindowAutomatically = false;

		// Name of the automatically generated window (not applicable).
		Ogre::String windowTitle = "";
		
		// Custom capabilities of the RenderSystem.
		Ogre::String customCapabilities = "";

		//ogrePtrs.root->initialise(createAWindowAutomatically, windowTitle, customCapabilities);
		ogrePtrs.root->initialise(createAWindowAutomatically, windowTitle);
	}

	// STEP 5: Create the render window
	// ------------------------------------
	{
		/* First we configure the window we are going to create.
		 * We pull the settings out from what was loaded from the
		 * config.ini, if it was loaded already. */
		ConfigIni::Configurations configs;
		if (configIni.get())
			configs = configIni->getConfigs();

		// Set the window title.
		Ogre::String windowTitle = "Paddocks";

		// Set some parameters.
		Ogre::NameValuePairList params;

		// Full screen anti-aliasing.
		params["FSAA"] = Ogre::StringConverter::toString(configs.fsaa);

		/* vertical synchronisation will prevent image tearing, but
		 * also will provide smooth framerate in windowed mode. */
		params["vsync"] = "true";

		// Make window non-resiable
		params["border"] = "fixed";

		// Create the render window, using our configurations.
		ogrePtrs.window = ogrePtrs.root->createRenderWindow(windowTitle, (unsigned int)configs.resolution.x, (unsigned int)configs.resolution.y, configs.fullscreen, &params);
	}

	// STEP 6: Assign the frame listener
	// ------------------------------------
	{
		ogrePtrs.root->addFrameListener(frameListener.get());
	}

	return true;
}


/*************************************************************************
 * Application::mainLoop()
 *************************************************************************
 * Main program loop.
 *************************************************************************/
void Application::mainLoop()
{
	/* Clear any events (clicks, etc) that were created while the
	 * window was being created. */
	ogrePtrs.root->clearEventTimes();

	// Main program loop.
	while (true)
	{
		Ogre::Real deltaTime = (timer.getMilliseconds()-lastTime)/1000.0f;
		lastTime = timer.getMilliseconds();

		if (activeState)
		{
			// Tell the active state to update
			activeState->update(deltaTime);

			/* We call messagePump() to let the messages between the application
			 * and the OS go through. For example, moving the window, closing
			 * the window, etc. If we don't call this then the user won't be
			 * able to click or use the window at all. */
			Ogre::WindowEventUtilities::messagePump();

			// Capture input
			InputManager::getSingletonPtr()->capture();

			/* Check if the window is closed. If it is, we stop the program
			 * running. */
			if (ogrePtrs.window->isClosed())
				running = false;

			// If window isn't closed, render a frame
			if (running)
				running = ogrePtrs.root->renderOneFrame();

			/* If the program is stopping, clean up GameStates and exit. */
			if (!running)
			{
				// Exit the active state
				activeState->exit();

				// Clean up GameStates
				cleanupGameStates();

				return;
			}
		}
	}
}


/*************************************************************************
 * Application::createScene()
 *************************************************************************
 * Sets up the scene.
 *************************************************************************/
bool Application::createScene()
{
	// Don't create the scene if the root hasn't been created.
	if (!ogrePtrs.root)
		return false;

	// If the scene has already been created, don't create it again.
	if (ogrePtrs.sceneManager)
		return false;

	/* Create a scene manager. We are using the ST_GENERIC type, which
	 * uses the OctreeSceneManager. This one will be the most efficient
	 * one for our purpose. */
	ogrePtrs.sceneManager = ogrePtrs.root->createSceneManager(Ogre::ST_GENERIC);
	ogrePtrs.sceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	// Get a pointer to the root scene node of the scene manager.
	ogrePtrs.rootSceneNode = ogrePtrs.sceneManager->getRootSceneNode();

	// Create a camera.
	ogrePtrs.camera = ogrePtrs.sceneManager->createCamera("Camera");

	/* Create the viewport. Since we want this to cover the whole screen,
	 * we don't specify the width, height, etc. parameters. */
	ogrePtrs.viewport = ogrePtrs.window->addViewport(ogrePtrs.camera);

	// Set the drawing background colour.
	ogrePtrs.viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 1.0f, 0.0f));

	// Alter the camera aspect ratio to match the viewport
	ogrePtrs.camera->setAspectRatio(
		Ogre::Real(ogrePtrs.viewport->getActualWidth()) / Ogre::Real(ogrePtrs.viewport->getActualHeight()));

	return true;
}


/*************************************************************************
 * Application::loadConfigIni()
 *************************************************************************
 * Load data from config.ini.
 *************************************************************************/
void Application::loadConfigIni()
{
	if (!configIni.get())
		configIni.reset(new ConfigIni("config.ini"));
}


/****************************************************************************
 * Application::setCurrentWorkingDirectory()
 ****************************************************************************
 * This function gets the IrrlichtDevice pointed to in the globals, and
 * changes the current working directory of its FileSystem to the directory
 * in which the executable file of the program is located.
 ****************************************************************************/
void Application::setCurrentWorkingDirectory() const
{
	// TODO: Find solutions to this for other platforms
#ifdef _MSC_VER
	int pathLen;
	int bufferLen = MAX_PATH;
	DWORD lastError = 0;
	wchar_t *pathBuffer = NULL;

	do
	{
		// Create a buffer for the program directory
		pathBuffer = new wchar_t[bufferLen + 1];
		memset(pathBuffer, '\0', sizeof(wchar_t) * (bufferLen + 1));

		// Put the full path + executable filename into the buffer
		pathLen = GetModuleFileNameW(NULL, pathBuffer, bufferLen);

		// Check if an error occurred
		lastError = GetLastError();

		if (lastError == ERROR_INSUFFICIENT_BUFFER)
		{
			// Free memory allocated for the buffer
			delete [] pathBuffer;
			pathBuffer = NULL;

			// Double the size of the buffer
			bufferLen *= 2;
		}
	}
	// Keep trying until GetModuleFileNameW() is successful
	while (lastError == ERROR_INSUFFICIENT_BUFFER);

	if (pathBuffer)
	{
		/* Backtrack from the end of the buffer, truncating off one character
		 * at a time, until the start of the filename is found, so that we are
		 * left with only the program path */
		for (int i = pathLen - 1; i >= 0; --i)
		{
			if (pathBuffer[i] == L'\\' || pathBuffer[i] == L'/')
				break;
			pathBuffer[i] = L'\0';
		}

		// Change working directory to point to this directory.
#ifdef _MSC_VER
		// Visual Studio uses _wchdir() from direct.h
		_wchdir(pathBuffer);
#else
		// Other platforms use wcs_chdir() from unistd.h
		wcs_chdir(pathBuffer);
#endif

		// Free memory allocated for the buffer
		delete [] pathBuffer;
	}
#endif
}


/*************************************************************************
 * Application::cleanupGameStates()
 *************************************************************************
 * Cleans up (deletes) all GameStates. Note that this function does not
 * call the current state's exit() function before deleting them all,
 * so that should be called first before this function if it is required.
 *************************************************************************/
void Application::cleanupGameStates()
{
	// Delete all GameStates
	while (states.size() > 0)
	{
		activeState = states.back();
		delete activeState;
		states.pop_back();
	}
	activeState = NULL;
}
