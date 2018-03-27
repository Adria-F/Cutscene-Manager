#include "j1App.h"
#include "Enemy.h"
#include "j1EntityController.h"
#include "j1Textures.h"
#include "j1Render.h"

#include "Enemy.h"

Enemy::~Enemy()
{

}

bool Enemy::Update(float dt)
{
	return true;
}

void Enemy::attackEntity(Entity* target)
{

}

Entity* Enemy::findTarget()
{
	return nullptr;
}
