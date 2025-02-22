#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

#include "utils/log_utils.h"

class Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  Status status;

 public:
  Game();
  ~Game();
  void InitGameLoop();
};

#endif  // !GAME_H