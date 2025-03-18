#include "saw.h"

#include "common.h"
#include "managers/time.h"
#include "managers/texture.h"

Saw::Saw(SDL_Renderer* renderer_, double start_time_, int size_, int x, int y, Vec2d velocity_) : LevelObject(renderer_) {
  texture = mTexture::LoadImage(renderer, "assets/bullets/saw.png");
  angle = 0.0f;
  size = size_;
  start_time = start_time_;
  position = Vec2d(x, y);
  SetRect(x, y, size, size);
  velocity = velocity_;
}

void Saw::Update() {
  angle -= 0.2f * mTime::delta_time;
  if (angle < 0.0) {
    angle += 360.0;
  }
  position += velocity * mTime::delta_time;
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
}

void Saw::Render() {
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

bool Saw::IsCollided(Player* target) {
  int player_radius = target->GetSize() / 2;
  int saw_radius = size / 2 - 2;
  Vec2d saw_mid = Vec2d(position.x + saw_radius, position.y + saw_radius);
  Vec2d player_mid = Vec2d(target->position.x + player_radius, target->position.y + player_radius);
  Vec2d diff = player_mid - saw_mid;
  int d = int((diff.x * diff.x) + (diff.y * diff.y));
  int r = player_radius + saw_radius;
  return d <= (r * r);
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