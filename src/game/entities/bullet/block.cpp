#include "block.h"

#include <iostream>

#include "managers/time.h"
#include "managers/texture.h"

Block::Block(SDL_Renderer* renderer, double fatal_time_, double countdown_, double intact_time_, Vec2d top_left_, Vec2d bottom_right_) : LevelObject(renderer) {
  fatal_time = fatal_time_;
  intact_time = intact_time_;
  original_countdown = countdown_;
  countdown = original_countdown;
  white_time = 0.1f;
  disapearing_time = 0.07f;
  start_time = fatal_time - countdown;
  top_left = top_left_;
  bottom_right = bottom_right_;
  w = bottom_right.x - top_left.x;
  h = bottom_right.y - top_left.y;
  texture = mTexture::LoadImage(renderer, "assets/bullets/purple.png");
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);  // what the fuck?
  rect = {static_cast<int>(top_left.x), static_cast<int>(top_left.y), w, h};
  intacted = false;
}

void Block::Update() {
  countdown -= mTime::delta_time / 1000.0f;
  if (countdown > 0) {
    return;
  }
  if (white_time == 0.1f) {
    texture = mTexture::LoadImage(renderer, "assets/bullets/white.png");
  }
  white_time -= mTime::delta_time / 1000.0f;
  if (!intacted && white_time < 0) {
    texture = mTexture::LoadImage(renderer, "assets/bullets/purple.png");
    intacted = true;
  }
  intact_time -= mTime::delta_time / 1000.0f;
  if (intact_time <= 0.0f) {
    disapearing_time -= mTime::delta_time / 1000.0f;
  }
}

// This fucking suck.
void Block::Render() {
  if (countdown > 0.0f) {
    SDL_SetTextureAlphaMod(texture, int(160 * (original_countdown - countdown) / original_countdown));
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return;
  }
  if (white_time > 0.0f) {
    //SDL_Rect r = rect;
    //r.x -= 5; r.y -= 5;
    //r.w += 10; r.h += 10;
    SDL_SetTextureAlphaMod(texture, 0xFF);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    return;
  }
  if (intacted) {
    if (intact_time > 0.0f) {
      SDL_SetTextureAlphaMod(texture, 0xFF);
      SDL_RenderCopy(renderer, texture, nullptr, &rect);
    } else if (disapearing_time >= 0.0f) {
      SDL_SetTextureAlphaMod(texture, 0xFF / 0.07f * disapearing_time);
      SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
  }
}

bool Block::IsCollided(Player* target) {
  if (countdown > 0.0f) {
    return false;
  }
  Vec2d tl = {target->position.x + 2, target->position.y + 2};
  Vec2d br = {tl.x + target->GetSize() - 4, tl.y + target->GetSize() - 4};
  if (tl.x < bottom_right.x && br.x > top_left.x && tl.y < bottom_right.y && br.y > top_left.y) {
    return true;
  }
  return false;
}


bool Block::IsOutOfScreen() {
  return false;
}

bool Block::IsDestroyed() {
  return (intact_time <= 0.0f && disapearing_time <= 0.0f);
}

LevelObject* Block::Clone() {
  return new Block(*this);
}