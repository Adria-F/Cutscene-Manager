#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "p2Animation.h"
#include "j1Module.h"

struct SDL_Texture;
struct ObjectsData;

struct PlayerData
{			
	bool			canDash;
	bool			isJumping;
	bool			isDashing;
	bool			flip;
	int				direction_x;
	iPoint			jumpForce;
	bool			grounded;
	float			Dashtime;
	float			currentDashtime;
	float			initialDashtime;
	iPoint			colOffset;
	iPoint			speed;
	iPoint			maxSpeed;
	iPoint			dashingSpeed;
	int				dashingColliderDifference;
	iPoint			accel;
	iPoint			position;
	SDL_Rect		collider;
	Animation*		current_animation;
	Animation		idle;
	Animation		running;
	Animation		jumping_up;
	Animation		falling;
	Animation		dashing;
	SDL_Texture*	Player_tex;
	p2SString		jumpFX;
	p2SString		deathFX;
	p2SString		landFX;
	p2SString		dashFX;
	

	void LoadPushbacks();
};

class j1Player : public j1Module
{
	//-------------Functions-----------------
public:

	j1Player();

	// Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	//Called before the first frame
	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called each loop iteration
	void Draw();

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	//Detects if the player's collider is going to collide in the next frame and acts in consequence
	iPoint Collider_Overlay(iPoint originalvec);

	//Called if the player's collider is going to collide with unpasable terrain, adjousts the player's speed to avoid it
	iPoint AvoidCollision(iPoint newvec, const SDL_Rect result, p2List_item<ObjectsData*>* objdata);

	//Returns the rect of the Object passed using its data
	SDL_Rect CreateRect_FromObjData(ObjectsData* data);

	// Called before quitting
	bool CleanUp();

	//Decides if the sprite needs to be flipped
	void FlipImage();

	 //When called, sets the corresponding bools and plays the sfx
	void BecomeGrounded();

	//When called, sets the player in the dash state
	void StartDashing();

	//When called, sets the corresponding bools and readjousts the player's collider
	void StopDashing();

	//Increased the speed according to the player's acceleration
	void AddSpeed_X();

	//Reduces the player's speed according to the player's acceleration
	void ReduceSpeed();

	//Changes the animation according to the player's state
	void ChangeAnimation();

	//Plays the indicated sfx
	void AddSFX(int channel, int repeat, uint volume = 128);

	//Adds the speed to the player's position and checks if its out of the boundaries
	void PlayerMovement(float dt);

	//Applies the gravity (acceleration.y) and checks if the speed is out of thee boundaries
	iPoint ApplyGravity(iPoint originalvec);

	//Positions the player in the start of the current level
	void Restart();

	//Centers the camera on the player and checks if it is out of the boundaries
	bool PositionCameraOnPlayer();

private:

//-------------Variables-----------------
public:

	bool			isPlayerAlive;

private:

	PlayerData		Player;
	p2SString		folder;
	p2SString		texture_path;
};

#endif // __j1MAP_H__