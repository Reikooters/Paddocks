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
 * GameState.h
 *************************************************************************/
#include <OIS\OISMouse.h>
#include <OIS\OISKeyboard.h>


/*************************************************************************
 * class GameState
 *************************************************************************
 * Abstract class which game states will derive from.
 *************************************************************************/
class GameState : public OIS::MouseListener, public OIS::KeyListener
{
	virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	virtual bool keyPressed(const OIS::KeyEvent &arg) = 0;
	virtual bool keyReleased(const OIS::KeyEvent &arg) = 0;

public:
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void update(const Ogre::Real deltaTimeSecs) = 0;
	virtual void exit() = 0;
	virtual void windowResized(int width, int height) = 0;
};
