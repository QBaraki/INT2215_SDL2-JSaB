#include "saw.h"

Saw::Saw(SDL_Renderer* renderer, double start_time_, int w, int h, int x, int y, Vec2d velocity_) {
  LoadImage(renderer, "assets/bullets/saw.png");
  angle = 0.0;
  position = Vec2d(x, y);
  SetRect(x, y, w, h);
  velocity = velocity_;
}

void Saw::Update(float delta_time, float current_time) {
  angle -= 0.2 * delta_time;
  if (angle < 0.0) {
    angle += 360.0;
  }
  position += velocity * delta_time;
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
}

void Saw::Draw(SDL_Renderer* renderer) {
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}