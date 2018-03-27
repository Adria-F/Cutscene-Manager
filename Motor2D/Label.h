#ifndef __LABEL_H__
#define __LABEL_H__

#include "UIElement.h"
#include "j1Fonts.h"
#include <string>

class Label : virtual public UIElement
{
public:
	bool LabelPreUpdate();
	bool LabelUpdate(float dt);
	bool LabelPostUpdate();
	bool LabelDraw(float dt);
	bool LabelCleanUp();

	void ChangeText(std::string& newText);

	Label();

	Label(SDL_Rect& position, iPoint positionOffset, std::string& fontPath, SDL_Color textColor, std::string& label, int size = 12);

	~Label();

public:
	iPoint Labelrelativepos = { 0,0 };
	std::string label;
	_TTF_Font* font = nullptr;
	SDL_Texture* fontTexture;
	SDL_Color textColor;
};

#endif