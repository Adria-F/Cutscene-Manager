#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "j1CutsceneManager.h"

j1Scene::j1Scene() : j1Module() { name = "scene"; }

// Destructor
j1Scene::~j1Scene() {}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");

	return true;
}

// Called before the first frame
bool j1Scene::Start()
{
	background = App->tex->Load("maps/background.png");
	//In your game probably, the entities are defined in an xml or generated procedurally, but to keep it simple, now we create them from the Start of the scene
	App->entitymanager->createAlly(100, 100);
	App->entitymanager->createEnemy(100, 200);
	//In your game probably all the audio files are loaded from an xml, but to keep it simple, now we load them from the Start of the scene
	App->audio->LoadMusic("Main_Theme.ogg"); //Music id 1
	App->audio->LoadMusic("Victory_Theme.ogg"); //Music id 2
	App->audio->LoadFx("ready_to_serve.wav"); //Fx id 1
	App->audio->LoadFx("under_attack.wav"); //Fx id 2

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Scene update", Profiler::Color::Black);

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) return false;

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		App->cutscenemanager->startCutscene("attack");

	App->render->Blit(background, 0, 0);

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	if (App->cutscenemanager->activeCutscene != nullptr)
	{
		for (std::list<Step*>::iterator it_s = App->cutscenemanager->activeCutscene->activeSteps.begin(); it_s != App->cutscenemanager->activeCutscene->activeSteps.end(); it_s++)
		{
			switch ((*it_s)->element)
			{
			case MUSIC:
				switch ((*it_s)->type)
				{
				case ACTIVATE:
					App->audio->PlayMusic((*it_s)->id, 0);
					App->cutscenemanager->activeCutscene->activeSteps.erase(it_s);
					break;
				case DEACTIVATE:
					App->audio->PlayMusic(0, 1);
					App->cutscenemanager->activeCutscene->activeSteps.erase(it_s);
					break;
				}
				break;
			case FX:
				switch ((*it_s)->type)
				{
				case ACTIVATE:
					App->audio->PlayFx((*it_s)->id);
					App->cutscenemanager->activeCutscene->activeSteps.erase(it_s);
					break;
				}
				break;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool j1Scene::OnEvent(UIElement* element, int eventType)
{
	return true;
}

bool j1Scene::Load(pugi::xml_node& data)
{
	return true;
}

bool j1Scene::Save(pugi::xml_node& data) const
{
	return true;
}
