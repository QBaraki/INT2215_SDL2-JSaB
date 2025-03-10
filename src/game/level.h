#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "entities/player.h"
#include "entities/level_object.h"

#include <vector>

class Level {
  SDL_Renderer* renderer;
  Player* player;
  bool level_loaded;
  float current_time;
  Mix_Music* music_player;
  std::vector<LevelObject*> objects;

 public:
  Level(SDL_Renderer* renderer_);
  ~Level();
  void InputHandler(SDL_Event* event);
  void Update(float delta_time, float current_time);
  void Draw();
  void RenderLevel(float delta_time);
};

#endif  // !LEVEL_H