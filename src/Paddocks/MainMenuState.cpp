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


/*************************************************************************
 * MainMenuState::MainMenuState()
 *************************************************************************
 * Constructor.
 *************************************************************************/
MainMenuState::MainMenuState(OgrePtrs &ogrePtrs, InputManager *inputManager)
	: ogrePtrs(ogrePtrs), inputManager(inputManager)
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
	std::vector<FontFaceDefinition> fontList;

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
		startGameButton = new GUIElements::Button("", 0, "");
		startGameButton->setSize(400, 66);
		startGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -288));
		startGameButton->setBackground(Fill("main_menu-start_game.png"));
		startGameButton->bindEvent("click", GUIDelegate(this, &MainMenuState::startGameClicked));

		howToPlayButton = new GUIElements::Box(400, 66);
		howToPlayButton->setPosition(Position(RelativePosition(BottomLeft), 30, -202));
		howToPlayButton->setBackground(Fill("main_menu-how_to_play.png"));
		howToPlayButton->bindEvent("click", GUIDelegate(this, &MainMenuState::startGameClicked));

		optionsButton = new GUIElements::Box(400, 66);
		optionsButton->setPosition(Position(RelativePosition(BottomLeft), 30, -116));
		optionsButton->setBackground(Fill("main_menu-options.png"));

		exitGameButton = new GUIElements::Box(400, 66);
		exitGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -30));
		exitGameButton->setBackground(Fill("main_menu-exit_game.png"));
	}
	catch (std::exception)
	{
		delete startGameButton;
		delete howToPlayButton;
		delete optionsButton;
		delete exitGameButton;

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


void MainMenuState::startGameClicked()
{
	std::cout << "Start game" << std::endl;
}
