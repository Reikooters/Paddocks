/*************************************************************************
 PaddocksFrameListener.h
**************************************************************************
 PaddocksFrameListener class.
**************************************************************************/

class PaddocksFrameListener : public Ogre::FrameListener
{
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

public:
	PaddocksFrameListener() { };
};
