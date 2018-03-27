#include "Scrollbar.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "Window.h"

Scrollbar::Scrollbar()
{
}

Scrollbar::Scrollbar(SDL_Rect & scroller_image, bool moves_vertically, int min, SDL_Rect & pos, iPoint Sliderrelativepos, SDL_Rect image_section, ScrollbarType type, bool draggable) : Image(pos,{0,0},image_section),UIElement(pos,draggable)
{
	this->Image_from_atlas = true;
	this->UItype = SCROLLBAR;
	this->moves_vertically = moves_vertically;
	this->type = type;
	if (moves_vertically)
	{
		this->min =pos.y+ Sliderrelativepos.y + min - scroller_image.h;
		max =pos.y+ Sliderrelativepos.y;
	}
	else
	{
		this->min =pos.x + Sliderrelativepos.x + min - scroller_image.w;
		max =pos.x+ Sliderrelativepos.x;
	}

	sliderPos.x = pos.x + Sliderrelativepos.x;
	sliderPos.y = pos.y + Sliderrelativepos.y;
	this->scroller_image = scroller_image;
	collider.x = pos.x + Sliderrelativepos.x;
	collider.y = pos.y + Sliderrelativepos.y;
	collider.w = scroller_image.w;
	collider.h = scroller_image.h;
	App->input->GetMousePosition(mouseLastFrame.x, mouseLastFrame.y);
}




Scrollbar::~Scrollbar()
{
}

bool Scrollbar::PreUpdate()
{
	SDL_Point currentMousepos;
	App->input->GetMousePosition(currentMousepos.x, currentMousepos.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		if(SDL_PointInRect(&currentMousepos, &collider) || beingSlided)
			{
			if (moves_vertically)
			{
				int movement = currentMousepos.y - mouseLastFrame.y;

					sliderPos.y += movement;
					if (sliderPos.y > min)
						sliderPos.y = min;
					if (sliderPos.y < max)
						sliderPos.y = max;
					collider.y += movement;
					if (collider.y > min)
						collider.y = min;
					if (collider.y < max)
						collider.y = max;

			}

			else
			{
				int movement = currentMousepos.x - mouseLastFrame.x;
			
					sliderPos.x += movement;
					if (sliderPos.x > min)
						sliderPos.x = min;
					if (sliderPos.x < max)
						sliderPos.x = max;
					collider.x += movement;
					if (collider.x > min)
						collider.x = min;
					if (collider.x < max)
						collider.x = max;
				
			}

			beingSlided = true;
			ModifySmth();
			}
		}
	else
	beingSlided = false;
	

	App->input->GetMousePosition(mouseLastFrame.x, mouseLastFrame.y);
	return true;
}

bool Scrollbar::CleanUp()
{
	return true;
}

void Scrollbar::ModifySmth()
{
	switch (type)
	{
	case SCROLLBAR_DEFAULT:
		break;
	case MUSICVOLUME:
		App->audio->ModifyMusicVolume(get_1to100value());
		break;
	case SFXVOLUME:
		App->audio->ModifySFXVolume(get_1to100value());
		break;
	default:
		break;
	}
}

bool Scrollbar::Draw(float dt)
{
	ImageDraw(image_section,dt);
	iPoint tmp = App->render->ScreenToWorld(sliderPos.x , sliderPos.y);

	if (!In_window)
	{
		App->render->Blit(image, tmp.x, tmp.y, &scroller_image);
	}

	if (In_window)
	{
		App->render->Blit(image, tmp.x+winElement->relativePosition.x, tmp.y+winElement->relativePosition.y, &scroller_image);
	}
	return true;
}

int Scrollbar::get_1to100value()
{
	int _100 = max - min;
	int _1 = _100 / 100;
	int current;
	if (moves_vertically)
	{
		current = sliderPos.y - min;
	}
	else
		current = sliderPos.x - min;

	int ret = current / _1;
	return ret;
}
