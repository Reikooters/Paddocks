#include "GUITextBox.h"

using namespace GUIElements;

TextBox::TextBox(const Ogre::String& font, Ogre::uint fontSize, Ogre::uint maxChars) : Box(100, 25),
font(font), fontSize(fontSize), maxChars(maxChars), hasFocus(false), caretIdx(0), caretBlinkVisible(true)
{
}

void TextBox::setFontColor(const Ogre::ColourValue& color)
{
	flagDirty();

	fontColor = color;
}

void TextBox::setFocusedBackground(const Fill& fill)
{
	flagDirty();

	focusedBackground = fill;
}

void TextBox::setValue(const Ogre::String& value)
{
	flagDirty();

	this->value = value.substr(0, maxChars);
	caretIdx = (Ogre::uint)value.length();
}

Ogre::String TextBox::getValue() const
{
	return value;
}

void TextBox::draw(Canvas* canvas, Atlas* atlas)
{
	int x, y;
	position.derivePosition(width, height, container->getViewport()->getActualWidth(),
		container->getViewport()->getActualHeight(), x, y);

	if(hasFocus)
		canvas->drawRectangle(x, y, width, height, focusedBackground, border);
	else
		canvas->drawRectangle(x, y, width, height, background, border);

	FontMetrics metrics = atlas->getFontMetrics(font, fontSize);
	GlyphInfo iInfo = atlas->getGlyphInfo(font, fontSize, 'i');

	y += (height / 2) + (metrics.height * 0.4);

	Ogre::Real pen = x + iInfo.advance * 0.6 + 6;

	glyphXPositions.clear();

	for(unsigned int i = 0; i < value.length(); ++i)
	{
		glyphXPositions.push_back(pen);

		if(i == caretIdx && hasFocus && caretBlinkVisible)
			canvas->drawRectangle(pen, y - metrics.height * 0.85, 1, metrics.height, fontColor);

		if(value[i] == ' ')
		{
			pen += iInfo.advance;
			continue;
		}

		GlyphInfo glyph = atlas->getGlyphInfo(font, fontSize, value[i]);
		canvas->drawGlyph(glyph, glyph.bearingX + pen, y - glyph.bearingY, glyph.texInfo.width, glyph.texInfo.height, fontColor);
		pen += glyph.advance;
	}

	glyphXPositions.push_back(pen);

	if(caretIdx == value.length() && hasFocus && caretBlinkVisible)
		canvas->drawRectangle(pen, y - metrics.height * 0.85, 1, metrics.height, fontColor);
}

bool TextBox::onMouseDown(int x, int y)
{
	if(hasFocus)
	{
		Ogre::Real closestDist = 99999.0f;
		Ogre::Real dist = 0;

		for(unsigned int i = 0; i < glyphXPositions.size(); ++i)
		{
			dist = Ogre::Math::Abs(x - glyphXPositions[i]);
			if(dist < closestDist)
			{
				closestDist = dist;
			}
			else
			{
				// last spot was closest
				caretIdx = i - 1;
				if(caretIdx < 0)
					caretIdx = 0;
				else if(caretIdx > value.length())
					caretIdx = (Ogre::uint)value.length();

				resetBlink();
				flagDirty();
				return true;
			}
		}

		// closest spot is very end
		caretIdx = (Ogre::uint)value.length();
		resetBlink();
		flagDirty();
	}

	return true;
}

bool TextBox::onMouseUp(int x, int y)
{
	return true;
}

bool TextBox::onKeyboardEvent(const OIS::KeyEvent& keyEvent)
{
	assert(container);

	if(keyEvent.key == OIS::KC_TAB)
	{
		return false;
	}
	else if(keyEvent.key == OIS::KC_RETURN)
	{
		container->clearFocus();
		fireEvent("enter");
		return true;
	}

	if(keyEvent.key == OIS::KC_BACK || keyEvent.key == OIS::KC_DELETE ||
		keyEvent.key == OIS::KC_LEFT || keyEvent.key == OIS::KC_RIGHT ||
		keyEvent.key == OIS::KC_HOME || keyEvent.key == OIS::KC_END)
	{
		if(keyEvent.key == OIS::KC_BACK)
		{
			if(caretIdx)
			{
				value.erase(caretIdx-1, 1);
				caretIdx--;
			}
		}
		else if(keyEvent.key == OIS::KC_DELETE)
		{
			if(caretIdx < value.length())
			{
				value.erase(caretIdx, 1);
			}
		}
		else if(keyEvent.key == OIS::KC_LEFT)
		{
			if(caretIdx)
			{
				caretIdx--;
			}
		}
		else if(keyEvent.key == OIS::KC_RIGHT)
		{
			if(caretIdx < value.length())
				caretIdx++;
		}
		else if(keyEvent.key == OIS::KC_HOME)
		{
			caretIdx = 0;
		}
		else if(keyEvent.key == OIS::KC_END)
		{
			caretIdx = (Ogre::uint)value.length();
		}

		flagDirty();
		resetBlink();
		return true;
	}

	if(keyEvent.text)
	{
		GlyphInfo glyph = container->getAtlas()->getGlyphInfo(font, fontSize, keyEvent.text);
		if(!glyph.texInfo.isEmpty || keyEvent.text == ' ')
		{
			if(value.length() == maxChars)
				return true;

			Ogre::DisplayString keyText;
			keyText.push_back(keyEvent.text);

			value.insert(caretIdx++, Ogre::String(keyText));
			
			flagDirty();
			resetBlink();

			return true;
		}
		else
		{
			std::cout << "Unknown Key Text: " << keyEvent.text << std::endl;
		}
	}

	return false;
}

bool TextBox::isFocusable()
{
	return true;
}

void TextBox::onGainFocus()
{
	resetBlink();
	flagDirty();

	hasFocus = true;
}

void TextBox::onLoseFocus()
{
	flagDirty();

	hasFocus = false;
}

void TextBox::update()
{
	if(hasFocus)
	{
		if(caretBlinkTimer.getMilliseconds() > 600)
		{
			caretBlinkVisible = !caretBlinkVisible;
			caretBlinkTimer.reset();
			flagDirty();
		}
	}
}

void TextBox::resetBlink()
{
	caretBlinkVisible = true;
	caretBlinkTimer.reset();
}