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
	//In your game probably, the entities are defined in an xml or generated procedurally, but to keep it simple, now we create them at the Start of the scene
	App->entitymanager->createAlly(475, 730); //Soldier ID 1
	App->entitymanager->createAlly(0, 0)->active = false; //Explorer ID 2
	App->entitymanager->createEnemy(0, 0)->active = false; //Orc ID 3
	App->entitymanager->createEnemy(0, 0)->active = false; //Orc ID 4
	App->entitymanager->createEnemy(0, 0)->active = false; //Orc ID 5
	//In your game probably all the audio files are loaded from an xml, but to keep it simple, now we load them at the Start of the scene
	App->audio->LoadMusic("Main_Theme.ogg"); //Music ID 1
	App->audio->LoadMusic("Victory_Theme.ogg"); //Music ID 2
	App->audio->LoadFx("ready_to_serve.wav"); //Fx ID 1
	App->audio->LoadFx("under_attack.wav"); //Fx ID 2
	App->audio->LoadFx("sword1.wav"); //Fx ID 3
	App->audio->LoadFx("sword2.wav"); //Fx ID 4
	App->audio->LoadFx("sword3.wav"); //Fx ID 5
	App->audio->LoadFx("orc_death.wav"); //Fx ID 6

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Scene update", Profiler::Color::Black);

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) return false;

	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN && !App->isGamePaused())
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
					App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
					break;
				case DEACTIVATE:
					App->audio->PlayMusic(0, 0);
					App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
					break;
				}
				break;
			case FX:
				switch ((*it_s)->type)
				{
				case ACTIVATE:
					App->audio->PlayFx((*it_s)->id);
					App->cutscenemanager->activeCutscene->forceStepFinish((*it_s)); //This kind of event has infinite duration, so force it to finish
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
