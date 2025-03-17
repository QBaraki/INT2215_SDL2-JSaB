#include "saw.h"

#include "common.h"
#include "managers/time.h"

Saw::Saw(SDL_Renderer* renderer_, double start_time_, int size_, int x, int y, Vec2d velocity_) : LevelObject(renderer_) {
  LoadImage(renderer, "assets/bullets/saw.png");
  angle = 0.0;
  size = size_;
  start_time = start_time_;
  position = Vec2d(x, y);
  SetRect(x, y, size, size);
  velocity = velocity_;
}

void Saw::Update() {
  angle -= 0.2 * my_time::delta_time;
  if (angle < 0.0) {
    angle += 360.0;
  }
  position += velocity * my_time::delta_time;
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
}

void Saw::Render() {
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

bool Saw::IsOutOfScreen() {
  if (position.x > WINDOW_WIDTH) {
    return true;
  }
  if (position.y > WINDOW_HEIGHT) {
    return true;
  }
  return (position.x + size < 0 || position.y + size < 0);
}

LevelObject* Saw::Clone() {
  return new Saw(*this);
}