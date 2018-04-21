#include "UI_TextBox.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "UI_Text.h"

TextBox::~TextBox()
{
	std::list<Text*>::iterator it_t = textLines.begin();
	while (it_t != textLines.end())
	{
		RELEASE(*it_t);
		it_t++;
	}
	textLines.clear();
}

void TextBox::BlitElement()
{
	iPoint globalPosition = getGlobalPosition();

	App->render->DrawQuad({ globalPosition.x - DEFAULT_BORDER_THICKNESS, globalPosition.y - DEFAULT_BORDER_THICKNESS, section.w + 2 * DEFAULT_BORDER_THICKNESS, section.h + 2 * DEFAULT_BORDER_THICKNESS }, DEFAULT_BORDER_COLOR);
	App->render->DrawQuad({ globalPosition.x, globalPosition.y, section.w, section.h }, DEFAULT_COLOR);

	for (std::list<Text*>::iterator it_t = textLines.begin(); it_t != textLines.end(); it_t++)
	{
		(*it_t)->BlitElement();
	}
}

void TextBox::addTextLine(std::string text)
{
	Text* line = new Text(text, BOX_MARGIN, BOX_MARGIN + getLinesHeight());
	line->parent = this;

	textLines.push_back(line);

	int width = line->tex_width;
	if (width + 2 * BOX_MARGIN > section.w)
		section.w = width + 2 * BOX_MARGIN;
	int height = getLinesHeight();
	if (height + 2 * BOX_MARGIN > section.h)
		section.h = height + 2 * BOX_MARGIN;
}

int TextBox::getLinesHeight()
{
	int height = 0;

	for (std::list<Text*>::iterator it_t = textLines.begin(); it_t != textLines.end(); it_t++)
	{
		height += (*it_t)->tex_height;
	}

	return height;
}
