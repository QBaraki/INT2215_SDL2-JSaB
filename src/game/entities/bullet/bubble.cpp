#include "bubble.h"

#include <cmath>
#include <iostream>

#include "managers/texture.h"
#include "managers/time.h"

#include "small_ball.h"

Bubble::Bubble(SDL_Renderer* renderer, double pop_time_, int size_, int x, int y) : LevelObject(renderer) {
  texture = mTexture::LoadImage(renderer, "assets/bullets/bubble.png");
  angle = 0.0f;
  size = size_;
  countdown = 0.5f;
  pop_time = pop_time_;
  start_time = pop_time - countdown;
  position = Vec2d(x, y);
  SetRect(x, y, size, size);
}

void Bubble::Update() {
  angle -= 0.8f * mTime::delta_time;
  if (angle < 0.0) {
    angle += 360.0;
  }
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  countdown -= 0.001 * mTime::delta_time;
}

void Bubble::Render() {
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

bool Bubble::IsCollided(Player* target) {
  return false;
}

bool Bubble::IsOutOfScreen() {
  return false;
}

bool Bubble::IsDestroyed() {
  return countdown < 0.0f;
}

// TODO: Change this function with random angle spawn.
std::vector<LevelObject*> Bubble::Spawn() {
  Vec2d center = Vec2d(position.x + size / 2, position.y + size / 2);
  std::vector<LevelObject*> res;
  int count = 40;
  for (int i = 0; i < count; ++i) {
    double speed = 0.4f;
    double shoot_angle = (360.0f / count * i) * 3.14159 / 180.0f;
    double vx = std::cosf(shoot_angle) * speed;
    double vy = std::sinf(shoot_angle) * speed;
    //// std::cerr << (360.0f / count * i) << ' ' << shoot_angle << ' ' << std::cos(shoot_angle) << ' ' << std::sin(shoot_angle) << ' ' << vx << ' ' << vy << '\n';
    res.push_back(new SmallBall(renderer, pop_time, 10, center.x, center.y, {vx, vy}));
  }
  return res;
}

LevelObject* Bubble::Clone() {
  return new Bubble(*this);
}