#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GUICanvas.h"
#include "GUIBox.h"
#include <vector>

namespace GUIElements
{

class Button : public Box
{
public:
	Button(const Ogre::String& font, Ogre::uint fontSize, const Ogre::String& value);

	void setValue(const Ogre::String& value);
	void setFontColor(const Ogre::ColourValue& color);
	void setDownBackground(const Fill& fill);

	void setContainer(GUICanvas* container);
	void draw(Canvas* canvas, Atlas* atlas);
	bool onMouseDown(int x, int y);
	bool onMouseUp(int x, int y);
	bool onMouseOver();
	bool onMouseOut();
protected:

	void calculateTextWidth();

	bool isDown;
	Ogre::String value;
	Ogre::String font;
	Ogre::uint fontSize;
	Ogre::ColourValue fontColor;
	Fill downBackground;
	Ogre::Real textWidth;
};

}

#endif