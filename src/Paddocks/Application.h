/*************************************************************************
 Application.h
**************************************************************************
 Application class.
**************************************************************************/

class Application
{
	bool initOgre();
	void mainLoop();

	struct OgrePtrs {
		std::auto_ptr<Ogre::Root> root;
		Ogre::RenderWindow *window;

		OgrePtrs() : window(NULL) { }
	} ogrePtrs;

public:
	int go();

	Application();
	~Application();
};
