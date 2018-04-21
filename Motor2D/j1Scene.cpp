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
	App->entitymanager->createAlly(100, 100);
	App->entitymanager->createEnemy(100, 200);
	App->entitymanager->createAlly(100, 300);
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
		App->cutscenemanager->startCutscene("test");
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		App->cutscenemanager->startCutscene("test2");
	if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		App->cutscenemanager->startCutscene("test3");

	App->render->Blit(background, 0, 0);

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{

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
