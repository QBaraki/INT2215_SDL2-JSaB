#include "player.h"

#include "common.h"

#include <iostream>

Player::Player(SDL_Renderer* renderer_, int size_, int x_, int y_, float speed_) {
  renderer = renderer_;
  size = size_;
  start_position = Vec2d(x_, y_);
  position = start_position;
  rect.w = rect.h = size;
  speed = speed_;
  // Control keys.
  key[0].binding = SDLK_UP;
  key[1].binding = SDLK_LEFT;
  key[2].binding = SDLK_RIGHT;
  key[3].binding = SDLK_DOWN;
}

Player::~Player() {
  ;
}

void Player::Draw() {
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

void Player::HandleKeyDown(SDL_Event* event) {
  std::cerr << "Player::HandleKeyDown() called.\n";
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
}