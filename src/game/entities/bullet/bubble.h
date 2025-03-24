#ifndef BUBBLE_H
#define BUBBLE_H

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

struct Bubble : public LevelObject {
  int size;
  double angle;
  double pop_time;
  double countdown;
  Vec2d position;

 public:
  Bubble(SDL_Renderer* renderer, double start_time_, int size_, int x, int y);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  bool IsDestroyed() override;
  std::vector<LevelObject*> Spawn() override;
  LevelObject* Clone() override;
};

#endif  // !BUBBLE_H