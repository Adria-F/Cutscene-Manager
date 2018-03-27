#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Input.h"

#define VSYNC true

j1Render::j1Render() : j1Module()
{
	name = "renderer";
	background.r = background.g = background.b = 0; background.a = 255;   //  black
}

// Destructor
j1Render::~j1Render() {}

// Called before render is available
bool j1Render::Awake(pugi::xml_node& config)
{
	LOG("Create SDL rendering context");

	// load flags
	Uint32 flags = SDL_RENDERER_ACCELERATED;

	if(config.child("vsync").attribute("value").as_bool(true) == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Using vsync");
	}

	renderer = SDL_CreateRenderer(App->win->window, -1, flags);

	if(renderer)
	{
		camera.w = App->win->screen_surface->w;
		camera.h = App->win->screen_surface->h;
		camera.x = camera.y = 0;

		culling_camera.w = App->win->screen_surface->w + 100;
		culling_camera.h = App->win->screen_surface->h + 100;
		culling_camera.x = camera.y = -100;
	}
	else
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
	
}

// Called before the first frame
bool j1Render::Start()
{
	LOG("render start");
	// back background
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

// Called each loop iteration
bool j1Render::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}


bool j1Render::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

// Called before quitting
bool j1Render::CleanUp()
{
	LOG("Destroying SDL render");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Load Game State
bool j1Render::Load(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();

	return true;
}

// Save Game State
bool j1Render::Save(pugi::xml_node& data) const
{
	pugi::xml_node cam = data.append_child("camera");

	cam.append_attribute("x") = camera.x;
	cam.append_attribute("y") = camera.y;

	return true;
}

iPoint j1Render::ScreenToWorld(int x, int y) const
{
	iPoint ret;
	int scale = App->win->GetScale();

	ret.x = (x - camera.x / scale);
	ret.y = (y - camera.y / scale);

	return ret;
}

void j1Render::SetBackgroundColor(SDL_Color color)
{
	background = color;
}

void j1Render::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

void j1Render::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

// Blit to screen
bool j1Render::Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section,SDL_RendererFlip flip, float speed, double angle, int pivot_x, int pivot_y) const
{
	uint scale = App->win->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * scale;
	rect.y = (int)(camera.y * speed) + y * scale;

	if(!section)			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	else
	{
		rect.w = section->w;
		rect.h = section->h;
	}

	rect.w *= scale;
	rect.h *= scale;

	SDL_Point* p = NULL;

	if(pivot_x != INT_MAX && pivot_y != INT_MAX)
	{
		SDL_Point pivot;
		pivot.x = pivot_x, pivot.y = pivot_y;
		p = &pivot;
	}

	if(SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool j1Render::DrawQuad(const SDL_Rect& rect, Color& color, bool filled, bool use_camera) const
{
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect rec(rect);
	if(use_camera)
	{
		rec.x = (int)(-camera.x + rect.x * scale);
		rec.y = (int)(-camera.y + rect.y * scale);
		rec.w *= scale, rec.h *= scale;
	}

	if((filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec))
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool j1Render::DrawLine(int x1, int y1, int x2, int y2, Color& color, bool use_camera) const
{
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int result = -1;

	if(use_camera)	result = SDL_RenderDrawLine(renderer, camera.x + x1 * scale, camera.y + y1 * scale, camera.x + x2 * scale, camera.y + y2 * scale);
	else			result = SDL_RenderDrawLine(renderer, x1 * scale, y1 * scale, x2 * scale, y2 * scale);

	if(result)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool j1Render::DrawCircle(int x, int y, int radius, Color& color, bool use_camera) const
{
	uint scale = App->win->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for(uint i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	int result = SDL_RenderDrawPoints(renderer, points, 360);

	if(result)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		return false;
	}

	return true;
}


void j1Render::MouseCameraMovement(float dt)
{
	int mousePosX, mousePosY, mov_x, mov_y;
	mousePosX = mousePosY = mov_x = mov_y = 0;

	App->input->GetMousePosition(mousePosX, mousePosY);

	if (mousePosX < 10 && camera.x < 0)								mov_x = 1000;  //Move left
	else if (mousePosX > camera.w - 10 && camera.x > -cam_limit_x)	 mov_x = -1000; //Move right
		
	if (mousePosY < 10 && camera.y < 0)								 mov_y = 1000;	 //Move up 
	else if (mousePosY > camera.h - 10 && camera.y > -cam_limit_y)	 mov_y = -1000; //Move down
		
	camera.x += mov_x * dt;
	camera.y += mov_y * dt;

	//clamp values to 0 and limit
	camera.x = (camera.x < -cam_limit_x ? -cam_limit_x : (camera.x > 0 ? 0 : camera.x));
	camera.y = (camera.y < -cam_limit_y ? -cam_limit_y : (camera.y > 0 ? 0 : camera.y));

	culling_camera.x = -camera.x - 100;
	culling_camera.y = -camera.y - 100;

}

bool j1Render::CullingCam(fPoint point) 
{
	SDL_Point p = { point.x, point.y };
	return SDL_PointInRect(&p, &culling_camera);
}