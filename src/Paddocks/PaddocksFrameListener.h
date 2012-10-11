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
 * PaddocksFrameListener.h
 *************************************************************************/


/*************************************************************************
 * class PaddocksFrameListener
 *************************************************************************
 * This class extends the Ogre::FrameListener class. It defines the
 * frameRenderingQueued function, which contains code that should be run
 * every single frame.
 *
 * The frameRenderingQueued function is called just before the GPU is
 * told to switch buffers. Meaning the CPU will run that function while
 * the GPU is busy rendering the frame. So this gives some efficiency.
 *************************************************************************/
class PaddocksFrameListener : public Ogre::FrameListener
{
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

public:
	// Constructor
	PaddocksFrameListener() { };
};
