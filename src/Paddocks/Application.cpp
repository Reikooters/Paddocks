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


/*************************************************************************
 * Application::Application()
 *************************************************************************
 * Constructor. Initialises variables.
 *************************************************************************/
Application::Application()
{
	frameListener.reset(new PaddocksFrameListener());
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
	// Load config.ini.
	loadConfigIni();

	// Initialise Ogre.
	if (!initOgre())
		return EXIT_FAILURE;

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
	//std::auto_ptr<Ogre::Root> root(
	//	new Ogre::Root("", "", logFilename));
	ogrePtrs.root.reset(new Ogre::Root("", "", logFilename));

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

		ogrePtrs.root->initialise(createAWindowAutomatically, windowTitle, customCapabilities);
	}

	// STEP 5: Create the render window
	// ------------------------------------
	{
		// First we configure the window we are going to create.

		// Set the window title.
		Ogre::String windowTitle = "Paddocks";

		// Window size.
		unsigned int width = 800;
		unsigned int height = 600;

		// Use windowed mode
		bool fullscreen = false; 

		// Set some parameters.
		Ogre::NameValuePairList params;

		// Full screen anti-aliasing.
		params["FSAA"] = "0";

		/* vertical synchronisation will prevent image tearing, but
		 * also will provide smooth framerate in windowed mode. */
		params["vsync"] = "true";

		// Create the render window
		ogrePtrs.window = ogrePtrs.root->createRenderWindow(windowTitle, width, height, fullscreen, &params);
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
		/* We call messagePump() to let the messages between the application
		 * and the OS go through. For example, moving the window, closing
		 * the window, etc. If we don't call this then the user won't be
		 * able to click or use the window at all. */
		Ogre::WindowEventUtilities::messagePump();

		// Stop rendering when the window is closed.
		if (ogrePtrs.window->isClosed())
			return;

		// Or when renderOneFrame() returns false.
		if (!ogrePtrs.root->renderOneFrame())
			return;
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
	if (!ogrePtrs.root.get())
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
	ogrePtrs.viewport->setBackgroundColour(Ogre::ColourValue(1.0f, 0.0f, 1.0f));

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
	Ogre::ConfigFile *config = new Ogre::ConfigFile();
	config->load("config.ini");

	Ogre::String fullscreen = config->getSetting("fullscreen", Ogre::StringUtil::BLANK, "false");
	MessageBoxA(NULL, fullscreen.c_str(), "Full Screen", 0);

	Ogre::String fsaa = config->getSetting("fsaa", Ogre::StringUtil::BLANK, "0");
	MessageBoxA(NULL, fsaa.c_str(), "FSAA", 0);

	Ogre::String width = config->getSetting("width", Ogre::StringUtil::BLANK, "800");
	MessageBoxA(NULL, width.c_str(), "Width", 0);

	Ogre::String height = config->getSetting("height", Ogre::StringUtil::BLANK, "600");
	MessageBoxA(NULL, height.c_str(), "Height", 0);
}
