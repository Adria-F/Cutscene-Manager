#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Player.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Input.h"
#include "j1SceneChange.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"

j1Player::j1Player() : j1Module()
{
	name.create("player");
}

// Destructor
j1Player::~j1Player()
{}

// Called before render is available
bool j1Player::Awake(pugi::xml_node& config)
{
	bool ret = true;

	folder.create(config.child("folder").child_value());
	texture_path = config.child("sprite_sheet").attribute("source").as_string();

	Player.direction_x = 1;

	Player.jumpFX = config.child("jumpFX").attribute("source").as_string();
	Player.deathFX = config.child("deathFX").attribute("source").as_string();
	Player.landFX = config.child("landFX").attribute("source").as_string();
	Player.dashFX = config.child("dashFX").attribute("source").as_string();

	Player.jumpForce.x = config.child("jumpForce").attribute("x").as_int();
	Player.jumpForce.y = config.child("jumpForce").attribute("y").as_int();

	Player.maxSpeed.x = config.child("maxSpeed").attribute("x").as_int();
	Player.maxSpeed.y = config.child("maxSpeed").attribute("y").as_int();

	Player.dashingSpeed.x = config.child("dashingSpeed").attribute("x").as_int();
	Player.dashingSpeed.y = config.child("dashingSpeed").attribute("y").as_int();

	Player.dashingColliderDifference = config.child("dashingColliderDifference").attribute("value").as_int();
	Player.Dashtime = config.child("dashtime").attribute("value").as_int();

	Player.accel.x = config.child("accel").attribute("x").as_int();
	Player.accel.y = config.child("accel").attribute("y").as_int();

	Player.colOffset.x = config.child("colOffset").attribute("x").as_int();
	Player.colOffset.y = config.child("colOffset").attribute("y").as_int();

	return ret;
}

// Called before the first frame
bool j1Player::Start()
{
	Player.LoadPushbacks();

	Player.speed = { 0,0 };

	App->audio->LoadFx(Player.jumpFX.GetString());
	App->audio->LoadFx(Player.deathFX.GetString());
	App->audio->LoadFx(Player.landFX.GetString());
	App->audio->LoadFx(Player.dashFX.GetString());

	isPlayerAlive = true;
	
	Player.isJumping = false;
	Player.isDashing = false;
	Player.canDash = true;

	Player.current_animation = &Player.idle;

	//Sets the player in the start position
	for (p2List_item<ObjectsGroup*>* obj = App->map->data.objLayers.start; obj; obj = obj->next)
	{
		if (obj->data->name == ("Collisions"))
		{		
			for (p2List_item<ObjectsData*>* objdata = obj->data->objects.start;objdata;objdata = objdata->next)
			{
				if (objdata->data->name == ("Player"))
				{
					Player.collider.h = objdata->data->height;
					Player.collider.w = objdata->data->width;
					Player.collider.x = objdata->data->x;
					Player.collider.y = objdata->data->y;
				}
				else if (objdata->data->name == ("Start"))
				{
					Player.position = { objdata->data->x, objdata->data->y };
					Player.collider.x = Player.position.x + Player.colOffset.x;
					Player.collider.y = Player.position.y + Player.colOffset.y;
				}
			}
		}
	}
	Player.Player_tex = App->tex->Load(PATH(folder.GetString(), texture_path.GetString()));
	return true;
}

// Called each loop iteration
bool j1Player::PreUpdate()
{
	return true;
}

bool j1Player::Update(float dt)
{
	FlipImage();

	if (!Player.isDashing && Player.canDash)
	{
		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
			StartDashing();
	}
	else if (Player.isDashing)
	{
		Player.currentDashtime = SDL_GetTicks();

		if (Player.currentDashtime >= Player.initialDashtime + Player.Dashtime)
		{
			StopDashing();
		}
	}
	if (!Player.isDashing)
	{
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			Player.direction_x = 1, AddSpeed_X();
		else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			Player.direction_x = -1, AddSpeed_X();
		else
			ReduceSpeed();

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && Player.grounded)
		{
			AddSFX(1, 0);
			Player.isJumping = true;
			Player.maxSpeed.x += Player.jumpForce.x;
			Player.speed.x = Player.jumpForce.x*Player.direction_x; 
			Player.speed.y = Player.jumpForce.y;
		}

		Player.speed = ApplyGravity(Player.speed);
	}

	Player.speed = Collider_Overlay(Player.speed);

	ChangeAnimation();
	PlayerMovement(dt);
	return true;
}

