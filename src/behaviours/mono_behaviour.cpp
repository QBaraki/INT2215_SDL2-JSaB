#include "mono_behaviour.h"

#include <stdexcept>

MonoBehaviour::MonoBehaviour(const SDL_Renderer* renderer_) : renderer(renderer_) {
  if (renderer == nullptr) {
    throw std::runtime_error("MonoBehaviour::MonoBehaviour(): renderer cannot be NULL");
  }
}

~MonoBehaviour() {
}

void MonoBehaviour(SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYUP:
      OnKeyUp(event);
      break;
    case SDL_KEYDOWN:
      OnKeyDown(event);
      break;
  }
}