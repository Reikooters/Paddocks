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
 * MainMenuState.h
 *************************************************************************/
#include "GameState.h"
#include "GUICanvas.h"


/*************************************************************************
 * class MainMenuState
 *************************************************************************
 * The MainMenuState is a specialisation of the GameState class that
 * loads and maintains everything specific to the main menu, such as
 * the GUI.
 *************************************************************************/
class MainMenuState : public GameState
{
	// Ogre pointers
	OgrePtrs ogrePtrs;

	// GUI
	std::auto_ptr<GUICanvas> guiCanvas;

	void createGUI();

public:
	MainMenuState(OgrePtrs &ogrePtrs);

	void enter();
	void update(const Ogre::Real deltaTimeSecs);
	void exit();
};
