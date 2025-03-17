#include "level.h"

#include "common.h"
#include "game/levels/00_Playground.h"

Level::Level(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11);
  music = nullptr;
  level_loaded = false;
  objects_count = current_index = 0;
}

Level::~Level() {
  delete player;
  for (LevelObject* o : loaded_objects) {
    delete o;
  }
  loaded_objects.clear();
  for (LevelObject* o : onscreen_objects) {
    delete o;
  }
  onscreen_objects.clear();
  Mix_FreeMusic(music);
}

void Level::EventHandler(SDL_Event& event) {
  player->EventHandler(event);
}

void Level::Update() {
  if (!level_loaded) {
    // Load the level here.
    level_loaded = PlaygroundLevel::LoadLevel(renderer, loaded_objects, music);
    objects_count = loaded_objects.size();
    current_index = 0;
    if (Mix_PlayMusic(music, -1)) {
      throw std::runtime_error("Level::RenderLevel(): Failed to play music! SDL error: " + std::string(Mix_GetError()));
    }
  }
  player->Update();
  // Check for pending objects
  double current_time = Mix_GetMusicPosition(music);
  while (current_index < objects_count && loaded_objects[current_index]->start_time <= current_time) {
    std::cout << "Level::Update(): Created object from address " << loaded_objects[current_index] << ".\n";
    std::cerr << "Time: " << loaded_objects[current_index]->start_time << ' ' << current_time << '\n';
    LevelObject* new_object = loaded_objects[current_index]->Clone();
    onscreen_objects.push_back(new_object);
    current_index++;
  }

  // Render objects
  for (LevelObject* o : onscreen_objects) {
    o->Update();
  }
}

void Level::Render() {
  if (!onscreen_objects.empty()) {
    for (LevelObject* o : onscreen_objects) {
      o->Render();
    }
  }
  player->Render();
}