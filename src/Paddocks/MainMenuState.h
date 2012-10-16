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

// Forward declaration
class InputManager;


/*************************************************************************
 * class MainMenuState
 *************************************************************************
 * The MainMenuState is a specialisation of the GameState class that
 * loads and maintains everything specific to the main menu, such as
 * the GUI.
 *************************************************************************/
class MainMenuState : public GameState
{
	// Variables
	// -------------------------------------------------------------
	// Ogre pointers
	OgrePtrs ogrePtrs;
	InputManager *inputManager;

	// GUI
	std::auto_ptr<GUICanvas> guiCanvas;
	std::map<Ogre::String, GUIElement*> guiElements;
	bool boolOpenExitConfirmation;
	bool boolCloseExitConfirmation;

	// Functions
	// -------------------------------------------------------------
	// GUI
	void createGUI();
	void runGUISteps();
	// Bindings
	void startGameClicked();
	void exitGameClicked();
	void exitYesClicked();
	void exitNoClicked();
	// Other functions
	void openExitConfirmation();
	void closeExitConfirmation();

	// Functions inherited from GameState
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);
	void windowResized(int width, int height);

public:
	MainMenuState(OgrePtrs &ogrePtrs, InputManager *inputManager);

	void enter();
	void update(const Ogre::Real deltaTimeSecs);
	void exit();
};
