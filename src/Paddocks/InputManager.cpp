/*************************************************************************
 * Paddocks
 * by Shane "Reiko" Swenson - October 2012.
 * 
 * Computer version of the pen and paper game, 'Paddocks' also known as
 * 'Dots and Boxes'.
 * 	
 * https://github.com/Reikooters/Paddocks
 *************************************************************************
 * InputManager.cpp
 *************************************************************************
 * Code in this file is based on code from "The Player v2.0" demo, by
 * Adam Simmons. http://princeofcode.com/player.php
 *************************************************************************/
#include "InputManager.h"

// Singleton stuff.
InputManager *InputManager::inputManager;

InputManager* InputManager::getSingletonPtr()
{
	if (!inputManager)
		inputManager = new InputManager();

	return inputManager;
}


/*************************************************************************
 * InputManager::InputManager
 *************************************************************************
 * Constructor. Initialises variables.
 *************************************************************************/
InputManager::InputManager()
	: mouse(NULL), keyboard(NULL), inputSystem(NULL)
{
}


/*************************************************************************
 * InputManager::~InputManager
 *************************************************************************
 * Destructor. Performs clean up.
 *************************************************************************/
InputManager::~InputManager()
{
	if (inputSystem)
	{
		if (mouse)
		{
			inputSystem->destroyInputObject(mouse);
			mouse = NULL;
		}

		if (keyboard)
		{
			inputSystem->destroyInputObject(keyboard);
			keyboard = NULL;
		}

		/*
		if (joysticks.size() > 0)
		{
			itJoystick    = mJoysticks.begin();
			itJoystickEnd = mJoysticks.end();
			for (; itJoystick != itJoystickEnd; ++itJoystick)
				mInputSystem->destroyInputObject(*itJoystick);

			mJoysticks.clear();
		}
		*/

		// If you use OIS1.0RC1 or above, uncomment this line
		// and comment the line below it
		inputSystem->destroyInputSystem(inputSystem);
		//inputSystem->destroyInputSystem();
		inputSystem = NULL;

		// Clear Listeners
		keyListeners.clear();
		mouseListeners.clear();
		//joystickListeners.clear();
    }
}

void InputManager::initialise(Ogre::RenderWindow *renderWindow)
{
    if(!inputSystem)
	{
		// Setup basic variables
		OIS::ParamList paramList;    
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;

		// Get window handle
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		// Fill parameter list
		windowHndStr << (unsigned int) windowHnd;
		paramList.insert( std::make_pair(std::string("WINDOW"), windowHndStr.str()));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		//paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		//paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		// Create inputsystem
		inputSystem = OIS::InputManager::createInputSystem(paramList);

		// If possible create a buffered keyboard
		if (inputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0)
		{
			keyboard = static_cast<OIS::Keyboard*>(inputSystem->createInputObject(OIS::OISKeyboard, true));
			keyboard->setEventCallback(this);
		}

		// If possible create a buffered mouse
		if (inputSystem->getNumberOfDevices(OIS::OISMouse) > 0)
		{
			mouse = static_cast<OIS::Mouse*>(inputSystem->createInputObject(OIS::OISMouse, true));
			mouse->setEventCallback(this);

			// Get window size
			unsigned int width, height, depth;
			int left, top;
			renderWindow->getMetrics(width, height, depth, left, top);

			// Set mouse region
			this->setWindowExtents(width, height);
		}

		/*
		// If possible create all joysticks in buffered mode
		if (inputSystem->getNumberOfDevices(OIS::OISJoyStick) > 0)
		{
			joysticks.resize(inputSystem->getNumberOfDevices(OIS::OISJoyStick));

			itJoystick    = joysticks.begin();
			itJoystickEnd = joysticks.end();
			for (; itJoystick != itJoystickEnd; ++itJoystick)
			{
				(*itJoystick) = static_cast<OIS::JoyStick*>(inputSystem->createInputObject(OIS::OISJoyStick, true));
				(*itJoystick)->setEventCallback(this);
			}
		}
		*/
	}
}

void InputManager::capture()
{
	// Need to capture / update each device every frame
	if (mouse)
		mouse->capture();

	if (keyboard)
		keyboard->capture();

	/*
	if (joysticks.size() > 0)
	{
		itJoystick    = joysticks.begin();
		itJoystickEnd = joysticks.end();
		for (; itJoystick != itJoystickEnd; ++itJoystick)
			(*itJoystick)->capture();
	}
	*/
}

