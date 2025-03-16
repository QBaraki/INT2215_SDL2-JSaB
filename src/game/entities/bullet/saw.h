#ifndef SAW_H
#define SAW_H

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class Saw : public LevelObject {
  int size;
  float angle;
  Vec2d position;
  Vec2d velocity;

 public:
  Saw(SDL_Renderer* renderer, double start_time_, int size_, int x, int y, Vec2d velocity_);
  void Update() override;
  void Render() override;
};

#endif  // !SAW_H