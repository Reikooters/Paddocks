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


void MainMenuState::update(Ogre::Real deltaTimeSecs)
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
	texList.push_back("menu-1.png");
	texList.push_back("menu-2.png");
	texList.push_back("menu-3.png");

	Ogre::ResourceGroupManager *resGrp = Ogre::ResourceGroupManager::getSingletonPtr();
	Ogre::String resourceDirectory = "data";
	Ogre::String resourceGroupName = "Main Menu";
	resGrp->addResourceLocation(resourceDirectory, "FileSystem", resourceGroupName, false);
	resGrp->loadResourceGroup(resourceGroupName);

	guiCanvas.reset(new GUICanvas(ogrePtrs.camera, ogrePtrs.sceneManager, texList, fontList));

	/*
	GUIElements::Box* fullscreenMatte = new GUIElements::Box(ogrePtrs.camera->getViewport()->getActualWidth(), 
		ogrePtrs.camera->getViewport()->getActualHeight());
	fullscreenMatte->setPosition(Position(BottomRight));
	fullscreenMatte->setBackground(Fill(parseHexColor("#00050a"), parseHexColor("#06182c")));
	*/

	GUIElements::Box* optionsButton = NULL;
	GUIElements::Box* howToPlayButton = NULL;
	GUIElements::Box* exitGameButton = NULL;

	try
	{
		optionsButton = new GUIElements::Box(406, 66);
		optionsButton->setPosition(Position(RelativePosition(BottomLeft), 30, -222));
		optionsButton->setBackground(Fill("menu-1.png"));

		howToPlayButton = new GUIElements::Box(406, 66);
		howToPlayButton->setPosition(Position(RelativePosition(BottomLeft), 30, -126));
		howToPlayButton->setBackground(Fill("menu-2.png"));

		exitGameButton = new GUIElements::Box(406, 66);
		exitGameButton->setPosition(Position(RelativePosition(BottomLeft), 30, -30));
		exitGameButton->setBackground(Fill("menu-3.png"));
	}
	catch (std::exception)
	{
		delete optionsButton;
		delete howToPlayButton;
		delete exitGameButton;
	}

	guiCanvas->addElement(optionsButton);
	guiCanvas->addElement(howToPlayButton);
	guiCanvas->addElement(exitGameButton);
}
