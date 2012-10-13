#ifndef __GUITEXTBOX_H__
#define __GUITEXTBOX_H__

#include "GUICanvas.h"
#include "GUIBox.h"
#include "OgreTimer.h"
#include <vector>

namespace GUIElements
{

class TextBox : public Box
{
public:
	TextBox(const Ogre::String& font, Ogre::uint fontSize, Ogre::uint maxChars);

	void setFontColor(const Ogre::ColourValue& color);
	void setFocusedBackground(const Fill& fill);
	void setValue(const Ogre::String& value);
	Ogre::String getValue() const;

	void draw(Canvas* canvas, Atlas* atlas);
	bool onMouseDown(int x, int y);
	bool onMouseUp(int x, int y);
	bool onKeyboardEvent(const OIS::KeyEvent& keyEvent);
	bool isFocusable();
	void onGainFocus();
	void onLoseFocus();
	void update();
protected:

	void resetBlink();

	bool hasFocus;
	Ogre::String value;
	Ogre::String font;
	Ogre::uint fontSize, maxChars, caretIdx;
	Ogre::ColourValue fontColor;
	Fill focusedBackground;
	std::vector<Ogre::Real> glyphXPositions;
	Ogre::Timer caretBlinkTimer;
	bool caretBlinkVisible;
};

}

#endif