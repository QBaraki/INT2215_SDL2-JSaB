#include "level_object.h"

#include <stdexcept>

LevelObject::LevelObject(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {}

LevelObject::~LevelObject() {
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

bool LevelObject::IsDestroyed() {
  return false;
}

std::vector<LevelObject*> LevelObject::Spawn() {
  return {};
}