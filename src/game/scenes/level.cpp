#include "level.h"

#include "common.h"
#include "game/levels/00_Playground.h"

Level::Level(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11);
  music = nullptr;
  level_loaded = false;
  objects_count = current_index = 0;
  previous_duration = -1.0f;
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
    return;
  }
  player->Update();

  // Check for "out-of-screen" and "is-destryoed" objects and delete them
  std::vector<std::list<LevelObject*>::iterator> target;
  for (std::list<LevelObject*>::iterator it = onscreen_objects.begin(); it != onscreen_objects.end(); it++) {
    if ((*it)->IsOutOfScreen() || (*it)->IsDestroyed()) {
      target.push_back(it);
    }
  }
  for (auto& it : target) {
    delete *it;
    // std::cerr << "Level::Update(): Deleted object with address " << (*it) << '\n';
    onscreen_objects.erase(it);
  }

  // Check for pending objects
  double current_duration = Mix_GetMusicPosition(music);
  while (current_index < objects_count && preloaded[current_index]->GetStartTime() <= current_duration) {
    onscreen_objects.push_back(preloaded[current_index]);
    //// std::cerr << "Level::Update(): Created object from address " << preloaded[current_index] << " to " << new_object << '\n';
    //// std::cerr << "Time: " << loaded_objects[current_index]->GetStartTime() << ' ' << current_duration << '\n';
    current_index++;
  }

  // Update objects and check collision
  for (LevelObject* o : onscreen_objects) {
    o->Update();
    if (o->IsCollided(player)) {
      // std::cerr << "Level::Update(): Player collided with object from address " << o << '\n';
    }
  }
}

void Level::FixedUpdate() {
  if (!level_loaded) {
    // Load the level here.
    PlaygroundLevel::LoadLevel(renderer, loaded_objects, music);
    objects_count = loaded_objects.size();
    current_index = 0;
    for (auto o : loaded_objects) {
      preloaded.push_back(o->Clone());
    }
    if (Mix_PlayMusic(music, -1)) {
      throw std::runtime_error("Level::RenderLevel(): Failed to play music! SDL error: " + std::string(Mix_GetError()));
    }
    level_loaded = true;
  }
}

void Level::Render() {
  if (!level_loaded) {
    return;
  }
  if (!onscreen_objects.empty()) {  // this is just for easier debugging purposes
    for (LevelObject* o : onscreen_objects) {
      o->Render();
    }
  }
  player->Render();
}