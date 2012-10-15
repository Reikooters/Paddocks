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
#include "MainMenuState.h"
#include "GUITextBox.h"
#include "GUIButton.h"
#include "GUILabel.h"


/*************************************************************************
 * MainMenuState::MainMenuState()
 *************************************************************************
 * Constructor.
 *************************************************************************/
MainMenuState::MainMenuState(OgrePtrs &ogrePtrs)
{
	this->ogrePtrs = ogrePtrs;
}


void MainMenuState::enter()
{
	createGUI();
}


void MainMenuState::update(const Ogre::Real deltaTimeSecs)
{
	guiCanvas->update();
}


void MainMenuState::exit()
{
	
}


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
		startGameButton = new GUIElements::Box(400, 66);
		startGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -288));
		startGameButton->setBackground(Fill("main_menu-start_game.png"));

		howToPlayButton = new GUIElements::Box(400, 66);
		howToPlayButton->setPosition(Position(RelativePosition(BottomLeft), 30, -202));
		howToPlayButton->setBackground(Fill("main_menu-how_to_play.png"));

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
