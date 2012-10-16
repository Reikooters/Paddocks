/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * MainMenuState.cpp
 *************************************************************************/
#include "MainMenuState.h"
#include "GUITextBox.h"
#include "GUIButton.h"
#include "GUILabel.h"
#include "InputManager.h"
#include "Application.h"


/*************************************************************************
 * MainMenuState::MainMenuState()
 *************************************************************************
 * Constructor.
 *************************************************************************/
MainMenuState::MainMenuState(OgrePtrs &ogrePtrs, InputManager *inputManager)
	: ogrePtrs(ogrePtrs), inputManager(inputManager),
	boolOpenExitConfirmation(false), boolCloseExitConfirmation(false)
{

}


/*************************************************************************
 * MainMenuState::enter()
 *************************************************************************
 * This should be called when the state should begin.
 *************************************************************************/
void MainMenuState::enter()
{
	inputManager->addMouseListener(this, "mainMenuMouseListener");
	inputManager->addKeyListener(this, "mainMenuKeyListener");

	createGUI();
}


/*************************************************************************
 * MainMenuState::update()
 *************************************************************************
 * This should be called every frame.
 *************************************************************************/
void MainMenuState::update(const Ogre::Real deltaTimeSecs)
{
	guiCanvas->update();

	runGUISteps();
}


/*************************************************************************
 * MainMenuState::exit()
 *************************************************************************
 * This should be called when the state should end.
 *************************************************************************/
void MainMenuState::exit()
{

}


/*************************************************************************
 * MainMenuState::createGUI()
 *************************************************************************
 * Creates the GUI canvas and GUI elements.
 *************************************************************************/
void MainMenuState::createGUI()
{
	FontFaceDefinition verdana("verdana.ttf");
	verdana.addSize(14);

	std::vector<FontFaceDefinition> fontList;
	fontList.push_back(verdana);

	std::vector<Ogre::String> texList;
	texList.push_back("main_menu-start_game.png");
	texList.push_back("main_menu-how_to_play.png");
	texList.push_back("main_menu-options.png");
	texList.push_back("main_menu-exit_game.png");

	Ogre::ResourceGroupManager *resGrp = Ogre::ResourceGroupManager::getSingletonPtr();
	Ogre::String resourceDirectory = "data";
	Ogre::String resourceGroupName = "Main Menu";
	resGrp->addResourceLocation(resourceDirectory, "FileSystem", resourceGroupName, false);
	resGrp->loadResourceGroup(resourceGroupName);

	guiCanvas.reset(new GUICanvas(ogrePtrs.camera, ogrePtrs.sceneManager, texList, fontList));

	/*
	GUIElements::Box* fullscreenMatte = new GUIElements::Box(ogrePtrs.camera->getViewport()->getActualWidth(), 
		ogrePtrs.camera->getViewport()->getActualHeight());
	fullscreenMatte->setPosition(Position(Center));
	fullscreenMatte->setBackground(Fill(parseHexColor("#00050a"), parseHexColor("#06182c")));
	*/

	GUIElements::Box* startGameButton = NULL;
	GUIElements::Box* howToPlayButton = NULL;
	GUIElements::Box* optionsButton = NULL;
	GUIElements::Box* exitGameButton = NULL;

	try
	{
		startGameButton = new GUIElements::Box(400, 66);
		startGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -288));
		startGameButton->setBackground(Fill("main_menu-start_game.png"));
		startGameButton->bindEvent("click", GUIDelegate(this, &MainMenuState::startGameClicked));
		startGameButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["startGameButton"] = startGameButton;

		howToPlayButton = new GUIElements::Box(400, 66);
		howToPlayButton->setPosition(Position(RelativePosition(BottomLeft), 30, -202));
		howToPlayButton->setBackground(Fill("main_menu-how_to_play.png"));
		howToPlayButton->bindEvent("click", GUIDelegate(this, &MainMenuState::startGameClicked));
		howToPlayButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["howToPlayButton"] = howToPlayButton;

		optionsButton = new GUIElements::Box(400, 66);
		optionsButton->setPosition(Position(RelativePosition(BottomLeft), 30, -116));
		optionsButton->setBackground(Fill("main_menu-options.png"));
		optionsButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["optionsButton"] = optionsButton;

		exitGameButton = new GUIElements::Box(400, 66);
		exitGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -30));
		exitGameButton->setBackground(Fill("main_menu-exit_game.png"));
		exitGameButton->bindEvent("click", GUIDelegate(this, &MainMenuState::exitGameClicked));
		exitGameButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["exitGameButton"] = exitGameButton;
	}
	catch (std::exception)
	{
		delete startGameButton;
		delete howToPlayButton;
		delete optionsButton;
		delete exitGameButton;

		std::list<std::map<Ogre::String, GUIElement*>::iterator> itlist;
		itlist.push_back(guiElements.find("startGameButton"));
		itlist.push_back(guiElements.find("howToPlayButton"));
		itlist.push_back(guiElements.find("optionsButton"));
		itlist.push_back(guiElements.find("exitGameButton"));

		for (std::list<std::map<Ogre::String, GUIElement*>::iterator>::iterator it = itlist.begin(); it != itlist.end(); ++it)
		{
			if (*it != guiElements.end())
				guiElements.erase(*it);
		}

		throw;
	}

	guiCanvas->addElement(startGameButton);
	guiCanvas->addElement(howToPlayButton);
	guiCanvas->addElement(optionsButton);
	guiCanvas->addElement(exitGameButton);
}


