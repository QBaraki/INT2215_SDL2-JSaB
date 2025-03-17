#include "player.h"

#include <iostream>
#include <stdexcept>

#include "common.h"
#include "managers/time.h"

Player::Player(SDL_Renderer* renderer_, int size_, int x_, int y_)
    : MonoBehaviour(renderer_), angle(90.0), size(size_), start_position(Vec2d(x_, y_)) {
  velocity = Vec2d(0, 0);
  position = start_position;
  rect.w = rect.h = size;
  // Init player 'texture'
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
  if (!texture) {
    throw std::runtime_error("Texture creation failed! SDL error: " + std::string(SDL_GetError()));
  }
  std::cout << "Player::Player(): Player loaded\n";
  SDL_Rect r = {0, 0, size, size};
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &r);
  SDL_SetRenderTarget(renderer, nullptr);
}

Player::~Player() {
  SDL_DestroyTexture(texture);
}

void Player::Update() {
  // Update position
  if (velocity.x && velocity.y) {
    position += velocity * my_time::delta_time * 0.86602540378f;
  } else {
    position += velocity * my_time::delta_time;
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
  rect.x = static_cast<int>(position.x);
  rect.y = static_cast<int>(position.y);
  SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

int Player::GetSize() {
  return size;
}

void Player::OnKeyUp(SDL_Event& event) {
  if (event.key.repeat) {
    return;
  }
  //std::cerr << "Called Player::OnKeyUp()\n";
  key[event.key.keysym.scancode] = false;
  if (direction_map.count(event.key.keysym.scancode)) {
    velocity -= direction_map[event.key.keysym.scancode];
  }
  //std::cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}

void Player::OnKeyDown(SDL_Event& event) {
  if (event.key.repeat) {
    return;
  }
  //std::cerr << "Called Player::OnKeyDown()\n";
  key[event.key.keysym.scancode] = true;
  if (direction_map.count(event.key.keysym.scancode)) {
    velocity += direction_map[event.key.keysym.scancode];
  }
  //std::cerr << "Player::velocity: " << velocity.x << ' ' << velocity.y << '\n';
}