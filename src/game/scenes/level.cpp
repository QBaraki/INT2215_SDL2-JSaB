#include "level.h"

#include "common.h"

Level::Level(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11);
  level_loaded = false;  // TODO: Change this to FALSE in future revision for level loading.
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

void Level::Update() {}

void Level::Render() {
  for (LevelObject* o : objects) {
    ;
  }
  player->Render();
}