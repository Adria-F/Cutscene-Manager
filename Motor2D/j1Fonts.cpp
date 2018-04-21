#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_ttf\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

j1Fonts::j1Fonts() : j1Module() { name = "fonts"; }

// Destructor
j1Fonts::~j1Fonts(){}

// Called before render is available
bool j1Fonts::Awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");

	if (TTF_Init() != -1)
	{
		const char* path = conf.child("default_font").attribute("file").as_string(DEFAULT_FONT);
		int size = conf.child("default_font").attribute("size").as_int(DEFAULT_FONT_SIZE);
		default_font = Load(path, size);
		return (default_font);
	}
	else LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

	return false;
}

// Called before quitting
bool j1Fonts::CleanUp()
{
	LOG("Freeing True Type fonts and library");

	for (std::list<_TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); it++) 
		TTF_CloseFont(*it);

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
TTF_Font* const j1Fonts::Load(const char* path, int size)
{
	TTF_Font* font = nullptr;

	if(font = TTF_OpenFont(path, size)) fonts.push_back(font);
	else	LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());

	return font;
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, SDL_Color* color , TTF_Font* font)
{
	SDL_Texture* ret = nullptr;
	SDL_Surface* surface = TTF_RenderText_Blended((font) ? font : default_font, text, *color);
	
	if(surface)
	{
		ret = App->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}
	else LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

	return ret;
}

// calculate size of a text
bool j1Fonts::CalcSize(const char* text, int& width, int& height, _TTF_Font* font) const
{
	if (TTF_SizeText((font) ? font : default_font, text, &width, &height) == 0)
	{
		LOG("Unable to calc size of text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

void j1Fonts::CloseFont(_TTF_Font * font)
{
	if (font)
	{
		TTF_CloseFont(font);
		fonts.remove(font);
	}
}
