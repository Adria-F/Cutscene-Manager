#include "LifeBar.h"
#include "p2log.h"
#include "j1Scene.h"
#include "j1App.h"

LifeBar::LifeBar(SDL_Rect& position, iPoint positionOffset, SDL_Rect & image_section, bool draggable) : Image(position, positionOffset, image_section), UIElement(position, draggable)
{
	fullHP = image_section;
}


LifeBar::~LifeBar()
{
}

bool LifeBar::Draw(float dt)
{
	ImageDraw(image_section, dt);
	return true;
}

void LifeBar::ChangeSection(int remainingLives)
{
	if (remainingLives == 3)
	{
		image_section = threeLivesImageSection;
		//LOG("entered");
		//LOG("threeLives x %i", threeLivesImageSection.x);
		//LOG("threeLives y %i", threeLivesImageSection.y);
		//LOG("threeLives h %i", threeLivesImageSection.h);
		//LOG("threeLives w %i", threeLivesImageSection.w);

	}
	else if (remainingLives == 2)
	{
		image_section = twoLivesImageSection;
	}
	else if (remainingLives == 1)
	{
		image_section = lastLifeImageSection;
	}
	else
	{
		image_section = fullHP;
	}
}
