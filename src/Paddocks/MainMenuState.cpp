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

	guiCanvas.reset(new GUICanvas(ogrePtrs.camera, ogrePtrs.sceneManager, texList, fontList));

	GUIElements::Box* fullscreenMatte = new GUIElements::Box(ogrePtrs.camera->getViewport()->getActualWidth(), 
		ogrePtrs.camera->getViewport()->getActualHeight());
	fullscreenMatte->setPosition(Position(BottomRight));
	fullscreenMatte->setBackground(Fill(parseHexColor("#00050a"), parseHexColor("#06182c")));

	guiCanvas->addElement(fullscreenMatte);
}