bool j1Player::PostUpdate()
{
	if (!isPlayerAlive)
	{
		AddSFX(2, 0, 70);
		App->scenechange->ChangeMap(App->scene->currentMap, App->scene->fade_time);
	}

	PositionCameraOnPlayer();

	return true;
}

void j1Player::Draw()
{
	if(Player.flip)
		App->render->Blit(Player.Player_tex, Player.position.x, Player.position.y, &(Player.current_animation->GetCurrentFrame()), SDL_FLIP_HORIZONTAL, -1.0);
	else
		App->render->Blit(Player.Player_tex, Player.position.x, Player.position.y, &(Player.current_animation->GetCurrentFrame()), SDL_FLIP_NONE, -1.0);

}

// Called before quitting
bool j1Player::CleanUp()
{
	LOG("Deleting player");
	App->tex->UnLoad(Player.Player_tex);
	return true;
}

// Load Game State
bool j1Player::Load(pugi::xml_node& data)
{
	Player.position.x = data.child("position").attribute("x").as_int();
	Player.position.y = data.child("position").attribute("y").as_int();
	Player.speed.x = data.child("speed").attribute("x").as_int();
	Player.speed.y = data.child("speed").attribute("y").as_int();
	Player.collider.w = data.child("collider").attribute("width").as_int();
	Player.collider.h = data.child("collider").attribute("height").as_int();
	Player.collider.x = data.child("collider").attribute("x").as_int();
	Player.collider.y = data.child("collider").attribute("y").as_int();
	Player.grounded = data.child("grounded").attribute("value").as_bool();
	Player.isDashing = data.child("dashing").attribute("value").as_bool();
	Player.currentDashtime = data.child("dashtime").attribute("value").as_float();
	return true;
}

// Save Game State
bool j1Player::Save(pugi::xml_node& data) const
{
	data.append_child("position").append_attribute("x") = Player.position.x;
	data.child("position").append_attribute("y") = Player.position.y;
	data.append_child("speed").append_attribute("x") = Player.speed.x;
	data.child("speed").append_attribute("y") = Player.speed.y;
	data.append_child("collider").append_attribute("width") = Player.collider.w;
	data.child("collider").append_attribute("height") = Player.collider.h;
	data.child("collider").append_attribute("x") = Player.collider.x;
	data.child("collider").append_attribute("y") = Player.collider.y;
	data.append_child("grounded").append_attribute("value") = Player.grounded;
	data.append_child("dashing").append_attribute("value") = Player.isDashing;
	data.append_child("currentDashtime").append_attribute("value") = Player.currentDashtime;
	return true;
}

iPoint j1Player::Collider_Overlay(iPoint originalvec)
{
	Player.grounded = false;

	SDL_Rect CastCollider;
	CastCollider = Player.collider;
	CastCollider.x += originalvec.x;
	CastCollider.y += originalvec.y;

	SDL_Rect result;

	iPoint newvec = originalvec;
	for (p2List_item<ObjectsGroup*>* obj = App->map->data.objLayers.start; obj; obj = obj->next)
	{
		if (obj->data->name == ("Collisions"))
		{
			for (p2List_item<ObjectsData*>* objdata = obj->data->objects.start; objdata; objdata = objdata->next)
			{
				if (objdata->data->name == ("Floor"))
				{
					if (SDL_IntersectRect(&CastCollider, &CreateRect_FromObjData(objdata->data), &result))
					{
						newvec = AvoidCollision(newvec, result, objdata);
					}
				}
				else if (objdata->data->name == ("BGFloor")) //Only collides if the player is above the platform
				{
					if (Player.position.y + Player.collider.h + Player.colOffset.y <= objdata->data->y)
						if (SDL_IntersectRect(&CastCollider, &CreateRect_FromObjData(objdata->data), &result))
							if (result.h <= result.w || Player.position.x + Player.collider.w + Player.colOffset.x >= objdata->data->x)
								newvec.y -= result.h, BecomeGrounded();
				}
				else if (objdata->data->name == ("Dead")) //Detects when the player falls
				{
					if (SDL_IntersectRect(&CastCollider, &CreateRect_FromObjData(objdata->data), &result))
						isPlayerAlive = false;
				}
				else if (objdata->data->name == ("End")) //Detects when the player has finished the level
				{
					if (SDL_IntersectRect(&CastCollider, &CreateRect_FromObjData(objdata->data), &result) && !App->scenechange->fading)
						App->scene->to_end = true;
				}
				//The new trajectory of the player is adjousted for the next collision check
				if (SDL_IntersectRect(&CastCollider, &CreateRect_FromObjData(objdata->data), &result) && !App->scenechange->fading)
				{
					CastCollider.x -= (originalvec.x - newvec.x);
					CastCollider.y -= (originalvec.y - newvec.y);
				}
			}
		}
	}

	return newvec;
}

