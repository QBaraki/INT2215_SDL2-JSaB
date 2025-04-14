#ifndef CIRCLE_H
#define CIRCLE_H

#include <random>

#include <SDL2/SDL.h>

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class Circle : public LevelObject {
  SDL_Texture* white_texture;
  SDL_Texture* filled_texture;
  SDL_Texture* outline_texture;
  double angle, alpha_angle, original_radius, radius, radius_rate;
  double countdown, original_countdown, fatal_time, intact_time, bubbing_time, disappearing_time;
  bool intacted;
  Vec2d midpoint;
  std::mt19937 rng;

 public:
  Circle(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d midpoint_, double radius_, double radius_rate_);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  bool IsDestroyed() override;
  LevelObject* Clone() override;
};

#endif  // CIRCLE_H