bool MainMenuState::mouseMoved(const OIS::MouseEvent &arg)
{
	return guiCanvas->injectMouseMove(arg.state.X.abs, arg.state.Y.abs);
}

bool MainMenuState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return guiCanvas->injectMouseDown(arg.state.X.abs, arg.state.Y.abs);
}

bool MainMenuState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return guiCanvas->injectMouseUp(arg.state.X.abs, arg.state.Y.abs);
}

bool MainMenuState::keyPressed(const OIS::KeyEvent &arg)
{
	return guiCanvas->injectKeyDown(arg);
}

bool MainMenuState::keyReleased(const OIS::KeyEvent &arg)
{
	guiCanvas->injectKeyUp(arg);

	switch(arg.key)
	{
	case OIS::KC_ESCAPE:
		break;
	case OIS::KC_F12:
	{
		Ogre::String screenshotName = ogrePtrs.window->writeContentsToTimestampedFile("screen", ".png");
		std::cout << "Screenshot saved to: " << screenshotName << std::endl;
		//messageConsole->addText("Screenshot saved to: " + screenshotName);
		break;
	}
	case OIS::KC_F2:
	{
	static bool flip = true;

	if (flip = !flip)
		ogrePtrs.camera->setPolygonMode(Ogre::PM_SOLID);
	else
		ogrePtrs.camera->setPolygonMode(Ogre::PM_WIREFRAME);

	std::cout << Ogre::String("Wireframe mode ") << (flip? "deactivated." : "activated.") << std::endl;
	//messageConsole->addText(Ogre::String("Wireframe mode ") + (flip? "deactivated." : "activated."));
	}
	}

	return true;
}

void MainMenuState::windowResized(int width, int height)
{
	if (guiCanvas.get())
	{
		guiCanvas->getCanvas()->clearClip();
		guiCanvas->setDirty();
	}
}


/*************************************************************************
 * MainMenuState::startGameClicked()
 *************************************************************************
 * This function is called when 'Start Game' is clicked.
 *************************************************************************/
void MainMenuState::startGameClicked()
{
	std::cout << "Start game" << std::endl;
}


/*************************************************************************
 * MainMenuState::exitGameClicked()
 *************************************************************************
 * This function is called when 'Exit Game' is clicked.
 *************************************************************************/
void MainMenuState::exitGameClicked()
{
	boolOpenExitConfirmation = true;
}


/*************************************************************************
 * MainMenuState::exitYesClicked()
 *************************************************************************
 * This function is called when 'Yes' is clicked in the 'Exit game?'
 * confirmation box.
 *************************************************************************/
void MainMenuState::exitYesClicked()
{
	Application::getSingletonPtr()->shutdown();
}


/*************************************************************************
 * MainMenuState::exitNoClicked()
 *************************************************************************
 * This function is called when 'No' is clicked in the 'Exit game?'
 * confirmation box.
 *************************************************************************/
void MainMenuState::exitNoClicked()
{
	boolCloseExitConfirmation = true;
}


/*************************************************************************
 * MainMenuState::openExitConfirmation()
 *************************************************************************
 * Opens the 'Exit game?' confirmation box.
 *************************************************************************/
