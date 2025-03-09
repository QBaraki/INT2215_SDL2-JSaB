#ifndef SAW_H
#define SAW_H

#include "../level_object.h"

class Saw : public LevelObject {
  float angle;

 public:
  Saw(SDL_Renderer* renderer, double start_time_, int w, int h, int x, int y);
  void Update(float delta_time, [[maybe_unused]] float current_time);
  void Draw(SDL_Renderer* renderer);
};

#endif  // !SAW_H