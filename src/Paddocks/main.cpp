/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * main.cpp
 *************************************************************************
 * Contains the entry point of the program.
 *************************************************************************/
#include "Application.h"


/* Hide console window on Windows release builds. Otherwise, if not on
 * Windows, or if creating a debug build (on any platform), use the
 * console. */
#ifndef _DEBUG
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char **argv)
#endif
#else
	int main(int argc, char **argv)
#endif
{
	// Initialise singletons, and create an auto_ptr for each
	Application *appPtr = Application::getSingletonPtr();
	InputManager *inpPtr = InputManager::getSingletonPtr();

	std::auto_ptr<Application> app(appPtr);
	std::auto_ptr<InputManager> inp(inpPtr);

	int result = EXIT_FAILURE;

	try
	{
		result = app->go();
	}
	// Catch any exceptions and display the details.
	catch(std::exception &e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n", e.what());
#endif
	}

	return result;
}
