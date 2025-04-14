#ifndef BUBBLE_H
#define BUBBLE_H

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class Bubble : public LevelObject {
  int size;
  double angle;
  double pop_time;
  double countdown;

 public:
  Bubble(SDL_Renderer* renderer, double pop_time_, int size_, int x, int y);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  bool IsDestroyed() override;
  std::vector<LevelObject*> Spawn() override;
  LevelObject* Clone() override;
};

#endif  // !BUBBLE_H