#include "level.h"

#include "common.h"

#include <iostream>

#include "levels/00_playground.h"

Level::Level(SDL_Renderer* renderer_) {
  renderer = renderer_;
  current_time = 0;
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11, 0.28);
  level_loaded = false; // TODO: Change this to FALSE in future revision for level loading.
  music_player = nullptr;
}

Level::~Level() {
  delete player;
  for (LevelObject* o : objects) {
    delete o;
  }
  objects.clear();
  Mix_FreeMusic(music_player);
}

void Level::InputHandler(SDL_Event* event) {
  player->InputHandler(event);
}

void Level::Update(float delta_time, float current_time) {
  player->UpdatePosition(delta_time);
  for (LevelObject* o : objects) {
    o->Update(delta_time, current_time);
  }
}

void Level::Draw() {
  for (LevelObject* o : objects) {
    o->Draw(renderer);
  }
  player->Draw();
}

// Note that this function is being called EVERY FRAME (in src/game/game.cpp) when a level is running.
void Level::RenderLevel(float delta_time) {
  if (!level_loaded) {
    // Load the level here.
    level_loaded = PlaygroundLevel::LoadLevel(renderer, objects, music_player);
    if (Mix_PlayMusic(music_player, -1)) {
      throw std::runtime_error("Level::RenderLevel(): Failed to play music! SDL error: " + std::string(Mix_GetError()));
    }
  }
  Update(delta_time, current_time);
  Draw();
}