iPoint j1Player::AvoidCollision(iPoint newvec,const SDL_Rect result, p2List_item<ObjectsData*>* objdata)
{
	//Checks to determine the position of the player and the other collider. 
	//The speed is adjousted using the resultant Rect from the collision
	if (newvec.y > 0)
	{
		if (Player.position.y + Player.collider.h + Player.colOffset.y <= objdata->data->y)
		{
			if (newvec.x > 0)
			{
				if (result.h <= result.w || Player.position.x + Player.collider.w + Player.colOffset.x >= objdata->data->x)
					newvec.y -= result.h, BecomeGrounded();
				else
					newvec.x -= result.w;
			}
			else if (newvec.x < 0)
			{
				if (result.h <= result.w || Player.position.x + Player.colOffset.x >= objdata->data->x + objdata->data->width)
					newvec.y -= result.h, BecomeGrounded();
				else
					newvec.x += result.w;
			}
			else
				newvec.y -= result.h, BecomeGrounded();
		}
		else
		{
			if (newvec.x > 0)
				newvec.x -= result.w;
			else
				newvec.x += result.w;
		}

	}
	else if (newvec.y < 0)
	{
   		if (Player.position.y + Player.colOffset.y >= objdata->data->y + objdata->data->height)
		{
			if (newvec.x > 0)
			{
				if (result.h <= result.w || Player.position.x + Player.collider.w + Player.colOffset.x >= objdata->data->x)
					newvec.y += result.h;
				else
					newvec.x -= result.w;
			}
			else if (newvec.x < 0)
			{
				if (result.h <= result.w || Player.position.x + Player.colOffset.x <= objdata->data->x + objdata->data->width)
					newvec.y += result.h;
				else
					newvec.x += result.w;
			}
			else
				newvec.y += result.h;
		}
		else
		{
			if (newvec.x > 0)
				newvec.x -= result.w;
			else if (newvec.x < 0)
				newvec.x += result.w;
			else
				newvec.y += result.h;
		}
	}
	else
	{
		if (newvec.x > 0)
			newvec.x -= result.w;
		else if (newvec.x < 0)
			newvec.x += result.w;
	}
	return newvec;
}


SDL_Rect j1Player::CreateRect_FromObjData(ObjectsData* data)
{
	SDL_Rect ret;
	ret.x = data->x;
	ret.y = data->y;
	ret.h = data->height;
	ret.w = data->width;
	return ret;
}

void j1Player::FlipImage()
{
	if (Player.speed.x < 0)
		Player.flip = true;
	else if(Player.speed.x > 0)
		Player.flip = false;
}

void j1Player::BecomeGrounded()
{
	if (Player.isJumping)
	{
		Player.isJumping = false;
		Player.maxSpeed.x -= Player.jumpForce.x;
	}

	if (Player.current_animation == &Player.falling)
		AddSFX(3, 0);

	Player.canDash = true;
	Player.grounded = true;
	Player.jumping_up.Reset();
}

void j1Player::StartDashing()
{
	AddSFX(4, 0);
	Player.isDashing = true;
	Player.canDash = false;
	Player.speed.x = Player.dashingSpeed.x * Player.direction_x;
	Player.speed.y = Player.dashingSpeed.y;
	Player.collider.w += Player.dashingColliderDifference;
	Player.initialDashtime = SDL_GetTicks();
}

void j1Player::StopDashing()
{
	Player.isDashing = false;
	Player.collider.w -= Player.dashingColliderDifference;
	Player.dashing.Reset();
}

