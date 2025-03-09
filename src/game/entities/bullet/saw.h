#ifndef SAW_H
#define SAW_H

#include "../level_object.h"
#include "geometry/vec2d.h"

class Saw : public LevelObject {
  float angle;
  Vec2d position;
  Vec2d velocity;

 public:
  Saw(SDL_Renderer* renderer, double start_time_, int w, int h, int x, int y, Vec2d velocity_);
  void Update(float delta_time, [[maybe_unused]] float current_time);
  void Draw(SDL_Renderer* renderer);
};

#endif  // !SAW_H