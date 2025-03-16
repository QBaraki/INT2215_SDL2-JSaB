#include "level.h"

#include "common.h"

#include "game/levels/00_Playground.h"

Level::Level(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11);
  music_player = nullptr;
  level_loaded = false;
}

Level::~Level() {
  delete player;
  for (LevelObject* o : objects) {
    delete o;
  }
  objects.clear();
  Mix_FreeMusic(music_player);
}

void Level::EventHandler(SDL_Event& event) {
  player->EventHandler(event);
}

void Level::Update() {
  player->Update();
  for (LevelObject* o : objects) {
    o->Update();
  }
}

void Level::Render() {
  if (!level_loaded) {
    // Load the level here.
    level_loaded = PlaygroundLevel::LoadLevel(renderer, objects, music_player);
    if (Mix_PlayMusic(music_player, -1)) {
      throw std::runtime_error("Level::RenderLevel(): Failed to play music! SDL error: " + std::string(Mix_GetError()));
    }
  }
  for (LevelObject* o : objects) {
    o->Render();
  }
  player->Render();
}