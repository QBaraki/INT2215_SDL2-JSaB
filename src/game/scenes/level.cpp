#include "level.h"

#include "common.h"
#include "managers/texture.h"
#include "managers/scene.h"
#include "game/scenes/pause_menu.h"
#include "game/levels/00_Playground.h"

#ifdef NDEBUG
#define cerr \
  if (0)     \
  std::cerr
#else
using std::cerr;
#endif  // NDEBUG

Level::Level(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  player = new Player(renderer, 22, 200, WINDOW_HEIGHT / 2 - 11);
  music = nullptr;
  level_loaded = false;
  player_died = false;
  objects_count = current_index = 0;
  previous_duration = -1.0f;
  loading_screen = mTexture::LoadImage(renderer, "assets/UI/loading_screen.png");
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
  if (!level_loaded) {
    return;
  }
  if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
    player->velocity = {0.0f, 0.0f};
    mScene::stack.emplace(new PauseMenu(renderer, this));
    return;
  }
  player->EventHandler(event);
}

// FIXME: Do NOT use Render here...
void Level::Update() {
  if (!level_loaded) {
    // Load the level here.
    SDL_RenderCopy(renderer, loading_screen, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    PlaygroundLevel::LoadLevel(renderer, loaded_objects, music);
    objects_count = loaded_objects.size();
    current_index = 0;
    for (auto o : loaded_objects) {
      preloaded.push_back(o->Clone());
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (Mix_PlayMusic(music, -1)) {
      throw std::runtime_error("Level::RenderLevel(): Failed to play music! SDL error: " + std::string(Mix_GetError()));
    }
#ifndef NDEBUG
    Mix_VolumeMusic(25);
    //Mix_SetMusicPosition(83.00f);
#endif  // NDEBUG
    level_loaded = true;
  }
  player->Update();

  // Check for "out-of-screen" and "is-destroyed" objects and delete them
  std::vector<std::list<LevelObject*>::iterator> target;
  for (std::list<LevelObject*>::iterator it = onscreen_objects.begin(); it != onscreen_objects.end(); it++) {
    if ((*it)->IsOutOfScreen() || (*it)->IsDestroyed()) {
      target.push_back(it);
    }
  }
  for (auto& it : target) {
    delete *it;
    cerr << "Level::Update(): Deleted object with address " << (*it) << '\n';
    onscreen_objects.erase(it);
  }

  // Check for pending objects
  double current_duration = Mix_GetMusicPosition(music);
  while (current_index < objects_count && preloaded[current_index]->GetStartTime() <= current_duration) {
    onscreen_objects.push_back(preloaded[current_index]);
    //cerr << "Level::Update(): Created object from address " << preloaded[current_index] << " to " << new_object << '\n';
    //cerr << "Time: " << loaded_objects[current_index]->GetStartTime() << ' ' << current_duration << '\n';
    current_index++;
  }

  // Update objects and check collision
  for (LevelObject* o : onscreen_objects) {
    o->Update();
    if (!player->IsInvi() && o->IsCollided(player)) {
      cerr << "Level::Update(): Player collided with object from address " << o << '\n';
      if (player->OnHit()) {
        cerr << "Level::Update(): Player died!\n";
        player_died = true;
        mScene::Pop();
        return;
      }
    }
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

#undef cerr