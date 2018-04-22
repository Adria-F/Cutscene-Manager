#include "p2Defs.h"
#include "p2Log.h"
#include "j1Audio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


j1Audio::j1Audio() : j1Module() { name = "audio"; }

// Destructor
j1Audio::~j1Audio() {}

// Called before render is available
bool j1Audio::Awake(pugi::xml_node& config)
{
	musicVolumeModifier = config.child("music").child("musicVolumeModifier").attribute("value").as_float();
	sfxVolumeModifier = config.child("sfx").child("sfxVolumeModifier").attribute("value").as_float();

	LOG("Loading Audio Mixer");
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (active = false);
	}

	// load support for the OGG audio format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		return (active = false);
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return (active = false);
	}

	return true;
}

// Called before quitting
bool j1Audio::CleanUp()
{
	if (active)
	{
		LOG("Freeing sound FX, closing Mixer and Audio subsystem");

		for (int i = 0; i < music.size(); i++)   Mix_FreeMusic(music[i]);
		music.clear();

		for (int i = 0; i < fx.size(); i++)   Mix_FreeChunk(fx[i]);
		fx.clear();

		Mix_CloseAudio();
		Mix_Quit();
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
	}
	return true;
}

bool j1Audio::Save(pugi::xml_node & config) const
{
	config.append_child("musicVolumeModifier").append_attribute("value") = musicVolumeModifier;
	config.append_child("sfxVolumeModifier").append_attribute("value") = sfxVolumeModifier;
	return true;
}

bool j1Audio::Load(pugi::xml_node & config)
{
	musicVolumeModifier = config.child("musicVolumeModifier").attribute("value").as_float();
	sfxVolumeModifier = config.child("sfxVolumeModifier").attribute("value").as_float();

	Mix_VolumeMusic(128 * musicVolumeModifier);

	return true;
}

unsigned int j1Audio::LoadMusic(const char* path)
{
	if (active) {

		if (_Mix_Music* chunk = Mix_LoadMUS(PATH(MUSIC_FOLDER, path)))
		{
			music.push_back(chunk);
			return music.size();
		}
		else LOG("Cannot load ogg %s. Mix_GetError(): %s", path, Mix_GetError());
	}

	return 0;
}

// Play a music file
bool j1Audio::PlayMusic(unsigned int id, uint fade_time)
{
	bool ret = false;

	if (fade_time)
		Mix_FadeOutMusic(int(fade_time * 1000.0f));
	else			
		Mix_HaltMusic();

	if (id > 0 && id <= music.size() && active)
	{
		
		if (fade_time)	ret = (Mix_FadeInMusic(music[id-1], -1, fade_time * 1000) < 0);
		else			ret = (Mix_PlayMusic(music[id-1], -1) < 0);

	}

	return ret;

}

// Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{
	if (active) {

		if (Mix_Chunk* chunk = Mix_LoadWAV(PATH(FX_FOLDER, path)))
		{
			fx.push_back(chunk);
			return fx.size();
		}
		else LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}

	return 0;
}

// Play WAV
bool j1Audio::PlayFx(unsigned int id, int repeat, uint volume)
{
	if(id > 0 && id <= fx.size() && active)
	{
		Mix_VolumeChunk(fx[id - 1], volume*sfxVolumeModifier);
		Mix_PlayChannel(-1, fx[id - 1], repeat);
		return true;
	}

	return false;
}

void j1Audio::ModifyMusicVolume(int value)
{
	musicVolumeModifier = (float)value/100;
	if (musicVolumeModifier < 0)musicVolumeModifier = 0;
	else if (musicVolumeModifier > 1)musicVolumeModifier = 1;

	Mix_VolumeMusic(128 * musicVolumeModifier);
}

void j1Audio::ModifySFXVolume(int value)
{
	sfxVolumeModifier = (float)value / 100;
	if (sfxVolumeModifier < 0)sfxVolumeModifier = 0;
	else if (sfxVolumeModifier > 1)sfxVolumeModifier = 1;
}
