#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "geometry/vec2d.h"

class Player {
  struct Key {
    uint32_t binding = 0;
    bool is_down = false;
  };

  SDL_Renderer* renderer;
  SDL_Rect rect;
  Key key[4]; // key[0] = up, key[1] = left, key[2] = right, key[3] = down.
  int size;
  float speed;

 public:
  Vec2d position;
  Vec2d start_position;

  Player(SDL_Renderer* renderer_, int size_, int x_, int y_, float speed_);
  ~Player();
  void Draw();
  void HandleKeyUp(SDL_Event* event);
  void HandleKeyDown(SDL_Event* event);
  void InputHandler(SDL_Event* event);
  void UpdatePosition(float delta_time);
};

#endif  //!PLAYER_H