#include "small_ball.h"

#include "common.h"
#include "managers/time.h"
#include "managers/texture.h"

SmallBall::SmallBall(SDL_Renderer* renderer, double start_time_, int size_, int x, int y, Vec2d velocity_) : LevelObject(renderer) {
  texture = mTexture::LoadImage(renderer, "assets/bullets/small_ball.png");
  angle = 0.0f;
  size = size_;
  start_time = start_time_;
  position = Vec2d(x, y);
  SetRect(x, y, size, size);
  velocity = velocity_;
}

void SmallBall::Update() {
  position += velocity * mTime::delta_time;
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
}

void SmallBall::Render() {
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

bool SmallBall::IsCollided(Player* target) {
  int player_radius = target->GetSize() / 2 - 5;
  Vec2d ball_mid = Vec2d(position.x + size, position.y + size);
  Vec2d player_mid = Vec2d(target->position.x + player_radius, target->position.y + player_radius);
  Vec2d diff = player_mid - ball_mid;
  int d = int((diff.x * diff.x) + (diff.y * diff.y));
  int r = player_radius + size;
  return d <= (r * r);
}

bool SmallBall::IsOutOfScreen() {
  if (position.x > WINDOW_WIDTH) {
    return true;
  }
  if (position.y > WINDOW_HEIGHT) {
    return true;
  }
  return (position.x + size < 0 || position.y + size < 0);
}

LevelObject* SmallBall::Clone() {
  return new SmallBall(*this);
}