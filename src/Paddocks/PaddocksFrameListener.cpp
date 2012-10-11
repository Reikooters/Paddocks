/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * PaddocksFrameListener.cpp
 *************************************************************************
 * This file contains the definitions for the functions declared in the
 * PaddocksFrameListener class. See PaddocksFrameListener.h for details
 * on this class.
 *************************************************************************/
#include "PaddocksFrameListener.h"


/*************************************************************************
 * PaddocksFrameListener::frameRenderingQueued()
 *************************************************************************
 * Constructor. Initialises variables.
 *************************************************************************/
bool PaddocksFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	//std::cout << "A frame!" << std::endl;

	bool ret = Ogre::FrameListener::frameRenderingQueued(evt);

	return ret;
}
