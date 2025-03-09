#include "level_object.h"

#include <stdexcept>

LevelObject::LevelObject() {}

LevelObject::~LevelObject() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
}

void LevelObject::SetRect(int x, int y, int w = -1, int h = -1) {
  rect.x = x;
  rect.y = y;
  if (w != -1 || h != -1) {
    rect.w = w;
    rect.h = h;
  }
}

SDL_Rect LevelObject::GetRect() {
  return rect;
}

double LevelObject::GetStartTime() {
  return start_time;
}

bool LevelObject::LoadImage(SDL_Renderer* renderer, const char* path) {
  texture = IMG_LoadTexture(renderer, path);
  if (texture == nullptr) {
    throw std::runtime_error("LoadImage(): Load image " + std::string(path) + " failed!. SDL error: " + IMG_GetError());
    return false;
  }
  return true;
}