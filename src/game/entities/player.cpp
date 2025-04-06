#include "player.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

#include "common.h"
#include "managers/time.h"
#include "managers/texture.h"

Player::Player(SDL_Renderer* renderer_, int size_, int x_, int y_)
    : MonoBehaviour(renderer_), angle(90.0), size(size_), start_position(Vec2d(x_, y_)) {
  velocity = Vec2d(0, 0);
  position = start_position;
  rect.w = rect.h = size;
  is_moving = play_idle = false;
  dashing = false;
  dash_cooldown = dash_offset = 0;
  // Init player 'texture'
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
  idle_gif = nullptr;
  if (!texture) {
    throw std::runtime_error("Texture creation failed! SDL error: " + std::string(SDL_GetError()));
  }
  std::cerr << "Player::Player(): Player loaded\n";
  SDL_Rect r = {0, 0, size, size};
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &r);
  SDL_SetRenderTarget(renderer, nullptr);
}

Player::~Player() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
  idle_gif = nullptr;
}

void Player::Update() {
  // Update position (and process with dashing)
  Vec2d true_velocity = velocity;
  if (dash_offset != 0 && (true_velocity.x || true_velocity.y)) {
    dash_offset = 0;
    dashing = true;
    dash_cooldown = 20;
  }
  if (dash_cooldown >= 16) {
    true_velocity *= 5.5f;
  }
  if (true_velocity.x && true_velocity.y) {
    position += true_velocity * mTime::delta_time * 0.86602540378f;
  } else {
    position += true_velocity * mTime::delta_time;
  }
  if (dash_offset != 0) {
    dash_offset--;
  } else if (dash_cooldown != 0) {
    assert(dash_offset == 0);
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
    idle_gif = mTexture::LoadImage(renderer, "assets/player_stop/" + std::to_string(++idle_frame) + ".png");
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
  //std::cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}

void Player::OnKeyDown(SDL_Event& event) {
  if (event.key.repeat) {
    return;
  }
  key[event.key.keysym.scancode] = true;
  if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
    if (dash_cooldown == 0) {
      dash_offset = 5;
    }
  } 
  if (direction_map.count(event.key.keysym.scancode)) {
    velocity += direction_map[event.key.keysym.scancode];
    if (velocity.x || velocity.y) {
      is_moving = true;
      play_idle = false;
    }
  }
  //std::cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}