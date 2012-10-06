/*************************************************************************
 * Application.cpp
 *************************************************************************
 * Application class.
 *************************************************************************/
#include "Application.h"


/*************************************************************************
 * Application::Application()
 *************************************************************************
 * Constructor. Initialises variables.
 *************************************************************************/
Application::Application()
{

}


/*************************************************************************
 * Application::~Application()
 *************************************************************************
 * Destructor.
 *************************************************************************/
Application::~Application()
{

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
		std::cout << renderSystemList.size() << std::endl;

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

	return true;
}


/*************************************************************************
 * Application::mainLoop()
 *************************************************************************
 * Main render loop.
 *************************************************************************/
void Application::mainLoop()
{
	while (!ogrePtrs.window->isClosed())
	{
		/* We call messagePump() to let the messages between the application
		 * and the OS go through. For example, moving the window, closing
		 * the window, etc. If we don't call this then the user won't be
		 * able to click or use the window at all. */
		Ogre::WindowEventUtilities::messagePump();
	}
}
