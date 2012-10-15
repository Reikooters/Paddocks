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
 * InputManager.h
 *************************************************************************
 * Code in this file is based on code from "The Player v2.0" demo, by
 * Adam Simmons. http://princeofcode.com/player.php
 *
 * Joystick functionality has been commented out as we won't be using
 * it in this project.
 *************************************************************************/
#include <OIS\OISMouse.h>
#include <OIS\OISKeyboard.h>
#include <OIS\OISJoyStick.h>
#include <OIS\OISInputManager.h>


/*************************************************************************
 * class InputManager
 *************************************************************************
 * Handles receiving input and passing it off to multiple Listeners.
 *************************************************************************/
class InputManager : public OIS::KeyListener, public OIS::MouseListener//, public OIS::JoyStickListener
{
	InputManager();
	InputManager(const InputManager&) { }
	InputManager &operator= (const InputManager&);

	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

	bool mouseMoved(const OIS::MouseEvent &e );
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	/*
	bool povMoved(const OIS::JoyStickEvent &e, int pov);
	bool axisMoved(const OIS::JoyStickEvent &e, int axis);
	bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
	bool buttonPressed(const OIS::JoyStickEvent &e, int button);
	bool buttonReleased(const OIS::JoyStickEvent &e, int button);
	*/

	OIS::InputManager *inputSystem;
	OIS::Mouse        *mouse;
	OIS::Keyboard     *keyboard;

	/*
	std::vector<OIS::JoyStick*> joysticks;
	std::vector<OIS::JoyStick*>::iterator itJoystick;
	std::vector<OIS::JoyStick*>::iterator itJoystickEnd;
	*/

	std::map<std::string, OIS::KeyListener*> keyListeners;
	std::map<std::string, OIS::MouseListener*> mouseListeners;
	//std::map<std::string, OIS::JoyStickListener*> joystickListeners;

	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
	//std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener;

	std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
	//std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListenerEnd;

	static InputManager *inputManager;

public:
	virtual ~InputManager();

	void initialise(Ogre::RenderWindow *renderWindow);
	void capture();

	void addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName);
	void addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName);
	//void addJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName);

	void removeKeyListener(const std::string& instanceName);
	void removeMouseListener(const std::string& instanceName);
	//void removeJoystickListener(const std::string& instanceName);

	void removeKeyListener(OIS::KeyListener *keyListener);
	void removeMouseListener(OIS::MouseListener *mouseListener);
	//void removeJoystickListener(OIS::JoyStickListener *joystickListener);

	void removeAllListeners();
	void removeAllKeyListeners();
	void removeAllMouseListeners();
	//void removeAllJoystickListeners();

	void setWindowExtents(const int width, const int height);

	OIS::Mouse*    getMouse();
	OIS::Keyboard* getKeyboard();
	//OIS::JoyStick* getJoystick(unsigned int index);

	//int getNumOfJoysticks();

	static InputManager* getSingletonPtr();
};