void InputManager::addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName)
{
	if (keyboard)
	{
		// Check for duplicate items
		itKeyListener = keyListeners.find(instanceName);
		if (itKeyListener == keyListeners.end())
		{
			keyListeners[instanceName] = keyListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}

void InputManager::addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName)
{
	if (mouse)
	{
		// Check for duplicate items
		itMouseListener = mouseListeners.find(instanceName);
		if (itMouseListener == mouseListeners.end())
		{
			mouseListeners[instanceName] = mouseListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}

/*
void InputManager::addJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName)
{
	if (joysticks.size() > 0)
	{
		// Check for duplicate items
		itJoystickListener = joystickListeners.find(instanceName);
		if (itJoystickListener == joystickListeners.end())
		{
			joystickListeners[instanceName] = joystickListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}
*/

void InputManager::removeKeyListener(const std::string& instanceName)
{
	// Check if item exists
	itKeyListener = keyListeners.find(instanceName);
	if (itKeyListener != keyListeners.end())
	{
		keyListeners.erase(itKeyListener);
	}
	else
	{
		// Doesn't Exist
	}
}

void InputManager::removeMouseListener(const std::string& instanceName)
{
	// Check if item exists
	itMouseListener = mouseListeners.find(instanceName);
	if (itMouseListener != mouseListeners.end())
	{
		mouseListeners.erase(itMouseListener);
	}
	else
	{
		// Doesn't Exist
	}
}

/*
void InputManager::removeJoystickListener(const std::string& instanceName)
{
	// Check if item exists
	itJoystickListener = joystickListeners.find(instanceName);
	if (itJoystickListener != joystickListeners.end())
	{
		joystickListeners.erase(itJoystickListener);
	}
	else
	{
		// Doesn't Exist
	}
}
*/

void InputManager::removeKeyListener(OIS::KeyListener *keyListener)
{
	itKeyListener    = keyListeners.begin();
	itKeyListenerEnd = keyListeners.end();
	for (; itKeyListener != itKeyListenerEnd; ++itKeyListener)
	{
		if (itKeyListener->second == keyListener)
		{
			keyListeners.erase(itKeyListener);
			break;
		}
	}
}

void InputManager::removeMouseListener(OIS::MouseListener *mouseListener)
{
	itMouseListener    = mouseListeners.begin();
	itMouseListenerEnd = mouseListeners.end();
	for (; itMouseListener != itMouseListenerEnd; ++itMouseListener)
	{
		if (itMouseListener->second == mouseListener)
		{
			mouseListeners.erase(itMouseListener);
			break;
		}
	}
}

/*
void InputManager::removeJoystickListener(OIS::JoyStickListener *joystickListener)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener)
	{
		if (itJoystickListener->second == joystickListener)
		{
			joystickListeners.erase(itJoystickListener);
			break;
		}
	}
}
*/

void InputManager::removeAllListeners()
{
	keyListeners.clear();
	mouseListeners.clear();
	//joystickListeners.clear();
}

void InputManager::removeAllKeyListeners()
{
	keyListeners.clear();
}

void InputManager::removeAllMouseListeners()
{
	mouseListeners.clear();
}

/*
void InputManager::removeAllJoystickListeners()
{
	joystickListeners.clear();
}
*/

void InputManager::setWindowExtents(int width, int height)
{
	// Set mouse region (if window resizes, we should alter this to reflect as well)
	const OIS::MouseState &mouseState = mouse->getMouseState();
	mouseState.width  = width;
	mouseState.height = height;
}

OIS::Mouse* InputManager::getMouse()
{
	return mouse;
}

OIS::Keyboard* InputManager::getKeyboard()
{
	return keyboard;
}

/*
OIS::JoyStick* InputManager::getJoystick(unsigned int index)
{
	// Make sure it's a valid index
	if (index < joysticks.size())
		return joysticks[index];

	return NULL;
}

int InputManager::getNumOfJoysticks()
{
	// Cast to keep compiler happy ^^
	return (int) joysticks.size();
}
*/

bool InputManager::keyPressed(const OIS::KeyEvent &e)
{
	itKeyListener    = keyListeners.begin();
	itKeyListenerEnd = keyListeners.end();
	for (; itKeyListener != itKeyListenerEnd; ++itKeyListener)
	{
		if (!itKeyListener->second->keyPressed(e))
			break;
	}

	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent &e)
{
	itKeyListener    = keyListeners.begin();
	itKeyListenerEnd = keyListeners.end();
	for (; itKeyListener != itKeyListenerEnd; ++itKeyListener)
	{
		if(!itKeyListener->second->keyReleased(e))
			break;
	}

	return true;
}

bool InputManager::mouseMoved(const OIS::MouseEvent &e)
{
	itMouseListener    = mouseListeners.begin();
	itMouseListenerEnd = mouseListeners.end();
	for (; itMouseListener != itMouseListenerEnd; ++itMouseListener )
	{
		if (!itMouseListener->second->mouseMoved(e))
			break;
	}

	return true;
}

bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	itMouseListener    = mouseListeners.begin();
	itMouseListenerEnd = mouseListeners.end();
	for (; itMouseListener != itMouseListenerEnd; ++itMouseListener)
	{
		if (!itMouseListener->second->mousePressed(e, id))
			break;
	}

	return true;
}

bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	itMouseListener    = mouseListeners.begin();
	itMouseListenerEnd = mouseListeners.end();
	for (; itMouseListener != itMouseListenerEnd; ++itMouseListener)
	{
		if (!itMouseListener->second->mouseReleased(e, id))
			break;
	}

	return true;
}

/*
bool InputManager::povMoved(const OIS::JoyStickEvent &e, int pov)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener)
	{
		if (!itJoystickListener->second->povMoved(e, pov))
			break;
	}

	return true;
}

bool InputManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener)
	{
		if (!itJoystickListener->second->axisMoved(e, axis))
			break;
	}

	return true;
}

bool InputManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener)
	{
		if (!itJoystickListener->second->sliderMoved(e, sliderID))
			break;
	}

	return true;
}

bool InputManager::buttonPressed(const OIS::JoyStickEvent &e, int button)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener)
	{
		if (!itJoystickListener->second->buttonPressed(e, button))
			break;
	}

	return true;
}

bool InputManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
{
	itJoystickListener    = joystickListeners.begin();
	itJoystickListenerEnd = joystickListeners.end();
	for (; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener )
	{
		if (!itJoystickListener->second->buttonReleased(e, button))
			break;
	}

	return true;
}
*/
