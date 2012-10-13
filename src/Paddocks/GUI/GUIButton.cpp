#include "GUIButton.h"

using namespace GUIElements;

Button::Button(const Ogre::String& font, Ogre::uint fontSize, const Ogre::String& value)
: Box(100, 30), isDown(false), font(font), fontSize(fontSize), value(value), textWidth(50)
{
}

void Button::setValue(const Ogre::String& value)
{
	this->value = value;
	calculateTextWidth();
	flagDirty();
}

void Button::setFontColor(const Ogre::ColourValue& color)
{
	flagDirty();
	fontColor = color;
}

void Button::setDownBackground(const Fill& fill)
{
	flagDirty();
	downBackground = fill;
}

void Button::setContainer(GUICanvas* container)
{
	this->container = container;

	calculateTextWidth();
}

void Button::draw(Canvas* canvas, Atlas* atlas)
{
	int x, y;
	position.derivePosition(width, height, container->getViewport()->getActualWidth(),
		container->getViewport()->getActualHeight(), x, y);

	if(isDown && isMouseOver)
		canvas->drawRectangle(x, y, width, height, downBackground, border);
	else
		canvas->drawRectangle(x, y, width, height, background, border);

	FontMetrics metrics = atlas->getFontMetrics(font, fontSize);
	GlyphInfo iInfo = atlas->getGlyphInfo(font, fontSize, 'i');

	y += (height / 2) + (metrics.height * 0.4);

	Ogre::Real pen = x + width / 2 - textWidth / 2;

	for(unsigned int i = 0; i < value.length(); ++i)
	{
		if(value[i] == ' ')
		{
			pen += iInfo.advance;
			continue;
		}

		GlyphInfo glyph = atlas->getGlyphInfo(font, fontSize, value[i]);
		canvas->drawGlyph(glyph, glyph.bearingX + pen, y - glyph.bearingY, glyph.texInfo.width, glyph.texInfo.height, fontColor);
		pen += glyph.advance;
	}
}

bool Button::onMouseDown(int x, int y)
{
	isDown = true;
	flagDirty();
	return true;
}

bool Button::onMouseUp(int x, int y)
{
	if(isDown && isMouseOver)
		fireEvent("click");

	isDown = false;
	flagDirty();
	
	return true;
}

bool Button::onMouseOver()
{
	flagDirty();
	return true;
}

bool Button::onMouseOut()
{
	isDown = false;
	flagDirty();
	return true;
}

void Button::calculateTextWidth()
{
	assert(container);

	textWidth = 0;
	
	Atlas* atlas = container->getAtlas();

	for(unsigned int i = 0; i < value.length(); ++i)
	{
		if(value[i] == ' ')
			textWidth += atlas->getGlyphInfo(font, fontSize, 'i').advance;
		else
			textWidth += atlas->getGlyphInfo(font, fontSize, value[i]).advance;
	}
}