#ifndef SMALL_BALL_H
#define SMALL_BALL_H

#include "game/entities/level_object.h"
#include "geometry/vec2d.h"

class SmallBall : public LevelObject {
  int size;
  double angle;
  Vec2d position;
  Vec2d velocity;

 public:
  SmallBall(SDL_Renderer* renderer, double start_time_, int size_, int x, int y, Vec2d velocity_);
  void Update() override;
  void Render() override;
  bool IsCollided(Player* target) override;
  bool IsOutOfScreen() override;
  LevelObject* Clone() override;
};

#endif  // !SMALL_BALL_H