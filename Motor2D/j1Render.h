#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Color.h"

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	iPoint j1Render::ScreenToWorld(int x, int y) const;
	// Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Color& color, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Color& color, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Color& color, bool use_camera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	//Move camera with cursor
	void MouseCameraMovement(float dt);
	bool CullingCam(fPoint point);

public:

	SDL_Renderer*	renderer;
	SDL_Rect		camera;
	SDL_Rect		culling_camera;
	SDL_Rect		viewport;
	SDL_Color		background;

	int cam_limit_x = 0;
	int cam_limit_y = 0;
};

#endif // __j1RENDER_H__