void j1Player::AddSpeed_X()
{
	Player.speed.x += Player.accel.x * Player.direction_x;

	if (Player.direction_x > 0)
	{
		if (Player.speed.x > Player.maxSpeed.x)
			Player.speed.x = Player.maxSpeed.x;
	}

	else
	{
		if (Player.speed.x < Player.direction_x*Player.maxSpeed.x)
			Player.speed.x = Player.direction_x*Player.maxSpeed.x;
	}
}

void j1Player::ReduceSpeed()
{
	if(Player.speed.x != 0)
	Player.speed.x -= Player.accel.x * Player.direction_x;
}

void j1Player::ChangeAnimation()
{
	if (!Player.isDashing)
	{
		if (Player.speed.y == 0 && Player.grounded)
			if (Player.speed.x == 0)
				Player.current_animation = &Player.idle;
			else
				Player.current_animation = &Player.running;
		else if (Player.speed.y < 0)
			Player.current_animation = &Player.jumping_up;
		else 
			Player.current_animation = &Player.falling;
	}

	else
		Player.current_animation = &Player.dashing;
}

void j1Player::AddSFX(int channel, int repeat, uint volume)
{
	App->audio->PlayFx(channel, repeat, volume);
}

void j1Player::PlayerMovement(float dt)
{
	Player.position += Player.speed;

	Player.collider.x = Player.position.x + Player.colOffset.x;
	Player.collider.y = Player.position.y + Player.colOffset.y;
}

iPoint j1Player::ApplyGravity(iPoint originalvec)
{
	originalvec.y += Player.accel.y;
	if (originalvec.y > Player.maxSpeed.y)
	{
		originalvec.y = Player.maxSpeed.y;
	}
	return originalvec;
}

void j1Player::Restart()
{
	//Same loop as int Start() to find the start zone
	for (p2List_item<ObjectsGroup*>* obj = App->map->data.objLayers.start; obj; obj = obj->next)
		if (obj->data->name == ("Collisions"))
			for (p2List_item<ObjectsData*>* objdata = obj->data->objects.start; objdata; objdata = objdata->next)
				if (objdata->data->name == ("Start"))
				{
					Player.position = { objdata->data->x, objdata->data->y };
					Player.collider.x = Player.position.x + Player.colOffset.x;
					Player.collider.y = Player.position.y + Player.colOffset.y;
					Player.speed.x = 0;
					Player.speed.y = 0;
					Player.current_animation = &Player.idle;
				}
	isPlayerAlive = true;
}

bool j1Player::PositionCameraOnPlayer()
{
	App->render->camera.x = Player.position.x - App->render->camera.w / 3;
	if (App->render->camera.x < 0)App->render->camera.x = 0;
	App->render->camera.y = Player.position.y - App->render->camera.h / 2;
	if (App->render->camera.y + App->win->height > App->map->data.height*App->map->data.tile_height)App->render->camera.y = App->map->data.height*App->map->data.tile_height - App->win->height;
	return true;
}

void PlayerData::LoadPushbacks()
{
	idle.PushBack({ 5, 17, 56, 73 });

	running.PushBack({ 89, 17, 60, 73 });
	running.PushBack({ 180, 17, 60, 73 });
	running.PushBack({ 277, 17, 60, 73 });
	running.PushBack({ 375, 17, 60, 73 });
	running.PushBack({ 470, 17, 60, 73 });
	running.PushBack({ 565, 17, 60, 73 });
	running.loop = true;
	running.speed = 0.1f;

	jumping_up.PushBack({ 672, 27, 53, 63 });
	jumping_up.PushBack({ 764, 0, 49, 75 });
	jumping_up.loop = false;
	jumping_up.speed = 0.2f;

	falling.PushBack({ 861, 17, 53, 73 });

	dashing.PushBack({ 635, 224, 79, 71 });
	dashing.PushBack({ 741, 226, 81, 69 });
	dashing.PushBack({ 834, 227, 82, 68 });
	dashing.PushBack({ 929, 228, 82, 67 });
	dashing.PushBack({ 390, 223, 73, 72 });
	dashing.PushBack({ 468, 219, 76, 69 }); 
	dashing.PushBack({ 548, 219, 76, 69 });
	dashing.loop = false;
	dashing.speed = 0.3f;
}
