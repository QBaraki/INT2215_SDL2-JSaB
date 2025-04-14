#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class Block : public LevelObject {
  double fatal_time, countdown, original_countdown, white_time, intact_time;
  double disappearing_time;
  int w, h;
  SDL_Rect rect;
  bool intacted;

 public:
  Vec2d top_left, bottom_right;

  Block(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d top_left_, Vec2d bottom_right_);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  bool IsDestroyed() override;
  LevelObject* Clone() override;
};

#endif  // !BLOCK_H