#include "p2Animation.h"

void Animation::PushBack(const SDL_Rect& rect)
{
	if (last_frame < MAX_FRAMES)
		frames[last_frame++] = rect;
	assert(last_frame < MAX_FRAMES);
}

SDL_Rect& Animation::GetCurrentFrame(float dt)
{
	float tmp = speed;
	current_frame += tmp * dt;

	if (current_frame < 0)
	{
		current_frame = 0;
	}

	if (current_frame >= last_frame)
	{
		current_frame = (loop) ? 0.0f : last_frame - 1;
		loops++;
	}

	return frames[(int)current_frame];
}

bool Animation::LoadAnimation(pugi::xml_node& data)
{
	int width = data.child("Width").attribute("value").as_int();
	int height = data.child("Height").attribute("value").as_int();
	int rows = data.child("Rows").attribute("value").as_int();
	int columns = data.child("Columns").attribute("value").as_int();
	for (int i = 0; i < rows; i++) 
		for (int j = 0; j < columns; j++) 
			PushBack({ width*j,height*i,width,height });
		
	speed = 0.2f;

	return true;
}

bool Animation::Finished() const				{ return loops > 0; }
void Animation::Reset()							{ current_frame = 0; }
float Animation::GetCurrentFrameinFloat()		{ return current_frame; }
int Animation::GetLastFrameinInt()				{ return last_frame;}
void Animation::ChangeCurrentFrame(float frame)	{ current_frame = frame; }