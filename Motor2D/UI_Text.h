#ifndef __UI_TEXT__
#define __UI_TEXT__

#include "UI_Element.h"
#include "SDL/include/SDL_pixels.h"
#include <string>

struct _TTF_Font;
class SDL_Texture;

class Text : public UI_Element
{
public:

	Text(std::string text, int x, int y);

	~Text();

	void createTexture();

	void BlitElement();

public:

	uint tex_width=0;
	uint tex_height=0;

private:

	std::string text = "";
	SDL_Texture* texture = nullptr;
	SDL_Color color;
	_TTF_Font* font = nullptr;
};

#endif // !__UI_TEXT__
