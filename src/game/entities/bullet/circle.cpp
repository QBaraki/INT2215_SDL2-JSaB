#include "circle.h"

#include "managers/time.h"

Circle::Circle(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d midpoint_, double radius_) : LevelObject(renderer) {
  fatal_time = fatal_time_;
  countdown = original_countdown = countdown_;
  intact_time = intact_time_;
  radius = radius_;
  midpoint = midpoint_;
  angle = 0;
  bubbing_time = disappearing_time = 0.07f;
}

void Circle::Update() {
  countdown -= mTime::delta_time;
  angle += 5;
  if (angle >= 360) {
    angle -= 360;
  }
  if (countdown > 0) {
    return;
  }
  bubbing_time -= mTime::delta_time;
  if (bubbing_time > 0.0f) {
    // Do something when "appearing" here
    ;
    return;
  } else {
    intact_time -= mTime::delta_time;
    if (intact_time <= 0.0f) {
      disappearing_time -= mTime::delta_time;
    } else {
      // Do something when intact here
      ;
      return;
    }
  }
  if (intact_time <= 0.0f && disappearing_time > 0.0f) {
    // Do something when "disappearing" here
    ;
  }
}

void Circle::Render() {
  ;
}

bool Circle::IsCollided(Player* target) {
  return false;
}

bool Circle::IsOutOfScreen() {
  return false;
}

bool Circle::IsDestroyed() {
  return fatal_time <= 0.0f && disappearing_time <= 0.0f;
}

LevelObject* Circle::Clone() {
  return new Circle(*this);
}