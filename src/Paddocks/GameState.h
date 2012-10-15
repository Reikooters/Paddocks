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


/*************************************************************************
 * class GameState
 *************************************************************************
 * Abstract class which game states will derive from.
 *************************************************************************/
class GameState
{
public:
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void update(const Ogre::Real deltaTimeSecs) = 0;
	virtual void exit() = 0;
};
