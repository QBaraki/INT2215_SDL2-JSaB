#include "saw.h"

Saw::Saw(SDL_Renderer* renderer, double start_time_, int w, int h, int x, int y) {
  LoadImage(renderer, "assets/bullets/saw.png");
  angle = 0;
  SetRect(x, y, w, h);
}

void Saw::Update(float delta_time, float current_time) {
  angle += 10;
}

void Saw::Draw(SDL_Renderer* renderer) {
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}