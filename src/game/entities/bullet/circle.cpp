#include "circle.h"

#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

#include "managers/time.h"
#include "managers/texture.h"

Circle::Circle(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d midpoint_, double radius_, double radius_rate_) : LevelObject(renderer) {
  white_texture = mTexture::LoadImage(renderer, "assets/bullets/circle_white.png");
  filled_texture = mTexture::LoadImage(renderer, "assets/bullets/circle.png");
  outline_texture = mTexture::LoadImage(renderer, "assets/bullets/circle_outline.png");
  fatal_time = fatal_time_;
  countdown = original_countdown = countdown_;
  start_time = fatal_time - countdown;
  intact_time = intact_time_;
  radius = original_radius = radius_;
  radius_rate = radius_rate_;
  intacted = false;
  midpoint = midpoint_;
  angle = alpha_angle = 0.0f;
  bubbing_time = disappearing_time = 0.06f;
  rect.x = static_cast<int>(midpoint.x - original_radius);
  rect.y = static_cast<int>(midpoint.y - original_radius);
  rect.w = rect.h = static_cast<int>(2 * original_radius);
  original_radius *= 1.2f;
  rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
}

void Circle::Update() {
  countdown -= mTime::delta_time / 1000.0f;
  angle += 1.5f;
  if (angle >= 360.0f) {
    angle -= 360.0f;
  }
  if (countdown > 0.0f) {
    texture = outline_texture;
    return;
  }
  texture = filled_texture;
  intacted = true;
  bubbing_time -= mTime::delta_time / 1000.0f;
  alpha_angle += 6.5f;
  if (alpha_angle >= 360.0f) {
    alpha_angle -= 360.0f;
  }
  if (bubbing_time > 0.0f) {
    // "appearing" here
    radius = original_radius * (0.07f - bubbing_time) / 0.07f;
    return;
  } else {
    intact_time -= mTime::delta_time / 1000.0f;
    if (intact_time <= 0.0f) {
      disappearing_time -= mTime::delta_time / 1000.0f;
    } else {
      // intact here
      radius += radius_rate;
      original_radius = radius;
      return;
    }
  }
  if (intact_time <= 0.0f && disappearing_time > 0.0f) {
    // "disappearing" here
    radius = original_radius * disappearing_time / 0.07f;
  }
}

void Circle::Render() {
  if (!intacted) {
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
    return;
  }
  SDL_Rect r = rect;
  int cox = std::uniform_int_distribution<int>(-3, 3)(rng);
  int coy = std::uniform_int_distribution<int>(-3, 3)(rng);
  r.x = static_cast<int>(midpoint.x - radius) + cox;
  r.y = static_cast<int>(midpoint.y - radius) + coy;
  r.w = r.h = static_cast<int>(2 * radius);
  SDL_RenderCopy(renderer, texture, nullptr, &r);
  SDL_SetTextureAlphaMod(white_texture, 120 + 50 * std::abs(std::cos(alpha_angle * 3.14159 / 180.0f)));
  SDL_RenderCopy(renderer, white_texture, nullptr, &r);
}

bool Circle::IsCollided(Player* target) {
  if (!intacted) {
    return false;
  }
  int player_radius = target->GetSize() / 2 - 5;
  Vec2d player_mid = Vec2d(target->position.x + player_radius, target->position.y + player_radius);
  Vec2d diff = player_mid - midpoint;
  int d = int((diff.x * diff.x) + (diff.y * diff.y));
  int r = player_radius + radius;
  return d <= (r * r);
}

bool Circle::IsOutOfScreen() {
  return false;
}

bool Circle::IsDestroyed() {
  //std::cerr << bubbing_time << ' ' << intact_time << ' ' << disappearing_time << '\n';
  return intact_time <= 0.0f && disappearing_time <= 0.0f;
}

LevelObject* Circle::Clone() {
  return new Circle(*this);
}