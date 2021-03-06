// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <unordered_map>
#include <string>
#include <vector>

#include <iostream>
#include <sstream>


class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);
	
	void CheckColision(Actor* actor);

	int placar;
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	void drawText(SDL_Surface* screen, int x, int y, int w, int h, char* texto);
	void drawInteger(SDL_Surface* screen, int x, int y, int w, int h, int valor);


	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class SpriteComponent*> mPlacares;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	//// Text related
	//TTF_Font* font;
	//SDL_Color textColor;
	//SDL_Surface* textSurface;
	//SDL_Texture* Message;

	// Game-specific
	class Ship* mShip; // Player's ship
	class Ship* player2;
	class Spawner* mSpawner;
	class Actor* mBackground;
};
