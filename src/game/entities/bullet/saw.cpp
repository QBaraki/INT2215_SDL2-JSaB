#include "saw.h"

#include "managers/time.h"

Saw::Saw(SDL_Renderer* renderer_, double start_time_, int w, int h, int x, int y, Vec2d velocity_) : LevelObject(renderer_) {
  LoadImage(renderer, "assets/bullets/saw.png");
  angle = 0.0;
  position = Vec2d(x, y);
  SetRect(x, y, w, h);
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