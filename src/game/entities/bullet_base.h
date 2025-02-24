#ifndef BULLET_BASE_H
#define BULLET_BASE_H

#include <SDL2/SDL.h>

#include "player.h"

class BulletBase {
  SDL_Renderer* renderer;
  SDL_Rect position;

 public:
  BulletBase(SDL_Renderer* renderer_);
  ~BulletBase();
  bool CheckCollision(Player* player);
};

#endif  // !BULLET_BASE_H