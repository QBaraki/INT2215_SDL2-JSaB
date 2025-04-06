#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

#include "scenes/level.h"

#include "utils/log_utils.h"

class Game {
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool running;
  //Level* level;

 public:
  Game();
  ~Game();
  void InitGameLoop();
  void StopGameLoop();
  void EventHandler(SDL_Event& event);
  void Update();  // called every frame.
  void FixedUpdate();  // called every common.h:FIXED_UPDATE_TIME_STEP.
  void Render();
};

#endif  // !GAME_H