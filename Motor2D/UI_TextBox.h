#ifndef __UI_TEXTBOX_H__
#define __UI_TEXTBOX_H__

#include "UI_Element.h"
#include <list>

class Text;

#define DEFAULT_COLOR White
#define DEFAULT_BORDER_COLOR Black
#define DEFAULT_BORDER_THICKNESS 1

#define BOX_MARGIN 10
#define LINES_SEPARATION 5

class TextBox : public UI_Element
{
public:
	TextBox(int x, int y, int w, int h): UI_Element(x, y, w, h)
	{}
	~TextBox();

	void BlitElement();

	void addTextLine(std::string text);
	int getLinesHeight();

public:

	std::list<Text*> textLines;
};

#endif //__UI_TEXTBOX_H__