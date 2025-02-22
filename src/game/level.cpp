#include "level.h"

#include "common.h"

#include <iostream>

Level::Level(SDL_Renderer* renderer_) {
  renderer = renderer_;
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11, 0.28);
  level_loaded = true; // TODO: Change this to FALSE in future revision for level loading.
}

Level::~Level() {
  delete player;
}

void Level::InputHandler(SDL_Event* event) {
  player->InputHandler(event);
}

void Level::Update(float delta_time) {
  player->UpdatePosition(delta_time);
}

void Level::Draw() {
  player->Draw();
}

// Note that this function is being called EVERY FRAME (in src/game/game.cpp) when a level is running.
void Level::RenderLevel(float delta_time) {
  if (!level_loaded) {
    // Load the level here.
    level_loaded = true;
  }
  Update(delta_time);
  Draw();
}