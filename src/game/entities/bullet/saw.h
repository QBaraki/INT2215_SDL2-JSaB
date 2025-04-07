#ifndef SAW_H
#define SAW_H

#include <SDL2/SDL.h>

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class Saw : public LevelObject {
  int size;
  double angle;
  double white_time;
  SDL_Texture* spawn_texture;
  Vec2d velocity;

 public:
  Saw(SDL_Renderer* renderer, double start_time_, int size_, int x, int y, Vec2d velocity_);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  LevelObject* Clone() override;
};

#endif  // !SAW_H