void MainMenuState::openExitConfirmation()
{
	// Only proceed if flag is set.
	if (!boolOpenExitConfirmation)
		return;

	// Set flag to false, so this function can't be called again.
	boolOpenExitConfirmation = false;

	// Variables we'll need.
	GUIElements::Box* exitWindow = NULL;
	GUIElements::Label* exitWindowLabel = NULL;
	GUIElements::Button* exitWindowYesButton = NULL;
	GUIElements::Button* exitWindowNoButton = NULL;

	Ogre::ColourValue windowColorTop(parseHexColor("#d99034"));
	Ogre::ColourValue windowColorBottom(parseHexColor("#de9f50"));
	windowColorTop.a = 0.5f;
	windowColorBottom.a = 0.5f;

	/* We do our GUI element creating in a try/catch block so that if an
	 * exception is raised, we can do the necessary clean up. */
	try
	{
		exitWindow = new GUIElements::Box(450, 280);
		exitWindow->setPosition(Position(RelativePosition(Center), 0, 0));
		exitWindow->setBackground(Fill(windowColorTop, windowColorBottom));
		exitWindow->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["exitWindow"] = exitWindow;

		exitWindowLabel = new GUIElements::Label("verdana.ttf", 14, "Are you sure you wish to exit?", true);
		exitWindowLabel->setPosition(Position(RelativePosition(Center), 0, -25));
		exitWindowLabel->setSize(420, 160);
		//exitWindowLabel->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["exitWindowLabel"] = exitWindowLabel;

		exitWindowYesButton = new GUIElements::Button("verdana.ttf", 14, "Yes");
		exitWindowYesButton->setPosition(Position(RelativePosition(Center), -65, 100));
		exitWindowYesButton->setSize(90, 40);
		exitWindowYesButton->setBackground(Fill(parseHexColor("#d99034"), parseHexColor("#de9f50")));
		exitWindowYesButton->setDownBackground(Fill(parseHexColor("#d9a564"), parseHexColor("#dcb27e")));
		exitWindowYesButton->bindEvent("click", GUIDelegate(this, &MainMenuState::exitYesClicked));
		exitWindowYesButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["exitWindowYesButton"] = exitWindowYesButton;

		exitWindowNoButton = new GUIElements::Button("verdana.ttf", 14, "No");
		exitWindowNoButton->setPosition(Position(RelativePosition(Center), 65, 100));
		exitWindowNoButton->setSize(90, 40);
		exitWindowNoButton->setBackground(Fill(parseHexColor("#d99034"), parseHexColor("#de9f50")));
		exitWindowNoButton->setDownBackground(Fill(parseHexColor("#d9a564"), parseHexColor("#dcb27e")));
		exitWindowNoButton->bindEvent("click", GUIDelegate(this, &MainMenuState::exitNoClicked));
		exitWindowNoButton->setBorder(Border(3, parseHexColor("#83493d")));
		guiElements["exitWindowNoButton"] = exitWindowNoButton;
	}
	catch (std::exception)
	{
		// If an exception was raised, do the necessary cleanup.
		delete exitWindow;
		delete exitWindowLabel;
		delete exitWindowYesButton;
		delete exitWindowNoButton;

		std::list<std::map<Ogre::String, GUIElement*>::iterator> itlist;
		itlist.push_back(guiElements.find("exitWindow"));
		itlist.push_back(guiElements.find("exitWindowLabel"));
		itlist.push_back(guiElements.find("exitWindowYesButton"));
		itlist.push_back(guiElements.find("exitWindowNoButton"));

		for (std::list<std::map<Ogre::String, GUIElement*>::iterator>::iterator it = itlist.begin(); it != itlist.end(); ++it)
		{
			if (*it != guiElements.end())
				guiElements.erase(*it);
		}
	}

	guiCanvas->addElement(exitWindow);
	guiCanvas->addElement(exitWindowLabel);
	guiCanvas->addElement(exitWindowYesButton);
	guiCanvas->addElement(exitWindowNoButton);
}


/*************************************************************************
 * MainMenuState::closeExitConfirmation()
 *************************************************************************
 * Closes the 'Exit game?' confirmation box.
 *************************************************************************/
void MainMenuState::closeExitConfirmation()
{
	// Only proceed if flag is set.
	if (!boolCloseExitConfirmation)
		return;

	// Set flag to false, so this function can't be called again.
	boolCloseExitConfirmation = false;

	// Items to be deleted.
	std::list<Ogre::String> items;
	items.push_back("exitWindow");
	items.push_back("exitWindowLabel");
	items.push_back("exitWindowYesButton");
	items.push_back("exitWindowNoButton");

	// Remove GUI elements from canvas
	for (std::list<Ogre::String>::iterator it = items.begin(); it != items.end(); ++it)
		guiCanvas->removeElement(guiElements[*it]);

	// Delete pointers from guiElements map.
	std::list<std::map<Ogre::String, GUIElement*>::iterator> itlist;
	for (std::list<Ogre::String>::iterator it = items.begin(); it != items.end(); ++it)
		itlist.push_back(guiElements.find(*it));

	for (std::list<std::map<Ogre::String, GUIElement*>::iterator>::iterator it = itlist.begin(); it != itlist.end(); ++it)
	{
		if (*it != guiElements.end())
			guiElements.erase(*it);
	}
}


/*************************************************************************
 * MainMenuState::runGUISteps()
 *************************************************************************
 * Runs any GUI related functions that need to be called.
 *************************************************************************/
void MainMenuState::runGUISteps()
{
	// Open Exit Confirmation
	if (boolOpenExitConfirmation)
		openExitConfirmation();

	// Close Exit Confirmation
	if (boolCloseExitConfirmation)
		closeExitConfirmation();
}
