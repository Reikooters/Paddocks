/*************************************************************************
 PaddocksFrameListener.cpp
**************************************************************************
 PaddocksFrameListener class.
**************************************************************************/
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
