#ifndef __LIFEBAR_H__
#define __LIFEBAR_H__

#include "Image.h"

class LifeBar : public Image
{
public:
	LifeBar(SDL_Rect& position, iPoint positionOffset, SDL_Rect &image_section, bool draggable);
	~LifeBar();

	bool Draw(float dt);
	void ChangeSection(int remainingLives);
public:
	SDL_Rect fullHP;
	SDL_Rect threeLivesImageSection;
	SDL_Rect twoLivesImageSection;
	SDL_Rect lastLifeImageSection;

};

#endif