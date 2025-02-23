#include "player.h"

#include "common.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

Player::Player(SDL_Renderer* renderer_, int size_, int x_, int y_, float speed_) {
  renderer = renderer_;
  size = size_;
  start_position = Vec2d(x_, y_);
  position = start_position;
  rect.w = rect.h = size;
  speed = speed_;
  angle = 90.0f;

  // Init player 'texture'
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
  if (!texture) {
    throw std::runtime_error("Texture creation failed! SDL error: " + std::string(SDL_GetError()));
  }
  SDL_Rect r = {0, 0, size, size};
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &r);
  SDL_SetRenderTarget(renderer, nullptr);

  // Control keys.
  key[0].binding = SDLK_UP;
  key[1].binding = SDLK_LEFT;
  key[2].binding = SDLK_RIGHT;
  key[3].binding = SDLK_DOWN;
}

Player::~Player() {
  SDL_DestroyTexture(texture);
}

void Player::Draw() {
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

void Player::HandleKeyDown(SDL_Event* event) {
  //std::cerr << "Player::HandleKeyDown() called.\n";
  if (event->key.keysym.sym == key[0].binding) {         // Go up.
    key[0].is_down = true;
  } else if (event->key.keysym.sym == key[1].binding) {  // Go left.
    key[1].is_down = true;
  } else if (event->key.keysym.sym == key[2].binding) {  // Go right.
    key[2].is_down = true;
  } else if (event->key.keysym.sym == key[3].binding) {  // Go down.
    key[3].is_down = true;
  }
}

void Player::HandleKeyUp(SDL_Event* event) {
  std::cerr << "Player::HandleKeyUp() called.\n";
  if (event->key.keysym.sym == key[0].binding) {         // Go up.
    key[0].is_down = false;
  } else if (event->key.keysym.sym == key[1].binding) {  // Go left.
    key[1].is_down = false;
  } else if (event->key.keysym.sym == key[2].binding) {  // Go right.
    key[2].is_down = false;
  } else if (event->key.keysym.sym == key[3].binding) {  // Go down.
    key[3].is_down = false;
  }
}

void Player::InputHandler(SDL_Event* event) {
  if (event->type == SDL_KEYDOWN) {
    HandleKeyDown(event);
  } else if (event->type == SDL_KEYUP) {
    HandleKeyUp(event);
  }
}

// TODO: Normalize speed for diagional movement.
void Player::UpdatePosition(float delta_time) {
  Vec2d offset;
  offset.x = (key[1].is_down * -speed) + (key[2].is_down * speed);
  offset.y = (key[0].is_down * -speed) + (key[3].is_down * speed);
  position += offset * delta_time;
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
  float destination_angle;
  if (offset.x < 0) {
    destination_angle = 270.0;
  } else {
    destination_angle = 90.0;
  }
  if (offset.y < 0) {
    destination_angle += (offset.x < 0 ? 45.0 : (offset.x > 0 ? -45.0 : -90.0));
  } else if (offset.y > 0) {
    destination_angle += (offset.x > 0 ? 45.0 : (offset.x < 0 ? -45.0 : 90.0));
  }
  if (angle != destination_angle) {
    float diff = destination_angle - angle;
    if (diff > 180.0) {
      diff -= 360.0;
    } else if (diff <= -180.0) {
      diff += 360.0;
    }
    if (diff > 0) {         // Rotate right.
      angle++;
    } else if (diff < 0) {  // Rotate left.
      angle--;
    }
  }
}