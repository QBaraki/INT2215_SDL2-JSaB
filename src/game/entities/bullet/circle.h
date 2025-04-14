#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL2/SDL.h>

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

struct Circle : public LevelObject {
  int size;
  double angle, radius;
  double countdown, original_countdown, fatal_time, intact_time, bubbing_time, disappearing_time;
  Vec2d midpoint;

 public:
  Circle(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d midpoint_, double radius_);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  bool IsDestroyed() override;
  LevelObject* Clone() override;
};

#endif  // CIRCLE_H