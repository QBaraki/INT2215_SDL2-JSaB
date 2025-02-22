#ifndef LEVEL_H
#define LEVEL_H

#include "SDL2/SDL.h"

#include "entities/player.h"

class Level {
  SDL_Renderer* renderer;
  Player* player;
  bool level_loaded;

 public:
  Level(SDL_Renderer* renderer_);
  ~Level();
  void InputHandler(SDL_Event* event);
  void Update(float delta_time);
  void Draw();
  void RenderLevel(float delta_time);
};

#endif  // !LEVEL_H