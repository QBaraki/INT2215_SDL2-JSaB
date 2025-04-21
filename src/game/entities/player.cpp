#include "player.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

#include "common.h"
#include "managers/time.h"
#include "managers/texture.h"

#ifdef NDEBUG
#define cerr \
  if (0)     \
  std::cerr
#else
using std::cerr;
#endif  // NDEBUG

Player::Player(SDL_Renderer* renderer_, int size_, int x_, int y_)
    : MonoBehaviour(renderer_), angle(90.0), size(size_), start_position(Vec2d(x_, y_)) {
  hitpoint = 3;
  invi_time = 0;
  velocity = Vec2d(0, 0);
  position = start_position;
  rect.w = rect.h = size;
  is_moving = play_idle = false;
  dashing = false;
  dash_cooldown = buffer_frame = 0;
  // Init player 'texture'
  texture = mTexture::LoadImage(renderer, "assets/player/3_idle.png");
  idle_gif = nullptr;
  if (!texture) {
    throw std::runtime_error("Texture creation failed! SDL error: " + std::string(SDL_GetError()));
  }
  cerr << "Player::Player(): Player loaded\n";
  SDL_Rect r = {0, 0, size, size};
}

Player::~Player() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
  idle_gif = nullptr;
}

void Player::Update() {
  // Update position (and process with dashing)
  Vec2d true_velocity = velocity;
  if (buffer_frame != 0 && (true_velocity.x || true_velocity.y)) {
    buffer_frame = 0;
    dashing = true;
    dash_cooldown = 20;
  }
  if (dash_cooldown >= 16) {
    true_velocity *= 5.7f;
  }
  if (true_velocity.x && true_velocity.y) {
    position += true_velocity * mTime::delta_time * 0.86602540378f;
  } else {
    position += true_velocity * mTime::delta_time;
  }
  if (buffer_frame != 0) {
    buffer_frame--;
  } else if (dash_cooldown != 0) {
    assert(buffer_frame == 0);
    dash_cooldown--;
    if (!dash_cooldown) {
      dashing = false;
    }
  }
  int padding = 8;
  if (position.x < padding) {
    position.x = padding;
  }
  if (position.x + size + padding > WINDOW_WIDTH) {
    position.x = WINDOW_WIDTH - size - padding;
  }
  if (position.y < padding) {
    position.y = padding;
  }
  if (position.y + size + padding > WINDOW_HEIGHT) {
    position.y = WINDOW_HEIGHT - size - padding;
  }
  // Rotate player.
  double destination_angle;
  if (velocity.x < 0) {
    destination_angle = 270.0;
  } else {
    destination_angle = 90.0;
  }
  if (velocity.y < 0) {
    destination_angle += (velocity.x < 0 ? 45.0 : (velocity.x > 0 ? -45.0 : -90.0));
  } else if (velocity.y > 0) {
    destination_angle += (velocity.x > 0 ? 45.0 : (velocity.x < 0 ? -45.0 : 90.0));
  }
  if (angle != destination_angle) {
    if (destination_angle == 360.0) {
      destination_angle = 0.0;
    }
    double diff = destination_angle - angle;
    if (diff > 180.0) {
      diff -= 360.0;
    } else if (diff <= -180.0) {
      diff += 360.0;
    }
    if (diff > 0) {  // Rotate right.
      angle += 15;
    } else if (diff < 0) {  // Rotate left.
      angle -= 15;
    }
  }
  invi_time -= mTime::delta_time / 1000.0f;
  if (invi_time < 0.000000000f) {
    invi_time = 0.000000000f;
  }
}

void Player::Render() {
  if (is_moving && !velocity.x && !velocity.y) {
    is_moving = false;
    play_idle = true;
    idle_frame = 0;
    angle = 90.0f;
  }
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  // Play jelly effect when idle
  if (play_idle) {
    rect.x -= 4;
    rect.y -= 4;
    rect.w = size + 8;
    rect.h = size + 8;
    idle_gif = mTexture::LoadImage(renderer, "assets/player/" + std::to_string(hitpoint) + "_" + std::to_string(++idle_frame) + ".png");
    SDL_RenderCopy(renderer, idle_gif, nullptr, &rect);
    if (idle_frame == 14) {
      play_idle = false;
    }
    return;
  }
  // Stretch when moving
  if (!is_moving) {
    rect.w = rect.h = size;
  } else {
    rect.y -= 2;
    rect.w = size - 4;
    rect.h = size + 4;
  }
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

int Player::GetSize() {
  return size;
}

bool Player::IsInvi() {
  return invi_time > 0.000000000f;
}

bool Player::OnHit() {
  hitpoint--;
  if (hitpoint == 0) {
    return true;
  }
  texture = mTexture::LoadImage(renderer, "assets/player/" + std::to_string(hitpoint) + "_idle.png");
  invi_time = 3.000000000f;
  return false;
}

void Player::OnKeyUp(SDL_Event& event) {
  if (event.key.repeat) {
    return;
  }
  key[event.key.keysym.scancode] = false;
  if (direction_map.count(event.key.keysym.scancode)) {
    velocity -= direction_map[event.key.keysym.scancode];
    if (velocity.x || velocity.y) {
      is_moving = true;
      play_idle = false;
    }
  }
  //cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}

void Player::OnKeyDown(SDL_Event& event) {
  if (event.key.repeat) {
    return;
  }
  key[event.key.keysym.scancode] = true;
  if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
    if (dash_cooldown == 0) {
      buffer_frame = 5;
    }
  } 
  if (direction_map.count(event.key.keysym.scancode)) {
    velocity += direction_map[event.key.keysym.scancode];
    if (velocity.x || velocity.y) {
      is_moving = true;
      play_idle = false;
    }
  }
  //cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}

#undef cerr