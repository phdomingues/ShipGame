#include "Enemy.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Laser.h"
#include "Item.h"
#include "Timer.h"

#include <iostream>

Enemy::Enemy(Game* game)
	:Actor(game, "enemy", true)
	, mDownSpeed(100.0f)
	, laserAvailable(true)
	, laserRechargeTime(5000)
{
	// Create an animated sprite component for the Ship using images of the project
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Enemy01.png"),
		game->GetTexture("Assets/Enemy02.png"),
		game->GetTexture("Assets/Enemy03.png"),
		game->GetTexture("Assets/Enemy04.png"),
		game->GetTexture("Assets/Enemy05.png"),
		game->GetTexture("Assets/Enemy06.png")
	};
	//set the textures to the Ship vector of animated sprites
	asc->SetAnimTextures(anims);
	int randY = 0 + (rand() % (769));
	int randX = 700 + (rand() % (1024 - 701));
	this->SetPosition(Vector2((float)randX, (float)randY));

	std::cout << "Enemy instatiated" << std::endl;
	game->AddActor(this);
}

void Enemy::UpdateActor(float deltaTime)
{
	//update the Ship following modifications made by the ProcessKeyboard
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.y += mDownSpeed * deltaTime;
	// Restrict movements in bounds and select direction
	float bound_up = this->GetPosition().y - 100;
	float bound_down = this->GetPosition().y + 100;
	mDownSpeed = pos.y > bound_up || pos.x < bound_down ? mDownSpeed * -1 : mDownSpeed;
	// Restrict position to left half of screen
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	if (this->laserAvailable) {
		this->laserAvailable = false;
		Game* game = this->GetGame();
		game->AddActor(new Laser(game, this, this->GetPosition() - Vector2(50, 0), -1));
		Timer::timer(this->laserRechargeTime, &(Enemy::LaserRecharge), this);
	}
	SetPosition(pos);
}

void Enemy::Colided(Actor* target)
{
	Item* item = new Item(this->GetGame(), this, this->GetPosition(), -1);
	this->GetGame()->AddActor( item );
	delete this;
}

void Enemy::LaserRecharge(void* origin)
{
	Enemy* enemy = static_cast<Enemy*>(origin);
	enemy->laserAvailable = true;
}
